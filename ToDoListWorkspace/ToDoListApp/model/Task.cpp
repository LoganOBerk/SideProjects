#include "Task.h"

std::unordered_map<std::string, int> Task::priorityLvl = { {"low", 1}, {"medium", 2}, {"high", 3} };

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
std::ostream& operator<<(std::ostream& os, const Task& x) {
	std::string taskName = x.taskName;
	std::string comment = x.comment;
	std::string status = x.status;
	std::string priority = x.priority;
	priority[0] = std::toupper(priority[0]);

	os << taskName << std::endl;
	os << "   Priority: " << priority << std::endl;
	os << "   Status: " << status << std::endl;
	os << "   Comment: " << comment << std::endl;
	return os;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void Task::serialize(std::ostream& out) const{
	out << taskName << std::endl;
	out << priority << std::endl;
	out << status << std::endl;
	out << comment << std::endl;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void Task::deserialize(std::istream& in) {
	std::getline(in, taskName);
	std::getline(in, priority);
	std::getline(in, status);
	std::getline(in, comment);
}

//INPUT: None
//OUTPUT: string representing the priority level (high, medium, low)
//PRECONDITION: The Task object is valid and constructed
//POSTCONDITION: no modification to object; returns task priority level
std::string Task::getPriority() const {
	return priority;
}

//INPUT: None
//OUTPUT: string representing the name of the task
//PRECONDITION: The Task object is valid and constructed
//POSTCONDITION: no modification to object; returns task name 
std::string Task::getTaskName() const {
	return taskName;
}

//INPUT: None 
//OUTPUT: string representing the comment in task
//PRECONDITION: The Task object is valid and constructed
//POSTCONDITION: no modification to object; returns comment
std::string Task::getComment() const {
	return comment;
}

//INPUT: None 
//OUTPUT: string representing the status (complete, uncomplete)
//PRECONDITION: The Task object is valid and constructed
//POSTCONDITION: no modification to the object; returns comment
std::string Task::getStatus() const {
	return status;
}

//INPUT: s, a formatted string
//OUTPUT: None
//PRECONDITION: Task object is valid and constructed and string s is either "Complete", or "Uncomplete"
//POSTCONDITION: object is updated to contain passed status
void Task::setStatus(const std::string& s) {
	this->status = s;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void Task::setPriority(const std::string& p) {
	this->priority = p;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void Task::setTaskName(const std::string& tn) {
	this->taskName = tn;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void Task::setComment(const std::string& c) {
	this->comment = c;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool Task::operator<(const Task& t) const{
	if (priorityLvl[priority] != priorityLvl[t.priority])
		return priorityLvl[priority] < priorityLvl[t.priority];

	return taskName < t.taskName;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool Task::operator>(const Task& t) const {
	return t < *this;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool Task::operator==(const Task& t) const {
	return taskName == t.taskName;
}








	




