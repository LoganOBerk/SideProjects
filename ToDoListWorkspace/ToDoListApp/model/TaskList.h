#pragma once

#include "Task.h"
#include "Date.h"
#include "String.util.h"
#include "UI.h"
#include <unordered_map>
#include <string>
#include <ostream>

class TaskList {
protected:
    Date date;
    std::unordered_map<std::string, Task, CaseInsensitiveHash, CaseInsensitiveEqual> taskList;

    // Allow streaming of TaskList objects
    friend std::ostream& operator<<(std::ostream& os, const TaskList& x);

public:
    // Constructors
    TaskList() = default;
    explicit TaskList(const Date& d) : date(d) {}

    // Accessors
    Date getDate() const;
    Task* getTask(const std::string& name);
    bool taskExists(const std::string& name);

    // Modifiers
    void createTask(const std::string& name);
    void addTask(const Task& task);
    void removeTask(const std::string& name);

    void updateTaskName(Task* task, const std::string& newName);
    void updatePriority(Task* task, const std::string& newPriority);
    void updateComment(Task* task, const std::string& newComment);
    void updateStatus(Task* task, const std::string& newStatus);

    // Utility
    bool isEmpty() const;
    void openTaskEditor(const std::string& name);

    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

    // Comparison operators
    bool operator<(const TaskList& other) const;
    bool operator>(const TaskList& other) const;
    bool operator==(const TaskList& other) const;
};
