#include <string>
#include <vector>
#include "Date.util.h"

class Task {
protected:
	int priorityLvl;
	std::string taskName;
	std::string comment;
	bool isComplete;

	friend std::ostream& operator<<(std::ostream& os, const Task& x);
	std::string priority() const{
		switch (priorityLvl) {
		case 2: return "Medium";
		case 3: return "High";
		default: return "Low";
		}
	}
	std::string status() const {
		return (isComplete) ? "Complete" : "Uncomplete";
	}
public:

	Task(int pl = 1, std::string tn = "-------", std::string c = "-------", bool ic = false) : priorityLvl(pl), taskName(tn), comment(c), isComplete(ic) {}

	int getPriorityLvl() {
		return priorityLvl;
	}
	std::string getTaskName() {
		return taskName;
	}
	std::string getComment() {
		return comment;
	}
	bool getIsComplete() {
		return isComplete;
	}

	void setIsComplete(bool& isComplete) {
		this->isComplete = isComplete;
	}
	void setPriorityLvl(int& priorityLvl) {
		this->priorityLvl = priorityLvl;
	}
	void setTaskName(std::string& taskName) {
		this->taskName = taskName;
	}
	void setComment(std::string& comment) {
		this->comment = comment;
	}
	
	bool operator<(Task& t) {
		return priorityLvl < t.priorityLvl;
	}
	bool operator>(Task& t) {
		return t < *this;
	}
	void displayTask() {
		std::cout << *this << std::endl;
	}

};

std::ostream& operator<<(std::ostream& os, const Task& x) {
	os << x.taskName << " : " << x.priority() << " : " << x.comment << " : " << x.status();
	return os;
}

class DaysTasks {
protected:
	Date date;
	std::vector<Task> taskList;

	void swap(Task& t1, Task& t2) {
		Task t = t1;
		t1 = t2;
		t2 = t;
	}
	void organize(std::vector<Task>& tl) {
		bool swapped;
		do {
			swapped = false;
			for (int i = 0; i < tl.size() - 1; i++) {
				if (tl[i] < tl[i + 1]) {
					swap(tl[i], tl[i + 1]);
					swapped = true;
				}
			}
		} while (swapped);
	}
public:
	void addTask(const Task& t) {
		taskList.push_back(t);
		organize(taskList);
	}
	void removeTask(Task& t) {
		
	}
	void editTask(Task& t) {

	}
	void displayTaskList() {
		for (int i = 0; i < taskList.size(); i++) {
			taskList[i].displayTask();
		}
	}
};

class TodoListManager{
protected:
	std::vector<DaysTasks> lists;
public:
	void addList(DaysTasks& l) {

	}
	void removeList(DaysTasks& l) {

	}
	void editList(DaysTasks& l) {

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

	DaysTasks taskList1;
	taskList1.addTask(Task(1, "First Task", "------", false));
	taskList1.addTask(Task(3, "Second Task", "------", false));
	taskList1.addTask(Task(2, "Third Task", "------", true));
	taskList1.addTask(Task(1, "Fourth Task", "------", false));
	taskList1.addTask(Task(3, "Fifth Task", "------", true));
	taskList1.displayTaskList();
	return 0;
}