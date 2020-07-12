#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <string>
#include <ctime>
#include <time.h>


using std::string;


class TaskModel {
        public:
		int task;
		long long hour;
                string detail;
                struct std::tm creation;
};


#endif /* TASKMODEL_H */
