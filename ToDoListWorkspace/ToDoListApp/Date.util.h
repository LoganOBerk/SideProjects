#include <iostream>
#include <iomanip>
#include <gtest/gtest.h>
#include "Math.util.h"

#ifndef DATE_UTIL_H
#define DATE_UTIL_H
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
		bool isLeapYear(const int y) const;
		int normalizeDay(const int d, const int dMax);
		int normalizeMonth(const int m);
		int daysInMonth(const int m, const int y);
		int daysInYear(const int y);
		int monthRollover(const int m);
		void adjustDY(int& d, int& y);
		void adjustMD(int& m, int& d, const int y);
		void adjustMDY(int& m, int& d, int& y);
		
	public:
		

		// Constructors ensure validity of initialized dates
		Date() : month(1), day(1), year(1) {}
		Date(int m, int d, int y);

		// Output and utility
		void printDate();
		int getMonth() const;
		int getDay() const;
		int getYear() const;

		// Comparison operators
		bool operator<(const Date&);
		bool operator>(const Date&);
		bool operator==(const Date&) const;
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
#endif