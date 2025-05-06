#include <iostream>
#include <iomanip>

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
int modulus(const int& m, const int& n) {
	return ((m % n) + n) % n;
}
struct Month {
	int val;
	explicit Month() : val(1) {}
	explicit Month(int v) : val(v){}
};

struct Day {
	int val;
	explicit Day() : val(1) {}
	explicit Day(int v) : val(v) {}
};

struct Year {
	int val;
	explicit Year() : val(1) {}
	explicit Year(int v) : val(v){}
};
class Date {
	private:
		unsigned int day;
		unsigned int month;
		unsigned int year;
		
		
		static bool isLeapYear(const int y);
		static int dayOfMonth(int m, const int y);
		static Date adjustedDate(int m, int d, int y);
		static int normalizeMonth(const int m);
		static int normalizeDay(const int d, const int dMax);
		static int monthsToYears(const int m);
		

	public:
		Date() : month(1), day(1), year(1){}
		Date(unsigned int m, unsigned int d, unsigned int y) : month(m), day(d), year(y) {
			if (m < 1 || m > 12) throw std::invalid_argument("Months are between 1-12");
			if (dayOfMonth(m, y) < d) throw std::invalid_argument("Invalid number of days for month");
		}
		
		void printDate();
		
		Date operator+(const Month&);
		Date operator+(const Day&);
		Date operator+(const Year&);
		Date operator-(const Month&);
		Date operator-(const Day&);
		Date operator-(const Year&);

};
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
bool Date::isLeapYear(const int y) {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
int Date::normalizeMonth(const int m) {
	return (m % 12 != 0) ? modulus(m, 12) : 12;
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
int Date::normalizeDay(const int d, const int dMax) {
	return (dMax < d) ? dMax : d;
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
int Date::monthsToYears(const int m) {
	if (m == 0) return -1;
	if (m == 12) return 0;
	return floor((float)m / 12);
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
int Date::dayOfMonth(int m, const int y) {
	int monthMax[12] = { 31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return monthMax[m - 1];
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::adjustedDate(int m, int d, int y) {
	int newMonth = normalizeMonth(m);
	int newYear = y + monthsToYears(m);
	int dMax = dayOfMonth(newMonth, newYear);
	int newDay = normalizeDay(d, dMax);

	m = newMonth;
	y = newYear;
	d = newDay;

	if (newYear <= 0) return Date(1, 1, 1);
	return Date(m, d, y);
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator+(const Month& x) {
	int m = month + x.val;
	int d = day;
	int y = year;
	while (m > 12) {
		m -= 12;
		y++;
	}
	return adjustedDate(m, d, y);
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator+(const Day& x) {
	int m = month;
	int d = day + x.val;
	int y = year;
	int mMax = dayOfMonth(m, y);
	while (d > mMax) {
		d -= mMax;
		m++;
		mMax = dayOfMonth(m, y);
	}
	while (d <= 0) {
		m--;
		mMax = dayOfMonth(m, y);
		d += mMax;
	}
	return adjustedDate(m, d, y);
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator+(const Year& x) {
	int m = month;
	int d = day;
	int y = year + x.val;
	return adjustedDate(m, d, y);
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator-(const Month& x) {
	return *this + Month(-x.val);
};
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator-(const Day& x) {
	return *this + Day(-x.val);
};
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator-(const Year& x) {
	return *this + Year(-x.val);
};
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
void Date::printDate() {
	std::cout << std::setw(2) << std::setfill('0') << month << "-";
	std::cout << std::setw(2) << std::setfill('0') << day << "-";
	std::cout << std::setw(4) << std::setfill('0') << year << std::endl;
}


int main(){
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
	date5 = date5 + Day(29);    // Add 29 days
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



	return 0;
}