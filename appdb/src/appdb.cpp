#include <soci/sqlite3/soci-sqlite3.h>
#include <chrono>
#include <vector>
#include <ctime>
#include "appdb.h"


using namespace soci;


AppDB::AppDB() : sql(*soci::factory_sqlite3(), DB_FILE_NAME) {
	createCPUInfoTable();
	createFileInfoTable();
}

void AppDB::createCPUInfoTable() {
	try {
		sql << " create table cpuinfo ("
			"frequency bigint,"
			"cache_size bigint,"
			"asked_at datetime,"
			"cores integer,"
			"name varchar(150)"
			");";
	}
	catch (soci_error const & error) {
		std::cerr << "Error creating table cpuinfo: " << error.what() << std::endl;
	}
}

void AppDB::createFileInfoTable() {
	try {
		sql << " create table fileinfo ("
			"size bigint,"
			"asked_at datetime,"
			"created_at datetime,"
			"modified_at datetime,"
			"name varchar(200)"
			");";
	}
	catch (soci_error const & error) {
		std::cerr << "Error creating table fileinfo: " << error.what() << std::endl;
	}
}

string AppDB::getNowDateTimeStr() {
	std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return convertTmDateTimeToStr(std::localtime(&now_time));
}

string AppDB::convertTmDateTimeToStr(struct std::tm * datetime) {
	char buffer [80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", datetime);
	string datetime_str(buffer);
	return datetime_str;

}

void AppDB::save(CPUInfo & cpu_info) {
	sql << "insert into cpuinfo(frequency, cache_size, asked_at, cores, name) "
		"values (:freq, :cache, :ask, :cores, :name);",
		use(cpu_info.frequency, "freq"), use(cpu_info.cache_size, "cache"),
		use(getNowDateTimeStr(), "ask"), 
		use(cpu_info.cores, "cores"),
		use(cpu_info.name, "name");
}

void AppDB::save(FileInfo & file_info) {
	sql << "insert into fileinfo(size, asked_at, created_at, modified_at, name) "
		"values (:size, :ask, :create, :mod, :name);",
		use(file_info.size, "size"), 
		use(getNowDateTimeStr(), "ask"),
		use(convertTmDateTimeToStr(&file_info.creation), "create"), 
		use(convertTmDateTimeToStr(&file_info.modification), "mod"),
		use(file_info.name, "name");
}

void AppDB::getDBBackUp(ostream & out_stream) {
	std::vector<string> tables;
	tables.push_back("cpuinfo");
	tables.push_back("fileinfo");
	out_stream << "{" << std::endl;
	for (string table_name : tables) {
		rowset<row> row_set = (sql.prepare << "select * from " << table_name);
		out_stream << "\"" << table_name << "\": [ " << std::endl;
		for (rowset<row>::const_iterator it = row_set.begin(); it != row_set.end(); it++) {
			out_stream << "{ ";
			row const & r = (*it);
			for (std::size_t i = 0; i != r.size(); ++i) {
				const column_properties& props = r.get_properties(i);
				out_stream << '"' << props.get_name() << "\": ";
				switch(props.get_data_type()) {
					case dt_string:
						out_stream << "\"" << r.get<std::string>(i) << "\"";
						break;
					case dt_double:
						out_stream << r.get<double>(i);
						break;
					case dt_integer:
						out_stream << r.get<int>(i);
						break;
					case dt_long_long:
						out_stream << r.get<long long>(i);
						break;
					case dt_unsigned_long_long:
						out_stream << r.get<unsigned long long>(i);
					case dt_date:
						std::tm when = r.get<std::tm>(i);
						out_stream << "\"" << asctime(&when) << "\"";
						break;
				}
				if (i != r.size() - 1) {
					out_stream << ", ";
				}
			}
			out_stream << "}" << std::endl;
		}
		out_stream << "]," << std::endl;
	}
	out_stream << "}" << std::endl;
}

