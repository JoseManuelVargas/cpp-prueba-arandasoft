#include <windows.h>
#include "fileinfo.h"
#include <string>
#include <ctime>


using namespace std;


std::tm convertFileTimeToTM(const FILETIME *lpFileTime) {
	SYSTEMTIME sysTime = { 0 };
	FileTimeToSystemTime(lpFileTime, &sysTime);
	std::tm tm_time;
	tm_time.tm_sec = sysTime.wSecond;
	tm_time.tm_min = sysTime.wMinute;
	tm_time.tm_hour = sysTime.wHour;
	tm_time.tm_mday = sysTime.wDay;
	tm_time.tm_mon = sysTime.wMonth - 1;
	tm_time.tm_year = sysTime.wYear - 1900;
	tm_time.tm_wday = sysTime.wDayOfWeek;
	return tm_time;
}


FileInfo getFileInfo(string file_name) {
	WIN32_FILE_ATTRIBUTE_DATA fInfo;
	GetFileAttributesEx(file_name.c_str(), GetFileExInfoStandard, &fInfo);
	LARGE_INTEGER size;
    size.HighPart = fInfo.nFileSizeHigh;
    size.LowPart = fInfo.nFileSizeLow;
	FileInfo file_info;
	file_info.name = file_name;
	file_info.size = size.QuadPart;
	file_info.modification = convertFileTimeToTM(&fInfo.ftLastWriteTime);
	file_info.creation = convertFileTimeToTM(&fInfo.ftCreationTime);
	return file_info;
}

