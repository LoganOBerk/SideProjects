#pragma once

#include <map>

#include "TaskList.h"
#include "Date.h"
#include "UI.h"

class TodoListManager {
protected:
	std::map<const Date, TaskList> taskLists;

public:
	TaskList* getList(const Date& d);
	bool taskListExists(const Date& d);
	void createList(const Date& d);
	void addList(const TaskList& l);

	void openList(const Date& d);
	void removeList(const Date& d);
};