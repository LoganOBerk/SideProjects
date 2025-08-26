#include "Task.h"

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

void Task::serialize(std::ostream& out) const{
	out << taskName << std::endl;
	out << priority << std::endl;
	out << status << std::endl;
	out << comment << std::endl;
}
void Task::deserialize(std::istream& in) {
	std::getline(in, taskName);
	std::getline(in, priority);
	std::getline(in, status);
	std::getline(in, comment);
}
std::unordered_map<std::string, int> Task::priorityLvl = { {"low", 1}, {"medium", 2}, {"high", 3} };

std::string Task::getPriority() const {
	return priority;
}
std::string Task::getTaskName() const {
	return taskName;
}
std::string Task::getComment() const {
	return comment;
}
std::string Task::getStatus() const {
	return status;
}

void Task::setStatus(const std::string& s) {
	this->status = s;
}
void Task::setPriority(const std::string& p) {
	this->priority = p;
}
void Task::setTaskName(const std::string& tn) {
	this->taskName = tn;
}
void Task::setComment(const std::string& c) {
	this->comment = c;
}

bool Task::operator<(const Task& t) const{
	return priorityLvl[priority] < priorityLvl[t.priority];
}
bool Task::operator>(const Task& t) const {
	return t < *this;
}
bool Task::operator==(const Task& t) const {
	return taskName == t.taskName;
}








	




