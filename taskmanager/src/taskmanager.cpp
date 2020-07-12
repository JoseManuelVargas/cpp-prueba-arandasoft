#include "taskmanager.h"
#include "taskmodel.h"
#include "cpuinfo.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <ctime>


using std::string;
using std::ofstream;
using json = nlohmann::json;


void TaskManager__run(TaskManager * self) {
	self->run();
}

void TaskManager__executeCPUTask(TaskManager * self) {
	self->executeCPUTask();
}

void TaskManager__executeFileTask(TaskManager * self, string file_name) {
	self->executeFileTask(file_name);
}

void TaskManager__executeBackUpTask(TaskManager * self) {
	self->executeBackUpTask();
}


TaskManager::TaskManager(string db_file_name, int port, string output_file) : out_file(output_file), server(port), database(db_file_name), scheduler(24), b_running(true), socket_port(port) {
	reloadTasks();
}


void TaskManager::reloadTasks() {
	long long epoch = static_cast<long long>(std::time(nullptr));
	std::vector<TaskModel> tasks;
	database.getLastTasks(tasks, epoch);
	for (int i = 0; i < tasks.size(); i++) {
		addTask(tasks.at(i));
	}
}


void TaskManager::run() {
	while (b_running) {
		server.acceptSocket();
		string line = server.readLine();
		json task_json = json::parse(line);
		if (!task_json.contains("task")) {
			server.sendLine("Wrong input: No task key");
			continue;
		}
		if (!task_json.contains("hour")) {
			server.sendLine("Wrong input: No hour key");
			continue;
		}
		TaskModel new_task;
		new_task.task = task_json["task"].get<int>();
		if (new_task.task <= 0 || new_task.task > 3) {
			server.sendLine("Wrong task number");
			continue;
		}
		new_task.hour = task_json["hour"].get<long long>();
		if (task_json.contains("detail")) {
			new_task.detail = task_json["detail"].get<string>();
		}
		else {
			new_task.detail = "";
		}
		addTask(new_task);
		server.sendLine("OK");
	}
}


void TaskManager::addTask(TaskModel & task_model) {
	database.save(task_model);
	std::time_t unix_time = task_model.hour;
	std::tm tm_time = *(std::localtime(&unix_time));
	char time_buff[128];
	strftime(time_buff, 128, "%Y/%m/%d %H:%M:%S", &tm_time);
	string unix_date_str(time_buff);
	string unix_date;
	if (task_model.task == 1) {
		scheduler.at(unix_date_str, TaskManager__executeCPUTask, this);
	}
	else if (task_model.task == 2) {
		scheduler.at(unix_date_str, TaskManager__executeFileTask,this,  task_model.detail);
	}
	else if (task_model.task == 3) {
		scheduler.at(unix_date_str, TaskManager__executeBackUpTask, this);
	}
}


void TaskManager::executeCPUTask() {
	CPUInfo cpu_info = getCPUInfo();
	database.save(cpu_info);
}


void TaskManager::executeFileTask(string file_name) {
	FileInfo file_info = getFileInfo(file_name);
	database.save(file_info);
}


void TaskManager::executeBackUpTask() {
	ofstream out_json;
	out_json.open(out_file);
	database.getDBBackUp(out_json);
	out_json.close();
}

void TaskManager::stop() {
	b_running = false;
	SocketClient client("127.0.0.1", socket_port);
	string msg("end");
	client.sendLine(msg);
	client.close();
	server.close();
}


void TaskManager::start() {
	scheduler.in(std::chrono::seconds(0), TaskManager__run, this);
}

