#include "TaskList.h"
void TaskList::serialize(std::ostream& out) const {
	out << date.toString() << std::endl;
	for (const auto& kv : taskList) {
		kv.second.serialize(out);
	}
	out << '\n';
}
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

Date TaskList::getDate() const {
	return date;
}

Task* TaskList::getTask(const std::string& n) {
	auto it = taskList.find(n);
	return (it != taskList.end()) ? &it->second : nullptr;
}

bool TaskList::taskExists(const std::string& n) {
	return getTask(n);
}

void TaskList::addTask(const Task& t) {
	taskList.insert(std::pair<std::string, Task>(t.getTaskName(), t));
}

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

void TaskList::removeTask(const std::string& n) {
	if (!taskExists(n)) {
		UI::displayXDoesNotExist("Task");
	}
	else {
		taskList.erase(n);
		UI::displaySuccessfulRemovalOf("Task");
	}
}
void TaskList::updateTaskName(Task* t, const std::string& n) {
	if (taskExists(n)) {
		UI::displayXAlreadyExists("Task");
		return;
	}
	t->setTaskName(n);
};
void TaskList::updatePriority(Task* t, const std::string& p) {
	t->setPriority(p);
};
void TaskList::updateComment(Task* t, const std::string& c) {
	t->setComment(c);
};
void TaskList::updateStatus(Task* t, const std::string& s) {
	t->setStatus(s);
};

bool TaskList::isEmpty() const{
	return taskList.empty();
}
bool TaskList::operator<(const TaskList& t) const {
	return date < t.date;
}
bool TaskList::operator>(const TaskList& t) const {
	return t < *this;
}
bool TaskList::operator==(const TaskList& t) const {
	return date == t.date;
}

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