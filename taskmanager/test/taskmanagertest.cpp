#include "gtest/gtest.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "taskmodel.h"
#include "socket.h"
#include "taskmanager.h"
#include <ctime>
#include <string>
#include <time.h>
#include <chrono>


TEST(TaskManagerTest, TMTest1) {
	std::string db_name("db_test.db");
	std::string json_file("test_backup.json");
	int port = 8080;
	TaskManager task_man(db_name, port, json_file);
	std::cout << "Creado task manager" << std::endl;
	task_man.start();
	task_man.executeCPUTask();
	TaskModel task1;
	task1.task = 1;
	task1.detail = "";
	task1.hour = static_cast<long long>(std::time(nullptr)) + 1;
        task_man.addTask(task1);	
	task1.task = 3;
	task_man.addTask(task1);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	task1.task = 2;
	task1.detail = json_file;
	task1.hour += 1;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	SocketClient client("127.0.0.1", port);
	char task_buf [128];
	sprintf(task_buf, "{\"task\": 1, \"hour\": %lld}", task1.hour + 1);
	string task_str(task_buf);
	client.sendLine(task_buf);
	string okAnswer("OK");
	string answer = client.readLine();
	EXPECT_EQ(answer, okAnswer);
	std::cout << "Answer from server: " << answer << std::endl;
	client.close();
	
	client = SocketClient("127.0.0.1", port);
	sprintf(task_buf, "{\"task\": 2, \"hour\": %lld, \"detail\": \"%s\"}", task1.hour + 1, json_file.c_str());
	task_str = string(task_buf);
	client.sendLine(task_str);
	answer = client.readLine();
	EXPECT_EQ(answer, okAnswer);
	std::cout << "Answer from server: " << answer << std::endl;
	client.close();
	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	
	client = SocketClient("127.0.0.1", port);
	sprintf(task_buf, "{\"task\": 3, \"hour\": %lld}", task1.hour + 1);
	task_str = string(task_buf);
	client.sendLine(task_str);
	answer = client.readLine();
	EXPECT_EQ(answer, okAnswer);
	std::cout << "Answer from server: " << answer << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	client.close();
	
	std::ifstream in_file (json_file);
	string line;
	std::cout << "backup file:" << std::endl;
	while (std::getline(in_file, line)) {
		std::cout << line << std::endl;
	}
	in_file.close();
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	task_man.stop();
	std::cout << "Termina task manager" << std::endl;
	remove(db_name.c_str());
	remove(json_file.c_str());
}


