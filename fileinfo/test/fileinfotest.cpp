#include "gtest/gtest.h"
#include "fileinfo.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <time.h>


TEST(FileInfoTest, FileInformationTest1) {
	string file_name ("testfile.txt");
	std::ofstream testfile (file_name);
	testfile << "Test message" << std::endl;
	testfile.close();
        FileInfo file_info = getFileInfo(file_name);
        EXPECT_GT(file_info.size, 0);
        EXPECT_TRUE(file_info.name != "");
	EXPECT_GT(file_info.modification.tm_year, 100);
	EXPECT_GT(file_info.creation.tm_year, 100);
	remove(file_name.c_str());
}

