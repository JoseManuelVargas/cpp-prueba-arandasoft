#ifndef APPDB_H
#define APPDB_H

#include <string>
#include <iostream>
#include <fstream>
#include <soci/soci.h>
#include "cpuinfo.h"
#include "fileinfo.h"
#include "taskmodel.h"
#include <ctime>
#include <time.h>
#include <vector>

#define DB_FILE_NAME "db_app.db"


using namespace soci;
using std::ostream;
using std::string;


class AppDB {
        public:
		AppDB();
		void save(CPUInfo & cpu_info);
		void save(FileInfo & file_info);
		void save(TaskModel & task_model);
		void getDBBackUp(ostream & out_stream);
		void getLastTasks(std::vector<TaskModel> & out_vector, long long from_hour);
		string getNowDateTimeStr();
		string convertTmDateTimeToStr(struct std::tm * datetime);
	private:
		soci::session sql;
		void createCPUInfoTable();
		void createFileInfoTable();
		void createTaskTable();
};



#endif /* APPDB_H */
