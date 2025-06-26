#include <string>
#include <vector>
#include <algorithm>
#include "Date.util.h"
void getIntegerInput(std::istream& is, int& input) {
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Enter a choice: ";
	is >> input;
	if (std::cin.peek() != '\n') {
		input = -1;
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool getValidDateInput(std::istream& is, Date& input) {
	std::cin >> input;
	if (std::cin.fail() || std::cin.peek() != '\n') {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl << "Invalid Date/Format: type in MM/DD/YYYY or MM-DD-YYYY format" << std::endl;
		return false;
	}
	return true;
}
class Task {
protected:
	int priorityLvl;
	std::string taskName;
	std::string comment;
	bool isComplete;

	friend std::ostream& operator<<(std::ostream& os, const Task& x);
	std::string priority() const{
		switch (priorityLvl) {
		case 1: return "Low";
		case 2: return "Medium";
		case 3: return "High";
		default: return "None";
		}
	}
	std::string status() const {
		return (isComplete) ? "Complete" : "Uncomplete";
	}
public:

	Task(std::string tn = "-------", int pl = 0, std::string c = "-------", bool ic = false) : taskName(tn), priorityLvl(pl), comment(c), isComplete(ic) {}

	int getPriorityLvl() const{
		return priorityLvl;
	}
	std::string getTaskName() const{
		return taskName;
	}
	std::string getComment() const{
		return comment;
	}
	bool getIsComplete() const{
		return isComplete;
	}

	void setIsComplete(const bool& isComplete) {
		this->isComplete = isComplete;
	}
	void setPriorityLvl(const int& priorityLvl) {
		this->priorityLvl = priorityLvl;
	}
	void setTaskName(const std::string& taskName) {
		this->taskName = taskName;
	}
	void setComment(const std::string& comment) {
		this->comment = comment;
	}
	
	bool operator<(const Task& t) const{
		return priorityLvl < t.priorityLvl;
	}
	bool operator>(const Task& t) const{
		return t < *this;
	}
	bool operator==(const Task& t) const {
		return taskName == t.taskName;
	}
	void displayTask() const{
		std::cout << *this << std::endl;
	}
	void displayOptions() const {
		std::cout << "1. Priority Level" << std::endl;
		std::cout << "2. Task Name" << std::endl;
		std::cout << "3. Comment" << std::endl;
		std::cout << "4. Status" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Task& x) {
	os << x.taskName << " : " << x.priority() << " : " << x.comment << " : " << x.status();
	return os;
}

class TaskList{
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

	void createTask(const std::string& n) {
		if (getTask(n)) { 
			std::cout << std::endl << "Task Already Exists!" << std::endl;
		}
		else {
			Task* task = new Task(n);
			std::cout << std::endl << "Task Successfully Created!" << std::endl;
			addTask(*task);
		}
		
	}
	void addTask(const Task& t) {
		taskList.insert(std::pair<std::string, Task>(t.getTaskName(), t));
	}
	void removeTask(const std::string& n) {
		taskList.erase(n);
		std::cout << std::endl << "Task Successfully Removed!" << std::endl;
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
	void createList(const Date& d) {
		if (getList(d)) {
			std::cout << std::endl << "List Already Exists!" << std::endl;
		}
		else {
			TaskList* taskList = new TaskList(d);
			std::cout << std::endl << "List Successfully Created!" << std::endl;
			addList(*taskList);
		}
	}
	void addList(const TaskList& l) {
		taskLists.insert(std::pair<const Date, TaskList>(l.getDate(), l));
	}
	
	void openList(TodoListManager& m, const Date d) {
		bool listIsOpen = false;
		do {
			TaskList* tl = m.getList(d);
			if (tl == nullptr) {
				std::cout << std::endl << "List Does Not Exist!" << std::endl;
			}
			else {
				int input;
				std::string name;
				listIsOpen = true;
				
				tl->displayTaskListMenu();
				getIntegerInput(std::cin, input);

				
				switch (input) {
				case 1:
					std::cout << std::endl;
					std::cout << "Enter task name: ";
					getline(std::cin, name);
					tl->createTask(name);
					break;
				case 2:
					std::cout << std::endl;
					std::cout << "Enter task name: ";
					getline(std::cin, name);
					tl->removeTask(name);
					break;
				case 3:
					break;
				case 4:
					listIsOpen = false;
					break;
				default:
					std::cout << "Invalid Input enter 1-4" << std::endl;
				}
			}
		} while (listIsOpen);
	}

	void removeList(const Date& d) {
		taskLists.erase(d);
		std::cout << std::endl << "List Successfully Removed!" << std::endl;
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
	taskList1->addTask(Task("First Task", 1, "------", false));
	taskList1->addTask(Task("Second Task", 3, "------", false));
	taskList1->addTask(Task("Third Task", 2, "------", true));
	taskList1->addTask(Task("Fourth Task", 1, "------", false));
	taskList1->addTask(Task("Fifth Task", 3, "------", true));
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
		getIntegerInput(std::cin, input);

		std::cout << std::endl;
		switch (input) {
		case 1:
			std::cout << "What date would you like to access?" << std::endl;
			std::cout << "Enter date: ";
			if(getValidDateInput(std::cin, date)) todoListManager.openList(todoListManager, date);
			break;
		case 2:
			std::cout << "What date would you like to create a new list for?" << std::endl;
			std::cout << "Enter date: ";
			if (getValidDateInput(std::cin, date)) todoListManager.createList(date);
			break;
		case 3: 
			std::cout << "What date would you like to remove a list?" << std::endl;
			std::cout << "Enter date: ";
			if (getValidDateInput(std::cin, date)) todoListManager.removeList(date);
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