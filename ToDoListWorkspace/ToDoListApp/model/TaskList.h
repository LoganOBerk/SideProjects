#pragma once

#include "UI.h"
#include "Task.h"
#include "Date.h"
#include "String.util.h"

class Task;

class TaskList {
private:
	struct CaseInsensitiveHash {
		size_t operator()(const std::string& s) const {
			return std::hash<std::string>()(toLower(s));
		}
	};

	struct CaseInsensitiveEqual {
		bool operator()(const std::string& a, const std::string& b) const {
			return toLower(a) == toLower(b);
		}
	};
protected:
	Date date;
	std::unordered_map<std::string, Task, CaseInsensitiveHash, CaseInsensitiveEqual> taskList;
	friend std::ostream& operator<<(std::ostream& os, const TaskList& x);;

public:
	TaskList() {}
	TaskList(Date d) : date(d) {}

	Date getDate() const;
	Task* getTask(const std::string& n);
	bool taskExists(const std::string& n);

	void createTask(const std::string& n);

	void updateTaskName(Task* t, const std::string& n);
	void updatePriority(Task* t, const std::string& p);
	void updateComment(Task* t, const std::string& c);
	void updateStatus(Task* t, const std::string& s);
	bool isEmpty() const;
	void openTaskEditor(const std::string& n);
	void addTask(const Task& t);
	void removeTask(const std::string& n);

	bool operator<(const TaskList& t) const;
	bool operator>(const TaskList& t) const;
	bool operator==(const TaskList& t) const;
};