#include "TodoListManager.h"


TaskList* TodoListManager::getList(const Date& d) {
	auto it = taskLists.find(d);
	return (it != taskLists.end()) ? &it->second : nullptr;
}
bool TodoListManager::taskListExists(const Date& d) {
	return getList(d);
}

void TodoListManager::createList(const Date& d) {
	if (!d.isValid()) return;

	if (taskListExists(d)) {
		UI::displayXAlreadyExists("List");
	}
	else {
		TaskList taskList(d);
		UI::displaySuccessfulCreationOf("List");
		taskLists.insert(std::pair<const Date, TaskList>(d, taskList));
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

