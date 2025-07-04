#include "Task.h"

std::ostream& operator<<(std::ostream& os, const Task& x) {
	std::string taskName = x.taskName;
	std::string comment = x.comment;
	std::string status = x.status;
	std::string priority = x.getPriority();
	priority[0] = std::toupper(priority[0]);

	os << taskName << std::endl;
	os << "   Priority: " << priority << std::endl;
	os << "   Status: " << status << std::endl;
	os << "   Comment: " << comment << std::endl;
	return os;
}

const std::unordered_map<int, std::string> Task::intToPriority = { {1, "low"}, {2, "medium"}, {3, "high"} };
const std::unordered_map<std::string, int> Task::priorityToInt = { {"low", 1}, {"medium", 2}, {"high", 3} };

int Task::getPriorityLvl() const {
	return priorityLvl;
}
std::string Task::getPriority() const {
	return intToPriority.at(priorityLvl);
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

void Task::setStatus(const std::string& status) {
	this->status = status;
}
void Task::setPriorityLvl(const std::string& priority) {
	this->priorityLvl = priorityToInt.at(priority);
}
void Task::setTaskName(const std::string& taskName) {
	this->taskName = taskName;
}
void Task::setComment(const std::string& comment) {
	this->comment = comment;
}

bool Task::operator<(const Task& t) const {
	return priorityLvl < t.priorityLvl;
}
bool Task::operator>(const Task& t) const {
	return t < *this;
}
bool Task::operator==(const Task& t) const {
	return taskName == t.taskName;
}








	




