#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>

using std::string;

class FileInfo {
        public:
		string name;
                string modification;
		string creation;
                long size;
};

FileInfo getFileInfo(string file_name);


#endif /* FILEINFO_H */

