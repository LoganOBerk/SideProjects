#include <iostream>
#include <iomanip>
#include "Date.util.h"


//INPUT: integers representing a m, month; d, day; y, year
//OUTPUT: a Date object, or throws an exception if input is invalid
//PRECONDITION: None (constructor handles validation internally)
//POSTCONDITION: Constructs a valid Date or throws std::invalid_argument
Date::Date(int m, int d, int y) : month(m), day(d), year(y) {
	if (y < 1) { month = 1, day = 1, year = 1; }
	if (m < 1 || m > 12) throw std::invalid_argument("Months are between 1-12");
	if (daysInMonth(m, y) < d) throw std::invalid_argument("Invalid number of days for month");
}
// INPUT: None
// OUTPUT: Integer representing the month of this Date
// PRECONDITION: This Date object is valid and constructed
// POSTCONDITION: No modification to the object; returns stored month value
int Date::getMonth() const{
	return month;
}
// INPUT: None
// OUTPUT: Integer representing the day of this Date
// PRECONDITION: This Date object is valid and constructed
// POSTCONDITION: No modification to the object; returns stored day value
int Date::getDay() const{
	return day;
}
// INPUT: None
// OUTPUT: Integer representing the year of this Date
// PRECONDITION: This Date object is valid and constructed
// POSTCONDITION: No modification to the object; returns stored year value
int Date::getYear() const{
	return year;
}
//INPUT: y, a year
//OUTPUT: true or false
//PRECONDITION: none
//POSTCONDITION: returns true if the given year is valid and a leap year
bool Date::isLeapYear(const int y) const{
	if (y < 1) return false;
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//INPUT: d, a given day; mMax, the maximum number of days in the current month
//OUTPUT: a valid day value, not exceeding dMax
//PRECONDITION: d and dMax are valid integers
//POSTCONDITION: returns d if within range; otherwise returns mMax
int Date::normalizeDay(const int d, const int mMax) const{
	return (mMax < d) ? mMax : d;
}

//INPUT: m, an integer representing a month (can be out of bounds)
//OUTPUT: a valid month in the range 1-12
//PRECONDITION: m may be outside the standard month range
//POSTCONDITION: returns a valid normalized month value
int Date::normalizeMonth(const int m) const{
	return (m % 12 != 0) ? modulus(m, 12) : 12;
}

//INPUT: m, an integer representing a month (can be out of bounds)
//OUTPUT: the number of years to adjust based on month overflow or underflow
//PRECONDITION: m is the result of month arithmetic (may overflow)
//POSTCONDITION: returns how many years the month change rolls over
int Date::monthRollover(const int m) const{
	if (m == 0) return -1;
	if (m == 12) return 0;
	return (int)floor((float)m / 12);
}

//INPUT: m, month; y, year
//OUTPUT: number of days in the given month of the given year
//PRECONDITION: m and y must be valid month and year values
//POSTCONDITION: returns the correct number of days in the specified month
int Date::daysInMonth(const int m, const int y) const{
	int monthMax[12] = { 31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return monthMax[normalizeMonth(m) - 1];
}

//INPUT: y, a year
//OUTPUT: number of days in that year (365 or 366)
//PRECONDITION: y is a valid positive integer
//POSTCONDITION: returns 365 for normal years, 366 for leap years
int Date::daysInYear(const int y) const{
	return isLeapYear(y) ? 366 : 365;
}

//INPUT: d, a number of days; y, a reference year
//OUTPUT: none
//PRECONDITION: d may exceed or be less than the number of days in a year
//POSTCONDITION: adjusts y and d so d fits within the updated year
void Date::adjustDY(int& d, int& y) const{
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
void Date::adjustMD(int& m, int& d, const int y) const{
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
void Date::adjustMDY(int& m, int& d, int& y) const{
	y += monthRollover(m);
	m = normalizeMonth(m);
	d = normalizeDay(d, daysInMonth(m, y));
}

//INPUT: x, a Day object
//OUTPUT: a new Date incremented by x days
//PRECONDITION: current Date is valid
//POSTCONDITION: returns a new Date with x days added
Date Date::operator+(const Day& x) const{
	int m = month;
	int d = day + x.val;
	int y = year;

	adjustDY(d, y);
	adjustMD(m, d, y);
	adjustMDY(m, d, y);

	return Date(m, d, y);
}

//INPUT: x, a Month object
//OUTPUT: a new Date incremented by x months
//PRECONDITION: current Date is valid
//POSTCONDITION: returns a new Date with x months added
Date Date::operator+(const Month& x) const{
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
Date Date::operator+(const Year& x) const{
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
Date Date::operator-(const Month& x) const{
	return *this + Month(-x.val);
}

//INPUT/OUTPUT/PRE/POST: identical to corresponding addition operator
Date Date::operator-(const Day& x) const{
	return *this + Day(-x.val);
}

//INPUT/OUTPUT/PRE/POST: identical to corresponding addition operator
Date Date::operator-(const Year& x) const{
	return *this + Year(-x.val);
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if Dates are equal, false otherwise
bool Date::operator==(const Date& x) const{
	bool yearsAreEqual = (year == x.year);
	bool monthsAreEqual = (month == x.month);
	bool daysAreEqual = (day == x.day);

	return yearsAreEqual && monthsAreEqual && daysAreEqual;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is less than x
bool Date::operator<(const Date& x) const{
	if (year != x.year) return year < x.year;
	if (month != x.month) return month < x.month;
	if (day != x.day) return day < x.day;
	return false;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is greater than x
bool Date::operator>(const Date& x) const{
	return (Date)x < *this;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is less than or equal to x
bool Date::operator<=(const Date& x) const{
	return *this < x || *this == x;
}

//INPUT: x, a Date
//OUTPUT: true or false
//PRECONDITION: both Dates are valid
//POSTCONDITION: returns true if this Date is greater than or equal to x
bool Date::operator>=(const Date& x) const{
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
	std::string monthName[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	os << monthName[x.month - 1] << ' ';
	os << std::setw(2) << std::setfill('0') << x.day << ", ";
	os << std::setw(4) << std::setfill('0') << x.year;
	return os;
}

//INPUT: none
//OUTPUT: formatted Date to standard output
//PRECONDITION: Date is valid
//POSTCONDITION: displays Date using operator<<
void Date::printDate() const{
	std::cout << *this << std::endl;
}

