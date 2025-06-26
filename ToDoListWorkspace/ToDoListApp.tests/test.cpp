#include <iostream>
#include <gtest/gtest.h>
#include "Date.util.cpp"
#include "Math.util.cpp"


TEST(Modulus_Compute, DividendEqualsDivisor_ReturnsZero) {
	EXPECT_EQ(modulus(5, 5), 0);
}

TEST(Modulus_Compute, DividendGreaterThanDivisor_ReturnsRemainder) {
	EXPECT_EQ(modulus(5, 3), 2);
}

TEST(Modulus_Compute, DividendLessThanDivisor_ReturnsDividend) {
	EXPECT_EQ(modulus(3, 5), 3);
}

TEST(Modulus_Compute, NegativeDividend_ReturnsPositiveRemainder) {
	EXPECT_EQ(modulus(-5, 3), 1);
}

TEST(Modulus_Compute, NegativeDivisor_ThrowsInvalidArgument) {
	EXPECT_THROW(modulus(5, -3), std::invalid_argument);
}

TEST(Modulus_Compute, ZeroDivisor_ThrowsInvalidArgument) {
	EXPECT_THROW(modulus(5, 0), std::invalid_argument);
}

TEST(Modulus_Compute, MaxDivisor_ThrowsOutOfRange) {
	EXPECT_THROW(modulus(5, INT_MAX), std::out_of_range);
}

TEST(Modulus_Compute, MaxDividend_ThrowsOutOfRange) {
	EXPECT_THROW(modulus(INT_MAX, 1), std::out_of_range);
}

TEST(Modulus_Compute, MinDividend_ThrowsOutOfRange) {
	EXPECT_THROW(modulus(INT_MIN, 1), std::out_of_range);
}
TEST(Date_Constructor_Build, ValidDate_ReturnsSameDate) {
	Date d(1, 31, 2001);
	EXPECT_EQ(d.getMonth(), 1);
	EXPECT_EQ(d.getDay(), 31);
	EXPECT_EQ(d.getYear(), 2001);
}
TEST(Date_Constructor_Build, InvalidDay_ThrowsInvalidArgument) {
	EXPECT_THROW(Date d(1, 32, 2001), std::invalid_argument);
}
TEST(Date_Constructor_Build, InvalidMonth_ThrowsInvalidArgument) {
	EXPECT_THROW(Date d(13, 31, 2001), std::invalid_argument);
}
TEST(Date_Constructor_Build, WrongDaysInFebruary_ThrowsInvalidArgument) {
	EXPECT_THROW(Date d(2, 29, 2001), std::invalid_argument);
	EXPECT_THROW(Date d(2, 30, 2004), std::invalid_argument);
}
TEST(Date_Constructor_Build, CorrectDaysInFebruary_ThrowsInvalidArgument) {
	EXPECT_NO_THROW(Date d(2, 28, 2001));
	EXPECT_NO_THROW(Date d(2, 29, 2004));
}
TEST(Addition_Days, AddingLargeAmountOfDays_ReturnCorrectDate) {
	Date d(1, 1, 1);
	Date x(12, 29, 8);
	d = d + Day(2919);
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Addition_Days, AddingNoDays_ReturnSameDate) {
	Date d(1, 1, 1);
	Date x(1, 1, 1);
	d = d + Day(0);
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Addition_Months, AddingNoMonths_ReturnSameDate) {
	Date d(1, 1, 1);
	Date x(1, 1, 1);
	d = d + Month(0);
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Addition_Months, AddingOneMonthOnLeapYear_ReturnCorrectDate) {
	Date d(1, 31, 2024);
	Date x(2, 29, 2024);
	d = d + Month();
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Addition_Months, AddingOneMonthOffLeapYear_ReturnCorrectDate) {
	Date d(1, 31, 2023);
	Date x(2, 28, 2023);
	d = d + Month();
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Addition_Months, MonthOverflow_ReturnCorrectDate) {
	Date d(12, 31, 2023);
	Date x(1, 31, 2024);
	d = d + Month();
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Subtraction_Months, MonthUnderflow_ReturnCorrectDate) {
	Date d(1, 31, 2023);
	Date x(12, 31, 2022);
	d = d - Month();
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}
TEST(Subtraction_Months, LargeMonthUnderflow_ReturnCorrectDate) {
	Date d(1, 31, 2023);
	Date x(1, 31, 2022);
	d = d - Month(12);
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}

TEST(Subtraction_Years, YearsLessThanOrEqualToZero_ReturnClampDate) {
	Date d(1, 1, 1);
	Date clamp(1, 1, 1);
	d = d - Year();
	EXPECT_EQ(d.getMonth(), clamp.getMonth());
	EXPECT_EQ(d.getDay(), clamp.getDay());
	EXPECT_EQ(d.getYear(), clamp.getYear());
}
TEST(Subtraction_Months, MonthUnderflowYearsLessThanZero_ReturnClampDate) {
	Date d(1, 1, 1);
	Date clamp(1, 1, 1);
	d = d - Month();
	EXPECT_EQ(d.getMonth(), clamp.getMonth());
	EXPECT_EQ(d.getDay(), clamp.getDay());
	EXPECT_EQ(d.getYear(), clamp.getYear());
}
TEST(Subtraction_Days, DayUnderflowYearsLessThanZero_ReturnClampDate) {
	Date d(1, 1, 1);
	Date clamp(1, 1, 1);
	d = d - Day();
	EXPECT_EQ(d.getMonth(), clamp.getMonth());
	EXPECT_EQ(d.getDay(), clamp.getDay());
	EXPECT_EQ(d.getYear(), clamp.getYear());
}
TEST(Addition_Years, LeapYearToNonLeapYearMonthAdjustment_ReturnDateWithAdjustedDay) {
	Date d(2, 29, 2024);
	Date x(2, 28, 2025);
	d = d + Year();
	EXPECT_EQ(d.getMonth(), x.getMonth());
	EXPECT_EQ(d.getDay(), x.getDay());
	EXPECT_EQ(d.getYear(), x.getYear());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}