#include <string>
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