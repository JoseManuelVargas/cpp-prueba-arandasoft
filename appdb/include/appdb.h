#ifndef APPDB_H
#define APPDB_H

#include <string>
#include <iostream>
#include <fstream>
#include <soci/soci.h>
#include "cpuinfo.h"
#include "fileinfo.h"
#include <ctime>
#include <time.h>

#define DB_FILE_NAME "db_app.db"


using namespace soci;
using std::ostream;
using std::string;


class AppDB {
        public:
		AppDB();
		void save(CPUInfo & cpu_info);
		void save(FileInfo & file_info);
		void getDBBackUp(ostream & out_stream);
		string getNowDateTimeStr();
		string convertTmDateTimeToStr(struct std::tm * datetime);
	private:
		soci::session sql;
		void createCPUInfoTable();
		void createFileInfoTable();
};



#endif /* APPDB_H */
