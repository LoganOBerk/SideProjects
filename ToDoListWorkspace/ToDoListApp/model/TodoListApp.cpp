#include "TodoListApp.h"
void TodoListApp::run() {
	UI::welcomeMenu();
	while (true) {
		Date date;
		int input;

		UI::displayTodoListManagerMenu();
		UI::getIntegerInput(std::cin, input, 1, 4);

		switch (input) {
		case 1:
			std::cout << "What date would you like to access?" << std::endl;
			UI::getDateInput(std::cin, date);
			manager.openList(date);
			break;
		case 2:
			std::cout << "What date would you like to create a new list for?" << std::endl;
			UI::getDateInput(std::cin, date);
			manager.createList(date);
			break;
		case 3:
			std::cout << "What date would you like to remove a list?" << std::endl;
			UI::getDateInput(std::cin, date);
			manager.removeList(date);
			break;
		case 4:
			return;
		}
	}
}