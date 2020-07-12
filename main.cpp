#include <iostream>
#include "taskmanager.h"


int main() {
	std::cout << "Starts Task manager programm" << std::endl;
	TaskManager task_man("app_db.db", 8080, "backup_db.json");
	task_man.run();
	return 0;
}

