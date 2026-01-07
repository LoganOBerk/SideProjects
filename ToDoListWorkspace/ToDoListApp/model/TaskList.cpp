#include "TaskList.h"
#include <sstream>

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::serialize(std::ostream& out) const {
	out << date.toString() << std::endl;
	for (const auto& kv : taskList) {
		kv.second.serialize(out);
	}
	out << '\n';
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::deserialize(std::istream& in) {
	std::string d;
	std::getline(in, d);
	std::istringstream iss(d);
	iss >> date;

	while (in.peek() != '\n') {
		Task t;
		t.deserialize(in);
		addTask(t);
	}
	in.ignore();
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::openTaskEditor(const std::string& n) {
	Task* t = getTask(n);
	if (!t) {
		UI::displayXDoesNotExist("Task");
		return;
	}
	while (true) {
		int input;
		std::string priority = t->getPriority();
		std::string name;
		std::string comment;
		std::string status = t->getStatus();

		UI::displayTaskEditorMenu(*t);

		UI::getIntegerInput(std::cin, input, 1, 5);


		switch (input) {
		case 1:
			UI::getPriorityInput(std::cin, priority);
			updatePriority(t, priority);
			break;
		case 2:
			UI::getNameInput(std::cin, name);
			updateTaskName(t, name);
			break;
		case 3:
			UI::getCommentInput(std::cin, comment);
			updateComment(t, comment);
			break;
		case 4:
			UI::getStatusInput(std::cin, status);
			updateStatus(t, status);
			break;
		case 5:
			return;
		}
	};
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
Date TaskList::getDate() const {
	return date;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
Task* TaskList::getTask(const std::string& n) {
	auto it = taskList.find(n);
	return (it != taskList.end()) ? &it->second : nullptr;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool TaskList::taskExists(const std::string& n) {
	return getTask(n);
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::addTask(const Task& t) {
	taskList.insert(std::pair<std::string, Task>(t.getTaskName(), t));
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::createTask(const std::string& n) {
	if (taskExists(n)) {
		UI::displayXAlreadyExists("Task");
	}
	else {
		Task task(n);
		UI::displaySuccessfulCreationOf("Task");
		addTask(task);
	}
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::removeTask(const std::string& n) {
	if (!taskExists(n)) {
		UI::displayXDoesNotExist("Task");
	}
	else {
		taskList.erase(n);
		UI::displaySuccessfulRemovalOf("Task");
	}
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::updateTaskName(Task* t, const std::string& n) {
	if (taskExists(n)) {
		UI::displayXAlreadyExists("Task");
		return;
	}
	t->setTaskName(n);
};

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::updatePriority(Task* t, const std::string& p) {
	t->setPriority(p);
};

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::updateComment(Task* t, const std::string& c) {
	t->setComment(c);
};

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskList::updateStatus(Task* t, const std::string& s) {
	t->setStatus(s);
};

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool TaskList::isEmpty() const{
	return taskList.empty();
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool TaskList::operator<(const TaskList& t) const {
	return date < t.date;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool TaskList::operator>(const TaskList& t) const {
	return t < *this;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool TaskList::operator==(const TaskList& t) const {
	return date == t.date;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
std::ostream& operator<<(std::ostream& os, const TaskList& x) {
	std::vector<Task> sortedTaskList;
	for (const auto& pair : x.taskList) {
		sortedTaskList.push_back(pair.second);
	}
	std::sort(sortedTaskList.begin(), sortedTaskList.end(), std::greater<Task>());
	for (const auto& task : sortedTaskList) {
		os << task << std::endl;
	}
	return os;
}