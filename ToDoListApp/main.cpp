#include <iostream>
#include <iomanip>

//INPUT: m, an integer dividend; n, an integer divisor
//OUTPUT: the modulus result, always non-negative
//PRECONDITION: n ? 0
//POSTCONDITION: returns a non-negative result of m mod n
int modulus(const int& m, const int& n) {
	return ((m % n) + n) % n;
}

// PURPOSE: Represents a number of months to be added or subtracted from a Date.
// Used in operator overloading for intuitive date manipulation with months.
struct Month {
	int val;
	explicit Month() : val(1) {}
	explicit Month(int v) : val(v) {}
};

// PURPOSE: Represents a number of days to be added or subtracted from a Date.
// Enables clear and type-safe day-based arithmetic on Date objects.
struct Day {
	int val;
	explicit Day() : val(1) {}
	explicit Day(int v) : val(v) {}
};

// PURPOSE: Represents a number of years to be added or subtracted from a Date.
// Used for clear and expressive year-level operations with Date objects.
struct Year {
	int val;
	explicit Year() : val(1) {}
	explicit Year(int v) : val(v) {}
};

// PURPOSE: Encapsulates a full calendar date with day, month, and year.
// Supports arithmetic and comparison operations, including handling leap years,
// normalization, and rollover for realistic calendar logic.
class Date {
protected:
	int day;
	int month;
	int year;

	// Internal helper functions for leap year checks, normalization,
	// rollover handling, and adjustment of day/month/year components.
	friend std::ostream& operator<<(std::ostream&, const Date&);
	bool isLeapYear(const int y);
	int normalizeDay(const int d, const int dMax);
	int normalizeMonth(const int m);
	int daysInMonth(const int m, const int y);
	int daysInYear(const int y);
	int monthRollover(const int m);
	void adjustDY(int& d, int& y);
	void adjustDM(int& m, int& d, const int y);
	void adjustMDY(int& m, int& d, int& y);


public:
	// Constructors ensure validity of initialized dates
	Date() : month(1), day(1), year(1) {}
	Date(int m, int d, int y);

	// Output and utility
	virtual void printDate();

	// Comparison operators
	bool operator<(const Date&);
	bool operator>(const Date&);
	bool operator==(const Date&);
	bool operator<=(const Date&);
	bool operator>=(const Date&);

	// Assignment and arithmetic operators
	Date& operator=(const Date&);
	Date operator+(const Month&);
	Date operator-(const Month&);
	Date& operator+=(const Month&);
	Date& operator-=(const Month&);
	Date operator+(const Day&);
	Date operator-(const Day&);
	Date& operator+=(const Day&);
	Date& operator-=(const Day&);
	Date operator+(const Year&);
	Date operator-(const Year&);
	Date& operator+=(const Year&);
	Date& operator-=(const Year&);

	// Increment and decrement (prefix and postfix)
	Date& operator++();
	Date& operator--();
	Date operator++(int);
	Date operator--(int);
	
	

};

//INPUT: integers representing a m, month; d, day; y, year
//OUTPUT: a Date object, or throws an exception if input is invalid
//PRECONDITION: None (constructor handles validation internally)
//POSTCONDITION: Constructs a valid Date or throws std::invalid_argument
Date::Date(int m, int d, int y) : month(m), day(d), year(y) {
	if (y < 1) { month = 1, day = 1, year = 1; }
	if (m < 1 || m > 12) throw std::invalid_argument("Months are between 1-12");
	if (daysInMonth(m, y) < d) throw std::invalid_argument("Invalid number of days for month");
}

//INPUT: y, a year
//OUTPUT: true or false
//PRECONDITION: none
//POSTCONDITION: returns true if the given year is valid and a leap year
bool Date::isLeapYear(const int y) {
	if (y < 1) return false;
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//INPUT: d, a given day; mMax, the maximum number of days in the current month
//OUTPUT: a valid day value, not exceeding dMax
//PRECONDITION: d and dMax are valid integers
//POSTCONDITION: returns d if within range; otherwise returns mMax
int Date::normalizeDay(const int d, const int mMax) {
	return (mMax < d) ? mMax : d;
}

//INPUT: m, an integer representing a month (can be out of bounds)
//OUTPUT: a valid month in the range 1-12
//PRECONDITION: m may be outside the standard month range
//POSTCONDITION: returns a valid normalized month value
int Date::normalizeMonth(const int m) {
	return (m % 12 != 0) ? modulus(m, 12) : 12;
}

//INPUT: m, an integer representing a month (can be out of bounds)
//OUTPUT: the number of years to adjust based on month overflow or underflow
//PRECONDITION: m is the result of month arithmetic (may overflow)
//POSTCONDITION: returns how many years the month change rolls over
int Date::monthRollover(const int m) {
	if (m == 0) return -1;
	if (m == 12) return 0;
	return (int)floor((float)m / 12);
}

//INPUT: m, month; y, year
//OUTPUT: number of days in the given month of the given year
//PRECONDITION: m and y must be valid month and year values
//POSTCONDITION: returns the correct number of days in the specified month
int Date::daysInMonth(const int m, const int y) {
	int monthMax[12] = { 31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return monthMax[normalizeMonth(m) - 1];
}

//INPUT: y, a year
//OUTPUT: number of days in that year (365 or 366)
//PRECONDITION: y is a valid positive integer
//POSTCONDITION: returns 365 for normal years, 366 for leap years
int Date::daysInYear(const int y) {
	return isLeapYear(y) ? 366 : 365;
}

//INPUT: d, a number of days; y, a reference year
//OUTPUT: none
//PRECONDITION: d may exceed or be less than the number of days in a year
//POSTCONDITION: adjusts y and d so d fits within the updated year
void Date::adjustDY(int& d, int& y) {
	int dMax = daysInYear(y);

	while (d > dMax) {
		d -= dMax;
		y++;
		dMax = daysInYear(y);
	}

	while (d <= -dMax) {
		y--;
		dMax = daysInYear(y);
		d += dMax;
	}
}

//INPUT: m, a month; d, a day; y, a year
//OUTPUT: none
//PRECONDITION: y has already been adjusted
//POSTCONDITION: adjusts m and d so they represent a valid date or, d may overflow or underflow a month
void Date::adjustDM(int& m, int& d, const int y) {
	int mMax = daysInMonth(m, y);
	while (d > mMax) {
		d -= mMax;
		m++;
		mMax = daysInMonth(m, y);
	}
	while (d <= 0) {
		m--;
		mMax = daysInMonth(m, y);
		d += mMax;
	}
}

//INPUT: m, a month; d, a day; y, a year
//OUTPUT: none
//PRECONDITION: m and d may be out of bounds
//POSTCONDITION: sets m, d, y to represent a normalized, valid date
void Date::adjustMDY(int& m, int& d, int& y) {
	y += monthRollover(m);
	m = normalizeMonth(m);
	d = normalizeDay(d, daysInMonth(m, y));
}

//INPUT: x, a Day object
//OUTPUT: a new Date incremented by x days
//PRECONDITION: current Date is valid
//POSTCONDITION: returns a new Date with x days added
Date Date::operator+(const Day& x) {
	int m = month;
	int d = day + x.val;
	int y = year;

	adjustDY(d, y);
	adjustDM(m, d, y);
	adjustMDY(m, d, y);

	return Date(m, d, y);
}

//INPUT: x, a Month object
//OUTPUT: a new Date incremented by x months
//PRECONDITION: current Date is valid
//POSTCONDITION: returns a new Date with x months added
Date Date::operator+(const Month& x) {
	int m = month + x.val;
	int d = day;
	int y = year;

	adjustMDY(m, d, y);

	return Date(m, d, y);
}

//INPUT: x, a Year object
//OUTPUT: a new Date incremented by x years
//PRECONDITION: current Date is valid
//POSTCONDITION: returns a new Date with x years added
Date Date::operator+(const Year& x) {
	int m = month;
	int d = day;
	int y = year + x.val;

	adjustMDY(m, d, y);

	return Date(m, d, y);
}

//INPUT: x, a Date
//OUTPUT: reference to this Date after assignment
//PRECONDITION: x is a valid Date
//POSTCONDITION: this Date takes on x's values
Date& Date::operator=(const Date& x) {
	month = x.month;
	day = x.day;
	year = x.year;
	return *this;
}

//INPUT/OUTPUT/PRE/POST: identical to corresponding addition operator
Date Date::operator-(const Month& x) {
	return *this + Month(-x.val);
}

//INPUT/OUTPUT/PRE/POST: identical to corresponding addition operator
Date Date::operator-(const Day& x) {
	return *this + Day(-x.val);
}

//INPUT/OUTPUT/PRE/POST: identical to corresponding addition operator
Date Date::operator-(const Year& x) {
	return *this + Year(-x.val);
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if Dates are equal, false otherwise
bool Date::operator==(const Date& x) {
	bool yearsAreEqual = (year == x.year);
	bool monthsAreEqual = (month == x.month);
	bool daysAreEqual = (day == x.day);

	return yearsAreEqual && monthsAreEqual && daysAreEqual;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is less than x
bool Date::operator<(const Date& x) {
	if (year != x.year) return year < x.year;
	if (month != x.month) return month < x.month;
	if (day != x.day) return day < x.day;
	return false;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is greater than x
bool Date::operator>(const Date& x) {
	return (Date)x < *this;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is less than or equal to x
bool Date::operator<=(const Date& x) {
	return *this < x || *this == x;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is greater than or equal to x
bool Date::operator>=(const Date& x) {
	return *this > x || *this == x;
}

//INPUT/OUTPUT/PRE/POST: as described in binary operator equivalents
Date& Date::operator+=(const Month& x) {
	*this = *this + x;
	return *this;
}

//INPUT/OUTPUT/PRE/POST: as described in binary operator equivalents
Date& Date::operator+=(const Day& x) {
	*this = *this + x;
	return *this;
}

//INPUT/OUTPUT/PRE/POST: as described in binary operator equivalents
Date& Date::operator+=(const Year& x) {
	*this = *this + x;
	return *this;
}

//INPUT/OUTPUT/PRE/POST: as described in binary operator equivalents
Date& Date::operator-=(const Month& x) {
	*this = *this - x;
	return *this;
}

//INPUT/OUTPUT/PRE/POST: as described in binary operator equivalents
Date& Date::operator-=(const Day& x) {
	*this = *this - x;
	return *this;
}

//INPUT/OUTPUT/PRE/POST: as described in binary operator equivalents
Date& Date::operator-=(const Year& x) {
	*this = *this - x;
	return *this;
}

//INPUT: none
//OUTPUT: updated Date incremented by one day (prefix)
//PRECONDITION: Date is valid
//POSTCONDITION: increments Date and returns updated object
Date& Date::operator++() {
	*this += Day(1);
	return *this;
}

//INPUT: none
//OUTPUT: original Date before increment (postfix)
//PRECONDITION: Date is valid
//POSTCONDITION: increments Date, returns value before change
Date Date::operator++(int) {
	Date cur = *this;
	*this += Day(1);
	return cur;
}

//INPUT: none
//OUTPUT: updated Date decremented by one day (prefix)
//PRECONDITION: Date is valid
//POSTCONDITION: decrements Date and returns updated object
Date& Date::operator--() {
	*this -= Day(1);
	return *this;
}

//INPUT: none
//OUTPUT: original Date before decrement (postfix)
//PRECONDITION: Date is valid
//POSTCONDITION: decrements Date, returns value before change
Date Date::operator--(int) {
	Date cur = *this;
	*this -= Day(1);
	return cur;
}

//INPUT: os, output stream; x, Date to print
//OUTPUT: formatted output to stream
//PRECONDITION: Date is valid
//POSTCONDITION: prints Date in "MonthName DD, YYYY" format
std::ostream& operator<<(std::ostream& os, const Date& x) {
	std::string monthName[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	os << monthName[x.month - 1] << ' ';
	os << std::setw(2) << std::setfill('0') << x.day << ", ";
	os << std::setw(4) << std::setfill('0') << x.year;
	return os;
}

//INPUT: none
//OUTPUT: formatted Date to standard output
//PRECONDITION: Date is valid
//POSTCONDITION: displays Date using operator<<
void Date::printDate() {
	std::cout << *this << std::endl;
}


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



	return 0;
}