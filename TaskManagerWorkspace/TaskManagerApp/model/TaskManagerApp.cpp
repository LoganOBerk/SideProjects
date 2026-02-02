#include "TaskManagerApp.h"

#include <fstream>

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskManagerApp::init(){
	std::fstream file("app_data.txt", std::ios::in);
	manager.deserialize(file);
	file.close();
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskManagerApp::run() {
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

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void TaskManagerApp::exit() {
	std::fstream file("app_data.txt", std::ios::out | std::ios::trunc);
	manager.serialize(file);
	file.close();
}