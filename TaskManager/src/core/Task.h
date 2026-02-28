#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <ostream>
#include "UI.h"

class Task {
private:
    static std::unordered_map<std::string, int> priorityLvl;

protected:
    std::string priority;
    std::string taskName;
    std::string comment;
    std::string status;

    // Allow stream output of Task objects
    friend std::ostream& operator<<(std::ostream& os, const Task& x);

public:
    // Constructor with default values
    Task(std::string tn = "-------",
        std::string p = "low",
        std::string c = "-------",
        std::string s = "Uncomplete")
        : taskName(tn), priority(p), comment(c), status(s) {
    }

    // Getters
    std::string getPriority() const;
    std::string getTaskName() const;
    std::string getComment() const;
    std::string getStatus() const;

    // Setters
    void setStatus(const std::string& s);
    void setPriority(const std::string& p);
    void setTaskName(const std::string& tn);
    void setComment(const std::string& c);

    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);
    // Comparison operators based on priority or other logic
    bool operator<(const Task& t) const;
    bool operator>(const Task& t) const;
    bool operator==(const Task& t) const;
};
