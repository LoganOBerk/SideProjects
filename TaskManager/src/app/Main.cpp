#include "TaskManagerApp.h"
void testing(bool runTest) {
	if (runTest) {
		// Test Case 1: Basic Year, Month, and Day increments
		Date date1(2, 28, 2020);  // Starting date
		std::cout << date1 << std::endl;
		date1 = date1 + Year(3);  // Add 3 years
		std::cout << date1 << std::endl;
		date1 = date1 + Month(1); // Add 1 month
		std::cout << date1 << std::endl;
		date1 = date1 + Day(28);  // Add 28 days
		std::cout << date1 << std::endl;
		// Test Case 2: Handling Month End and Year Increment
		Date date2(12, 31, 2019); // Starting date at the end of year
		std::cout << date2 << std::endl;
		date2 = date2 + Year(1);  // Add 1 year
		std::cout << date2 << std::endl;
		date2 = date2 + Month(1); // Add 1 month
		std::cout << date2 << std::endl;
		date2 = date2 + Day(1);   // Add 1 day
		std::cout << date2 << std::endl;
		// Test Case 3: Date Decrement with Negative Values
		Date date3(3, 1, 2024);  // Starting date
		std::cout << date3 << std::endl;
		date3 = date3 - Year(1); // Subtract 1 year
		std::cout << date3 << std::endl;
		date3 = date3 - Month(11); // Subtract 11 months
		std::cout << date3 << std::endl;
		date3 = date3 - Day(30);   // Subtract 30 days
		std::cout << date3 << std::endl;

		// Test Case 4: Leap Year Handling
		Date date4(2, 29, 2024); // Leap year date
		std::cout << date4 << std::endl;
		date4 = date4 + Year(1);  // Add 1 year, check for leap year roll-over
		std::cout << date4 << std::endl;
		date4 = date4 - Month(12); // Subtract 12 months, check for correct roll-back
		std::cout << date4 << std::endl;
		date4 = date4 + Day(31);  // Add 31 days to handle month overflow
		std::cout << date4 << std::endl;

		// Test Case 5: Large Date Operations (Years, Months, Days)
		Date date5(1, 1, 2000); // Starting date
		std::cout << date5 << std::endl;
		date5 = date5 + Year(100);  // Add 100 years
		std::cout << date5 << std::endl;
		date5 = date5 + Month(1);   // Add 1 month
		std::cout << date5 << std::endl;
		date5 = date5 + Day(29000);    // Add 29 days
		std::cout << date5 << std::endl;
		date5 = date5 - Year(4);    // Subtract 4 years
		std::cout << date5 << std::endl;
		date5 = date5 - Month(2);   // Subtract 2 months
		std::cout << date5 << std::endl;
		date5 = date5 - Day(1);     // Subtract 1 day
		std::cout << date5 << std::endl;

		// Test Case 6: Day and Month Modifications
		Date date6(6, 15, 2022); // Starting date
		std::cout << date6 << std::endl;
		date6 = date6 + Year(2);  // Add 2 years
		std::cout << date6 << std::endl;
		date6 = date6 + Month(7); // Add 7 months
		std::cout << date6 << std::endl;
		date6 = date6 + Day(16);  // Add 16 days
		std::cout << date6 << std::endl;
		date6 = date6 - Year(0);  // No change in year
		std::cout << date6 << std::endl;

		// Test Case 7: Date Edge Case Handling (Negative Day, Month, Year)
		Date date7(1, 1, 2024); // Starting date
		std::cout << date7 << std::endl;
		date7 = date7 + Day(-1); // Subtract 1 day (edge case)
		std::cout << date7 << std::endl;
		date7 = date7 + Month(-1); // Subtract 1 month (edge case)
		std::cout << date7 << std::endl;
		date7 = date7 + Year(-1); // Subtract 1 year (edge case)
		std::cout << date7 << std::endl;

		// Test Case 8: Day and Month Rollover
		Date date8(3, 1, 2020); // Starting date
		std::cout << date8 << std::endl;
		date8 = date8 + Day(-1); // Subtract 1 day (end of month)
		std::cout << date8 << std::endl;
		date8 = date8 + Month(-1); // Subtract 1 month (beginning of year)
		std::cout << date8 << std::endl;

		std::cout << "========================================" << std::endl;

		TaskList* taskList1 = new TaskList;
		taskList1->addTask(Task("First Task", "low", "------", "Uncomplete"));
		taskList1->addTask(Task("Second Task", "high", "------", "Uncomplete"));
		taskList1->addTask(Task("Third Task", "medium", "------", "Complete"));
		taskList1->addTask(Task("Fourth Task", "low", "------", "Uncomplete"));
		taskList1->addTask(Task("Fifth Task", "high", "------", "Complete"));
		std::cout << "========================================" << std::endl;
		UI::displayTaskListMenu(*taskList1);
	}
}

int main() {
	testing(false);

	TaskManagerApp app;
	app.init();
	app.run();
	app.exit();
	return 0;
}