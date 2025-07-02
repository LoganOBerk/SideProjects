#include <string>
#include <vector>
#include <algorithm>
#include "Date.h"

bool BothAreSpaces(char lhs, char rhs) {
	return (lhs == rhs) && (lhs == ' ');
}

void removeWhiteSpace(std::string& s) {
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

void trim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
	std::string::iterator new_end = std::unique(s.begin(), s.end(), BothAreSpaces);
	s.erase(new_end, s.end());
}

void getIntegerInput(std::istream& is, int& input) {
	is >> input;
	if (is.peek() != '\n') {
		input = -1;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void getNameInput(std::istream& is, std::string& n) {
	getline(is, n);
	trim(n);
}

void getPriorityInput(std::istream& is, std::string& input) {
	std::string initPrio = input;
	getline(is, input);
	trim(input);
	std::transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) { return std::tolower(c); });
	if (input != "high" && input != "medium" && input != "low") {
		std::cout << std::endl << "Invalid Priority: Priority is either high, medium or low" << std::endl;
		input = initPrio;
	}
}

void getStatusInput(std::istream& is, std::string& input) {
	std::string initStatus = input;
	getline(is, input);
	trim(input);
	std::transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) { return std::tolower(c); });
	if (input == "complete") input = "Complete";
	if (input == "uncomplete") input = "Uncomplete";
	if (input != "Complete" && input != "Uncomplete") {
		std::cout << std::endl << "Invalid Status: Status is either complete or uncomplete" << std::endl;
		input = initStatus;
	}
}

void getDateInput(std::istream& is, Date& input) {
	std::string s;
	getline(is, s);
	removeWhiteSpace(s);
	std::istringstream iss(s);
	iss >> input;
	if (iss.fail() || iss.peek() != EOF) {
		iss.clear();
		iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl << "Invalid Date/Format: type in MM/DD/YYYY or MM-DD-YYYY format" << std::endl;
		input = Date();
	}
}


class Task {
protected:
	int priorityLvl;
	std::string taskName;
	std::string comment;
	std::string status;

	
	friend std::ostream& operator<<(std::ostream& os, const Task& x);
	
public:

	Task(std::string tn = "-------", int pl = 1, std::string c = "-------", std::string s = "Uncomplete") : taskName(tn), priorityLvl(pl), comment(c), status(s) {}

	int getPriorityLvl() const;
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

	void displayTask() const;
	void displayOptions() const;
	void displayTaskMenu() const;
	
};

std::ostream& operator<<(std::ostream& os, const Task& x) {
	os << x.taskName << std::endl;
	os << "   Priority: " << x.getPriority() << std::endl;
	os << "   Status: " << x.status << std::endl;
	os << "   Comment: " << x.comment << std::endl;
	return os;
}

int Task::getPriorityLvl() const {
	return priorityLvl;
}
std::string Task::getPriority() const {
	std::unordered_map<int, std::string> priority = { {1, "Low"}, {2, "Medium"}, {3, "High"} };
	return priority[priorityLvl];
}
std::string Task::getTaskName() const {
	return taskName;
}
std::string Task::getComment() const {
	return comment;
}
std::string Task::getStatus() const {
	return status;
}

void Task::setStatus(const std::string& status) {
	this->status = status;
}
void Task::setPriorityLvl(const std::string& priority) {
	std::unordered_map<std::string, int> priorityLvl = { {"low", 1}, {"medium", 2}, {"high", 3} };
	this->priorityLvl = priorityLvl[priority];
}
void Task::setTaskName(const std::string& taskName) {
	this->taskName = taskName;
}
void Task::setComment(const std::string& comment) {
	this->comment = comment;
}

bool Task::operator<(const Task& t) const {
	return priorityLvl < t.priorityLvl;
}
bool Task::operator>(const Task& t) const {
	return t < *this;
}
bool Task::operator==(const Task& t) const {
	return taskName == t.taskName;
}
void Task::displayTask() const {
	std::cout << *this << std::endl;
}
void Task::displayTaskMenu() const {
	std::cout <<
		std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "             Edit Task               " << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	displayTask();
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	displayOptions();
}

void Task::displayOptions() const {
	std::cout << "1. Priority Level" << std::endl;
	std::cout << "2. Task Name" << std::endl;
	std::cout << "3. Comment" << std::endl;
	std::cout << "4. Status" << std::endl;
	std::cout << "5. Go Back" << std::endl;
}

class TaskList {
protected:
	Date date;
	std::unordered_map<std::string, Task> taskList;
	friend std::ostream& operator<<(std::ostream& os, const TaskList& x);

	
public:
	TaskList() {}
	TaskList(Date d) : date(d) {}
	
	Date getDate() const{
		return date;
	}
	Task* getTask(const std::string& n) {
		auto it = taskList.find(n);
		return (it != taskList.end()) ? &it->second : nullptr;
	}
	bool taskExists(const std::string& n) {
		return getTask(n);
	}

	void createTask(const std::string& n) {
		if (taskExists(n)) {
			std::cout << std::endl << "Task Already Exists!" << std::endl;
		}
		else {
			Task task(n);
			std::cout << std::endl << "Task Successfully Created!" << std::endl;
			addTask(task);
		}
	}

	void updateTaskName(Task* t, const std::string& n) {
		if (taskExists(n)) {
			std::cout << std::endl << "Task Already Exists!" << std::endl;
			return;
		}
		t->setTaskName(n);
	};
	void updatePriority(Task* t, const std::string& p) {
		t->setPriorityLvl(p);
	};
	void updateComment(Task* t, const std::string& c) {
		t->setComment(c);
	};
	void updateStatus(Task* t, const std::string& s) {
		t->setStatus(s);
	};

	void openTaskEditor(const std::string& n) {
		Task* t = getTask(n);
		if (!t) {
			std::cout << std::endl << "Task Does Not Exist!" << std::endl;
			return;
		}
		while (true) {
			int input;
			std::string priority = t->getPriority();
			std::string name;
			std::string comment;
			std::string status = t->getStatus();

			t->displayTaskMenu();
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cout << "Enter a choice: ";
			getIntegerInput(std::cin, input);


			switch (input) {
			case 1:
				std::cout << std::endl;
				std::cout << "Enter a priority level (high, medium or low): ";
				getPriorityInput(std::cin, priority);
				updatePriority(t, priority);
				break;
			case 2:
				std::cout << std::endl;
				std::cout << "Rename task to: ";
				getNameInput(std::cin, name);
				updateTaskName(t, name);
				break;
			case 3:
				std::cout << std::endl;
				std::cout << "Write your comment here: ";
				getline(std::cin, comment);
				updateComment(t, comment);
				break;
			case 4:
				std::cout << std::endl;
				std::cout << "Set status (complete/uncomplete): ";
				getStatusInput(std::cin, status);
				updateStatus(t, status);
				break;
			case 5:
				return;
			default:
				std::cout << "Invalid Input enter 1-5" << std::endl;
			}
		};
	}
	void addTask(const Task& t) {
		taskList.insert(std::pair<std::string, Task>(t.getTaskName(), t));
	}
	void removeTask(const std::string& n) {
		if (!taskExists(n)) {
			std::cout << std::endl << "Task Does Not Exist!" << std::endl;
		}
		else {
			taskList.erase(n);
			std::cout << std::endl << "Task Successfully Removed!" << std::endl;
		}
	}

	void displayTaskListMenu() const{
		std::cout << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << *this;
		if (taskList.empty()) {
			std::cout << "No tasks at this time." << std::endl;
		}
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		displayOptions();
	}
	bool operator<(const TaskList& t) const {
		return date < t.date;
	}
	bool operator>(const TaskList& t) const {
		return t < *this;
	}
	bool operator==(const TaskList& t) const {
		return date == t.date;
	}
	void displayOptions() const {
		std::cout << "1. Add Task" << std::endl;
		std::cout << "2. Remove Task" << std::endl;
		std::cout << "3. Edit Task" << std::endl;
		std::cout << "4. Go Back" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const TaskList& x) {
	os << "Date: " << x.date << std::endl << std::endl;
	std::vector<Task> sortedTaskList;
	for (const auto& pair : x.taskList) {
		sortedTaskList.push_back(pair.second);
	}
	std::sort(sortedTaskList.begin(), sortedTaskList.end(), std::greater<Task>());
	for (const auto& task : sortedTaskList) {
		task.displayTask();
	}
	return os;
}

class TodoListManager {
protected:
	std::map<const Date, TaskList> taskLists;

public:
	TaskList* getList(const Date& d) {
		auto it = taskLists.find(d);
		return (it != taskLists.end()) ? &it->second : nullptr;
	}
	bool taskListExists(const Date& d) {
		return getList(d);
	}
	void createList(const Date& d) {
		if (!d.isValid()) return;

		if (taskListExists(d)) {
			std::cout << std::endl << "List Already Exists!" << std::endl;
		}
		else {
			TaskList taskList(d);
			std::cout << std::endl << "List Successfully Created!" << std::endl;
			addList(taskList);
		}
	}
	void addList(const TaskList& l) {
		taskLists.insert(std::pair<const Date, TaskList>(l.getDate(), l));
	}
	
	void openList(const Date& d) {
		if (!d.isValid()) return;

		TaskList* tl = getList(d);
		if (!tl) {
			std::cout << std::endl << "List Does Not Exist!" << std::endl; 
			return;
		}
		while(true){
			int input;
			std::string name;
				
			tl->displayTaskListMenu();
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cout << "Enter a choice: ";
			getIntegerInput(std::cin, input);

				
			switch (input) {
			case 1:
				std::cout << std::endl;
				std::cout << "Enter task name: ";
				getNameInput(std::cin, name);
				tl->createTask(name);
				break;
			case 2:
				std::cout << std::endl;
				std::cout << "Enter task name: ";
				getNameInput(std::cin, name);
				tl->removeTask(name);
				break;
			case 3:
				std::cout << std::endl;
				std::cout << "Enter task name: ";
				getNameInput(std::cin, name);
				tl->openTaskEditor(name);
				break;
			case 4:
				return;
			default:
				std::cout << "Invalid Input enter 1-4" << std::endl;
			}
		};
	}

	void removeList(const Date& d) {
		if (!d.isValid()) return;

		if (!taskListExists(d)) {
			std::cout << std::endl << "List Does Not Exist!" << std::endl;
		}
		else {
			taskLists.erase(d);
			std::cout << std::endl << "List Successfully Removed!" << std::endl;
		}
	}
	void displayMenu() const {
		std::cout <<
		std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Create, Manage, or Remove To-do Lists" << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		displayOptions();
	}
	void displayOptions() const {
		std::cout << "1. Open List" << std::endl;
		std::cout << "2. Create List" << std::endl;
		std::cout << "3. Remove List" << std::endl;
		std::cout << "4. Exit" << std::endl;
	}
};


int main() {
	// Test Case 1: Basic Year, Month, and Day increments
	Date date1(2, 28, 2020);  // Starting date
	date1.printDate();
	date1 = date1 + Year(3);  // Add 3 years
	date1.printDate();
	date1 = date1 + Month(1); // Add 1 month
	date1.printDate();
	date1 = date1 + Day(28);  // Add 28 days
	date1.printDate();
	// Test Case 2: Handling Month End and Year Increment
	Date date2(12, 31, 2019); // Starting date at the end of year
	date2.printDate();
	date2 = date2 + Year(1);  // Add 1 year
	date2.printDate();
	date2 = date2 + Month(1); // Add 1 month
	date2.printDate();
	date2 = date2 + Day(1);   // Add 1 day
	date2.printDate();
	// Test Case 3: Date Decrement with Negative Values
	Date date3(3, 1, 2024);  // Starting date
	date3.printDate();
	date3 = date3 - Year(1); // Subtract 1 year
	date3.printDate();
	date3 = date3 - Month(11); // Subtract 11 months
	date3.printDate();
	date3 = date3 - Day(30);   // Subtract 30 days
	date3.printDate();

	// Test Case 4: Leap Year Handling
	Date date4(2, 29, 2024); // Leap year date
	date4.printDate();
	date4 = date4 + Year(1);  // Add 1 year, check for leap year roll-over
	date4.printDate();
	date4 = date4 - Month(12); // Subtract 12 months, check for correct roll-back
	date4.printDate();
	date4 = date4 + Day(31);  // Add 31 days to handle month overflow
	date4.printDate();

	// Test Case 5: Large Date Operations (Years, Months, Days)
	Date date5(1, 1, 2000); // Starting date
	date5.printDate();
	date5 = date5 + Year(100);  // Add 100 years
	date5.printDate();
	date5 = date5 + Month(1);   // Add 1 month
	date5.printDate();
	date5 = date5 + Day(29000);    // Add 29 days
	date5.printDate();
	date5 = date5 - Year(4);    // Subtract 4 years
	date5.printDate();
	date5 = date5 - Month(2);   // Subtract 2 months
	date5.printDate();
	date5 = date5 - Day(1);     // Subtract 1 day
	date5.printDate();

	// Test Case 6: Day and Month Modifications
	Date date6(6, 15, 2022); // Starting date
	date6.printDate();
	date6 = date6 + Year(2);  // Add 2 years
	date6.printDate();
	date6 = date6 + Month(7); // Add 7 months
	date6.printDate();
	date6 = date6 + Day(16);  // Add 16 days
	date6.printDate();
	date6 = date6 - Year(0);  // No change in year
	date6.printDate();

	// Test Case 7: Date Edge Case Handling (Negative Day, Month, Year)
	Date date7(1, 1, 2024); // Starting date
	date7.printDate();
	date7 = date7 + Day(-1); // Subtract 1 day (edge case)
	date7.printDate();
	date7 = date7 + Month(-1); // Subtract 1 month (edge case)
	date7.printDate();
	date7 = date7 + Year(-1); // Subtract 1 year (edge case)
	date7.printDate();

	// Test Case 8: Day and Month Rollover
	Date date8(3, 1, 2020); // Starting date
	date8.printDate();
	date8 = date8 + Day(-1); // Subtract 1 day (end of month)
	date8.printDate();
	date8 = date8 + Month(-1); // Subtract 1 month (beginning of year)
	date8.printDate();

	std::cout << "========================================" << std::endl;

	TaskList* taskList1 = new TaskList;
	taskList1->addTask(Task("First Task", 1, "------", "Uncomplete"));
	taskList1->addTask(Task("Second Task", 3, "------", "Uncomplete"));
	taskList1->addTask(Task("Third Task", 2, "------", "Complete"));
	taskList1->addTask(Task("Fourth Task", 1, "------", "Uncomplete"));
	taskList1->addTask(Task("Fifth Task", 3, "------", "Complete"));
	std::cout << "========================================" << std::endl;
	taskList1->displayTaskListMenu();
	
	std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
	std::cout << "=====================================" << std::endl;
	std::cout << "Welcome To Your To-do List Manager!" << std::endl; 
	std::cout << "=====================================" << std::endl;
	std::cout << std::endl;
	
	TodoListManager todoListManager;
	bool running = true;
	while (running) {
		Date date;
		int input;
		
		todoListManager.displayMenu();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Enter a choice: ";
		getIntegerInput(std::cin, input);

		std::cout << std::endl;
		switch (input) {
		case 1:
			std::cout << "What date would you like to access?" << std::endl;
			std::cout << "Enter date: ";
			getDateInput(std::cin, date);
			todoListManager.openList(date);
			break;
		case 2:
			std::cout << "What date would you like to create a new list for?" << std::endl;
			std::cout << "Enter date: ";
			getDateInput(std::cin, date);
			todoListManager.createList(date);
			break;
		case 3: 
			std::cout << "What date would you like to remove a list?" << std::endl;
			std::cout << "Enter date: ";
			getDateInput(std::cin, date);
			todoListManager.removeList(date);
			break;
		case 4: 
			running = false;
			break;
		default:
			std::cout << "Invalid Input enter 1-4" << std::endl;
		}
	}

	return 0;
}