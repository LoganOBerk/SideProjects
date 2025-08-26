#include "TodoListManager.h"

void TodoListManager::serialize(std::ostream& out) const {
	for (const auto& kv : taskLists) {
		kv.second.serialize(out);
	}
}
void TodoListManager::deserialize(std::istream& in) {
	while (in.peek() != std::char_traits<char>::eof()) {
		TaskList tl;
		tl.deserialize(in);
		addTaskList(tl);
	}
}
TaskList* TodoListManager::getList(const Date& d) {
	auto it = taskLists.find(d);
	return (it != taskLists.end()) ? &it->second : nullptr;
}
bool TodoListManager::taskListExists(const Date& d) {
	return getList(d);
}

void TodoListManager::addTaskList(const TaskList& tl) {
	taskLists.insert(std::pair<const Date, TaskList>(tl.getDate(), tl));
}

void TodoListManager::createList(const Date& d) {
	if (!d.isValid()) return;

	if (taskListExists(d)) {
		UI::displayXAlreadyExists("List");
	}
	else {
		TaskList taskList(d);
		UI::displaySuccessfulCreationOf("List");
		addTaskList(taskList);
	}
}

void TodoListManager::removeList(const Date& d) {
	if (!d.isValid()) return;

	if (!taskListExists(d)) {
		UI::displayXDoesNotExist("List");
	}
	else {
		taskLists.erase(d);
		UI::displaySuccessfulRemovalOf("List");
	}
}

void TodoListManager::openList(const Date& d) {
	if (!d.isValid()) return;

	if (!taskListExists(d)) {
		UI::displayXDoesNotExist("List");
		return;
	}

	TaskList* tl = getList(d);
	while (true) {
		int input;
		std::string name;

		UI::displayTaskListMenu(*tl);
		UI::getIntegerInput(std::cin, input, 1, 4);


		switch (input) {
		case 1:
			UI::getNameInput(std::cin, name);
			tl->createTask(name);
			break;
		case 2:
			UI::getNameInput(std::cin, name);
			tl->removeTask(name);
			break;
		case 3:
			UI::getNameInput(std::cin, name);
			tl->openTaskEditor(name);
			break;
		case 4:
			return;
		}
	};
}

