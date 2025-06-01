#include <string>
#include <vector>
#include "Date.util.h"
class Task {
protected:
	int priorityLvl;
	std::string taskName;
	std::string comment;
	bool isComplete;
public:
	int getPriorityLvl() {
		return priorityLvl;
	}
	std::string getTaskName() {
		return taskName;
	}
	std::string getComment() {
		return comment;
	}
	bool getIsComplete() {
		return isComplete;
	}

	void setIsComplete(bool& isComplete) {
		this->isComplete = isComplete;
	}
	void setPriorityLvl(int& priorityLvl) {
		this->priorityLvl = priorityLvl;
	}
	void setTaskName(std::string& taskName) {
		this->taskName = taskName;
	}
	void setComment(std::string& comment) {
		this->comment = comment;
	}
	


};

class DaysTasks {
protected:
	Date date;
	std::vector<Task> taskList;
public:
	void addTask(Task& t) {

	}
	void removeTask(Task& t) {

	}
	void editTask(Task& t) {

	}

};

class TodoListManager {
protected:
	std::vector<DaysTasks> lists;
public:
	void addList(DaysTasks& l) {

	}
	void removeList(DaysTasks& l) {

	}
	void editList(DaysTasks& l) {

	}
};