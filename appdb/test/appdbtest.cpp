#include "gtest/gtest.h"
#include <stdio.h>
#include <iostream>
#include "appdb.h"
#include <ctime>
#include <time.h>


TEST(CPUInfoTest, InformationTest1) {
	AppDB db;
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
	db.getDBBackUp(std::cout);
	remove(DB_FILE_NAME);
}

