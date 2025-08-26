#pragma once

#include <string>
#include <iostream>
#include <algorithm>

class TaskList;
class Task;
class Date;

class UI {
public:
    // Menus
    static void welcomeMenu();
    static void displayTaskEditorMenu(Task& t);
    static void displayTaskListMenu(TaskList& tl);
    static void displayTodoListManagerMenu();

    // Input handlers
    static void getIntegerInput(std::istream& is, int& input, int lower, int upper);
    static void getNameInput(std::istream& is, std::string& name);
    static void getPriorityInput(std::istream& is, std::string& priority);
    static void getStatusInput(std::istream& is, std::string& status);
    static void getDateInput(std::istream& is, Date& date);
    static void getCommentInput(std::istream& is, std::string& comment);

    // Messages and prompts
    static void displayXAlreadyExists(const std::string& x);
    static void displaySuccessfulCreationOf(const std::string& x);
    static void displaySuccessfulRemovalOf(const std::string& x);
    static void displayXDoesNotExist(const std::string& x);

    static void listAccessPrompt();
    static void listCreationPrompt();
    static void listRemovalPrompt();
};
