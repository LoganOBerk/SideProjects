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
	explicit Month(int v) : val(v) {}
};

struct Day {
	int val;
	explicit Day() : val(1) {}
	explicit Day(int v) : val(v) {}
};

struct Year {
	int val;
	explicit Year() : val(1) {}
	explicit Year(int v) : val(v) {}
};
class Date {
protected:
	int day;
	int month;
	int year;

	
	virtual friend std::ostream& operator<<(std::ostream&, const Date&);

	virtual bool isLeapYear(const int y);
	virtual int normalizeDay(const int d, const int dMax);
	virtual int normalizeMonth(const int m);
	virtual int daysInMonth(const int m, const int y);
	virtual int daysInYear(const int y);
	virtual int monthRollover(const int m);
	
	virtual void adjustDY(int& d, int& y);
	virtual void adjustDM(int& m, int& d, const int y);
	virtual void adjustMDY(int& m, int& d, int& y);



public:
	Date() : month(1), day(1), year(1) {}
	Date(int m, int d, int y) : month(m), day(d), year(y) {
		if (y < 1) { month = 1, day = 1, year = 1;}
		if (m < 1 || m > 12) throw std::invalid_argument("Months are between 1-12");
		if (daysInMonth(m, y) < d) throw std::invalid_argument("Invalid number of days for month");
	}

	virtual void printDate();

	virtual bool operator<(const Date&);
	virtual bool operator>(const Date&);
	virtual bool operator==(const Date&);
	virtual bool operator<=(const Date&);
	virtual bool operator>=(const Date&);

	virtual Date& operator=(const Date&);
	
	virtual Date operator+(const Month&);
	virtual Date operator-(const Month&);
	virtual Date& operator+=(const Month&);
	virtual Date& operator-=(const Month&);

	virtual Date operator+(const Day&);
	virtual Date operator-(const Day&);
	virtual Date& operator+=(const Day&);
	virtual Date& operator-=(const Day&);
	
	virtual Date operator+(const Year&);
	virtual Date operator-(const Year&);
	virtual Date& operator+=(const Year&);
	virtual Date& operator-=(const Year&);

	virtual Date& operator++();
	virtual Date& operator--();
	virtual Date operator++(int);
	virtual Date operator--(int);
	
	

};

//INPUT: y, a year
//OUTPUT: true or false
//PRECONDITION: none
//POSTCONDITION: returns true if the given year is valid and a leap year
bool Date::isLeapYear(const int y) {
	if (y < 1) return false;
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//INPUT:d a given day, mMax maximum days in the month
//OUTPUT: the proper number of days in the month
//PRECONDITION: day is properly set for last year
//POSTCONDITION: day is properly set for current year
int Date::normalizeDay(const int d, const int mMax) {
	return (mMax < d) ? mMax : d;
}

//INPUT: m, a number of months 
//OUTPUT: the month number (1-12)
//PRECONDITION: the amount of months to add/subtract was 
// properly added or subtracted to/from the previous month
//POSTCONDITION: the month is normalized to its proper number (1 - 12)
int Date::normalizeMonth(const int m) {
	return (m % 12 != 0) ? modulus(m, 12) : 12;
}

//INPUT: m, a number of months 
//OUTPUT: the amount of months to roll forward or backward
//PRECONDITION: the amount of months to add/subtract was 
// properly added or subtracted to/from the previous month
//POSTCONDITION: the proper amount of months to roll back or forward is set
int Date::monthRollover(const int m) {
	if (m == 0) return -1;
	if (m == 12) return 0;
	return (int)floor((float)m / 12);
}

//INPUT: m, a month; y, a year
//OUTPUT: the maximum amount of days in a given month & year
//PRECONDITION: the amount of months is set properly (even if overflow or underflow)
//POSTCONDITION: the maximum amount of days in the given month and year
int Date::daysInMonth(const int m, const int y) {
	int monthMax[12] = { 31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return monthMax[normalizeMonth(m) - 1];
}

//INPUT: y, a year
//OUTPUT: days in the year
//PRECONDITION: year is properly set
//POSTCONDITION: maximum days in the current year is set 
int Date::daysInYear(const int y) {
	return isLeapYear(y) ? 366 : 365;
}

//INPUT: d, day, y year
//OUTPUT: none
//PRECONDITION: days are properly added/subtracted from the previous day 
//POSTCONDITION: number of whole year days is added or subtracted from d,
// also adding or subtracting from the current year. Day is set to a number
// of days less than the updated years maximum or greater than the updated years minimum 
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

//INPUT: 
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
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

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
void Date::adjustMDY(int& m, int& d, int& y) {
	y += monthRollover(m);
	m = normalizeMonth(m);
	d = normalizeDay(d, daysInMonth(m, y));
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator+(const Day& x) {
	int m = month;
	int d = day + x.val;
	int y = year;

	adjustDY(d, y);
	adjustDM(m, d, y);
	adjustMDY(m, d, y);


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

	adjustMDY(m, d, y);

	return Date(m, d, y);
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator+(const Year& x) {
	int m = month;
	int d = day;
	int y = year + x.val;

	adjustMDY(m, d, y);

	return Date(m, d, y);
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator=(const Date& x) {
	month = x.month;
	day = x.day;
	year = x.year;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator-(const Month& x) {
	return *this + Month(-x.val);
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator-(const Day& x) {
	return *this + Day(-x.val);
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator-(const Year& x) {
	return *this + Year(-x.val);
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
bool Date::operator==(const Date& x) {
	bool yearsAreEqual = (year == x.year);
	bool monthsAreEqual = (month == x.month);
	bool daysAreEqual = (day == x.day);

	return yearsAreEqual && monthsAreEqual && daysAreEqual;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
bool Date::operator<(const Date& x) {
	if (year != x.year) return year < x.year;
	if (month != x.month) return month < x.month;
	if (day != x.day) return day < x.day;
	return false;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
bool Date::operator>(const Date& x) {
	return (Date)x < *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
bool Date::operator<=(const Date& x) {
	return *this < x || *this == x;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
bool Date::operator>=(const Date& x) {
	return *this > x || *this == x;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator+=(const Month& x) {
	*this = *this + x;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator+=(const Day& x) {
	*this = *this + x;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator+=(const Year& x) {
	*this = *this + x;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator-=(const Month& x) {
	*this = *this - x;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator-=(const Day& x) {
	*this = *this - x;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator-=(const Year& x) {
	*this = *this - x;
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator++() {
	*this += Day(1);
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator++(int) {
	Date cur = *this;
	*this += Day(1);
	return cur;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date& Date::operator--() {
	*this -= Day(1);
	return *this;
}

//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
Date Date::operator--(int) {
	Date cur = *this;
	*this -= Day(1);
	return cur;
}

std::ostream& operator<<(std::ostream& os, const Date& x) {
	std::string monthName[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	os << monthName[x.month - 1] << ' ';
	os << std::setw(2) << std::setfill('0') << x.day << ", ";
	os << std::setw(4) << std::setfill('0') << x.year;
	return os;
}
//INPUT:
//OUTPUT:
//PRECONDITION:
//POSTCONDITION:
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