#include "gtest/gtest.h"
#include <stdio.h>
#include <iostream>
#include "appdb.h"
#include "taskmodel.h"
#include <ctime>
#include <string>
#include <time.h>


TEST(CPUInfoTest, InformationTest1) {
	std::string db_file_name("db_test.db");
	AppDB db(db_file_name);
	struct std::tm min_dt = {0};
	min_dt.tm_year = 0;
	min_dt.tm_mday = 1;
	min_dt.tm_mon = 0;
	min_dt.tm_hour = 0;
	min_dt.tm_wday = 0;
	min_dt.tm_min = 0;
	min_dt.tm_sec = 0;
	CPUInfo cpu_info;
	cpu_info.frequency = 2700;
	cpu_info.cache_size = 256000;
	cpu_info.cores = 8;
	cpu_info.name = "Test CPU Intel";
	db.save(cpu_info);
	cpu_info.name = "Test CPU 2";
	cpu_info.frequency = 3100;
	db.save(cpu_info);
	FileInfo file_info;
	file_info.creation = min_dt;
	file_info.modification = min_dt;
	file_info.name = "new/file/test.txt";
	file_info.size = 43243;
	db.save(file_info);
	file_info.name = "other/file.txt";
	db.save(file_info);
	TaskModel task;
	task.task = 2;
	task.hour = 1594525724;
	task.detail = "test.txt";
	db.save(task);
	task.task = 1;
	task.hour += 123423;
	task.detail = "";
	db.save(task);
	db.getDBBackUp(std::cout);
	std::vector<TaskModel> tasksVector;
	db.getLastTasks(tasksVector, 159);
	EXPECT_EQ(tasksVector.size(), 2);
	for (int i = 0; i < tasksVector.size(); i++) {
		TaskModel & inTask = tasksVector.at(i);
		EXPECT_GE(inTask.hour, 159);
		EXPECT_GE(inTask.task, 1);
		std::cout << i << "-> Task.task " << inTask.task << ". Task.hour " << inTask.hour << ". Task.detail " << inTask.detail << std::endl;
	}
	remove(db_file_name.c_str());
}

