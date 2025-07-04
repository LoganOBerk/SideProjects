#pragma once

#include <string>
#include <iostream>
#include <algorithm>

#include "Date.h"
#include "Task.h"
#include "TaskList.h"
#include "String.util.h"

class Task;
class TaskList;

class UI {
public:
	static void welcomeMenu();

	static void getIntegerInput(std::istream& is, int& input, const int lower, const int upper);
	static void getNameInput(std::istream& is, std::string& n);
	static void getPriorityInput(std::istream& is, std::string& input);
	static void getStatusInput(std::istream& is, std::string& input);
	static void getDateInput(std::istream& is, Date& input);
	static void getCommentInput(std::istream& is, std::string& input);

	static void displayTaskEditorMenu(Task& t);
	static void displayTaskListMenu(TaskList& tl);
	static void displayTodoListManagerMenu();


};