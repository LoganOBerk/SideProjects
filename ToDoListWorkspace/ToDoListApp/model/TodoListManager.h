#pragma once

#include <map>

#include "TaskList.h"
#include "Date.h"
#include "UI.h"

class TodoListManager {
protected:
    std::map<Date, TaskList> taskLists;

public:
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);
    // Accessors
    TaskList* getList(const Date& d);
    bool taskListExists(const Date& d);
    // Modifiers
    void addTaskList(const TaskList& tl);
    void createList(const Date& d);
    void openList(const Date& d);
    void removeList(const Date& d);
};
