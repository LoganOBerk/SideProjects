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
		std::cout << std::endl << "List Already Exists!" << std::endl;
	}
	else {
		TaskList taskList(d);
		std::cout << std::endl << "List Successfully Created!" << std::endl;
		taskLists.insert(std::pair<const Date, TaskList>(d, taskList));
	}
}

void TodoListManager::removeList(const Date& d) {
	if (!d.isValid()) return;

	if (!taskListExists(d)) {
		std::cout << std::endl << "List Does Not Exist!" << std::endl;
	}
	else {
		taskLists.erase(d);
		std::cout << std::endl << "List Successfully Removed!" << std::endl;
	}
}

void TodoListManager::openList(const Date& d) {
	if (!d.isValid()) return;
	if (!taskListExists(d)) {
		std::cout << std::endl << "List Does Not Exist!" << std::endl;
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

