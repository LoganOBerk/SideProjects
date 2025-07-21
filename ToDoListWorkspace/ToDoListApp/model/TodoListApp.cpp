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
			UI::listAccessPrompt();
			UI::getDateInput(std::cin, date);
			manager.openList(date);
			break;
		case 2:
			UI::listCreationPrompt();
			UI::getDateInput(std::cin, date);
			manager.createList(date);
			break;
		case 3:
			UI::listRemovalPrompt();
			UI::getDateInput(std::cin, date);
			manager.removeList(date);
			break;
		case 4:
			return;
		}
	}
}