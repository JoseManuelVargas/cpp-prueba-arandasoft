#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <ctime>
#include <time.h>

using std::string;

class FileInfo {
        public:
		string name;
                struct std::tm modification;
		struct std::tm creation;
                long size;
};

FileInfo getFileInfo(string file_name);


#endif /* FILEINFO_H */

