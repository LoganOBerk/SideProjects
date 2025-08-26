#include "UI.h"
#include "Date.h"
#include "Task.h"
#include "TaskList.h"
#include "String.util.h"

void UI::welcomeMenu() {
	std::cout << std::endl; std::cout << std::endl;
	std::cout << "=====================================" << std::endl;
	std::cout << "Welcome To Your To-do List Manager!" << std::endl;
	std::cout << "=====================================" << std::endl;
	std::cout << std::endl;
}

void UI::getIntegerInput(std::istream& is, int& input, const int lower, const int upper) {
	is >> input;
	std::cout << std::endl;
	if (is.peek() != '\n' || input > upper || input < lower) {
		std::cout << "Invalid Input: Input is " << lower << "-" << upper << std::endl;
		input = -1;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
}

void UI::getNameInput(std::istream& is, std::string& n) {
	std::cout << "Enter a task name: ";
	getline(is, n);
	trim(n);
}

void UI::getCommentInput(std::istream& is, std::string& input) {
	std::cout << "Write your comment here: ";
	getline(is , input);
}
void UI::getPriorityInput(std::istream& is, std::string& input) {
	std::cout << "Enter a priority level (high, medium or low): ";
	std::string initPrio = input;
	getline(is, input);
	trim(input);
	input = toLower(input);
	if (input != "high" && input != "medium" && input != "low") {
		std::cout << std::endl << "Invalid Priority: Priority is either high, medium or low" << std::endl;
		input = initPrio;
	}
}

void UI::getStatusInput(std::istream& is, std::string& input) {
	std::cout << "Set status (complete/uncomplete): ";
	std::string initStatus = input;
	getline(is, input);
	trim(input);
	toLower(input);
	if (input == "complete") input = "Complete";
	if (input == "uncomplete") input = "Uncomplete";
	if (input != "Complete" && input != "Uncomplete") {
		std::cout << std::endl << "Invalid Status: Status is either complete or uncomplete" << std::endl;
		input = initStatus;
	}
}

void UI::getDateInput(std::istream& is, Date& input) {
	std::cout << "Enter date: ";
	std::string s;
	getline(is, s);
	std::istringstream iss(s);
	iss >> input;
	if (iss.fail() || iss.peek() != EOF) {
		iss.clear();
		iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl << "Invalid Date/Format: type in MM/DD/YYYY or MM-DD-YYYY format" << std::endl;
		input = Date();
	}
}

void UI::displayTaskEditorMenu(Task& t){
	std::cout <<
	std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "             Edit Task               " << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << t << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "1. Priority Level" << std::endl;
	std::cout << "2. Task Name" << std::endl;
	std::cout << "3. Comment" << std::endl;
	std::cout << "4. Status" << std::endl;
	std::cout << "5. Go Back" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Enter a choice (1-5): ";
};
void UI::displayTaskListMenu(TaskList& tl){
	std::cout << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Date: " << tl.getDate() << std::endl << std::endl;
	if (!tl.isEmpty()) {
		std::cout << tl;
	}
	else {
		std::cout << "No tasks at this time." << std::endl;
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "1. Add Task" << std::endl;
	std::cout << "2. Remove Task" << std::endl;
	std::cout << "3. Edit Task" << std::endl;
	std::cout << "4. Go Back" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Enter a choice (1-4): ";
};
void UI::displayTodoListManagerMenu(){
	std::cout <<
	std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Create, Manage, or Remove To-do Lists" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "1. Open List" << std::endl;
	std::cout << "2. Create List" << std::endl;
	std::cout << "3. Remove List" << std::endl;
	std::cout << "4. Save & Exit" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Enter a choice (1-4): ";
};

void UI::displayXAlreadyExists(const std::string& x) {
	std::cout << std::endl << x << " Already Exists!" << std::endl;
}
void UI::displaySuccessfulCreationOf(const std::string& x) {
	std::cout << std::endl << x << " Successfully Created!" << std::endl;
}
void UI::displaySuccessfulRemovalOf(const std::string& x) {
	std::cout << std::endl << x << " Successfully Removed!" << std::endl;
}
void UI::displayXDoesNotExist(const std::string& x) {
	std::cout << std::endl << x << " Does Not Exist!" << std::endl;
}

void UI::listAccessPrompt(){
	std::cout << "What list would you like to access?" << std::endl;
}
void UI::listCreationPrompt(){
	std::cout << "What date would you like to create a new list for?" << std::endl;
}
void UI::listRemovalPrompt(){
	std::cout << "What date would you like to remove a list?" << std::endl;
}