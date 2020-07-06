#include "gtest/gtest.h"
#include "cpuinfo.h"


TEST(CPUInfoTest, InformationTest1) {
	CPUInfo cpu_info = getCPUInfo();
	EXPECT_GT(cpu_info.cores, 0);
	EXPECT_GT(cpu_info.frequency, 0);
	EXPECT_GT(cpu_info.cache_size, 0);
	EXPECT_TRUE(cpu_info.name != "");
}

