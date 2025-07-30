#pragma once

#include <unordered_map>
#include <string>
#include "UI.h"

class Task {
private:
	static const std::unordered_map<int, std::string> intToPriority;
	static const std::unordered_map<std::string, int> priorityToInt;
protected:
	int priorityLvl;
	std::string taskName;
	std::string comment;
	std::string status;

	friend std::ostream& operator<<(std::ostream& os, const Task& x);

public:

	Task(std::string tn = "-------", int pl = 1, std::string c = "-------", std::string s = "Uncomplete") : taskName(tn), priorityLvl(pl), comment(c), status(s) {}

	std::string getPriority() const;
	std::string getTaskName() const;
	std::string getComment() const;
	std::string getStatus() const;

	void setStatus(const std::string& status);
	void setPriorityLvl(const std::string& priority);
	void setTaskName(const std::string& taskName);
	void setComment(const std::string& comment);

	bool operator<(const Task& t) const;
	bool operator>(const Task& t) const;
	bool operator==(const Task& t) const;
};

