#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>
#include <iostream>
#include <vector>
#include "socket.h"
#include "appdb.h"
#include "taskmodel.h"
#include "Scheduler.h"


using std::string;


class TaskManager {
        public:
		TaskManager(string db_file_name, int port, string output_file);
		void run();
		void start();
		void stop();
		void executeFileTask(string file_name);
		void executeBackUpTask();
		void executeCPUTask();
		void addTask(TaskModel & task_model);
	private:
		void reloadTasks();
		string out_file;
		SocketServer server;
		AppDB database;
		Bosma::Scheduler scheduler;
		bool b_running;
		int socket_port;
};



#endif /* TASKMANAGER_H */
