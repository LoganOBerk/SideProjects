#include <iostream>
#include <iomanip>
struct Day {
	int val;
	Day(int v) : val(v){}
};

struct Month {
	int val;
	Month(int v) : val(v){}
};

struct Year {
	int val;
	Year(int v) : val(v){}
};
class Date {
	private:
		int day;
		int month;
		int year;
		
		
		bool isLeapYear(const int& y) { 
			return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); 
		};

		int dayOfMonth(const int& y, int m) {
			int monthMax[12] = { 31,(isLeapYear(y)) ? 29 : 28,31,30,31,30,31,31,30,31,30,31 };
			m = (m % 12 != 0) ? m % 12 : 12;
			return monthMax[m - 1];
		}
	public:
		Date(int d = 1, int m = 1, int y = 1){
			y += (m != 12) ? m / 12 : 0;
			m = (m % 12 != 0) ? m % 12 : 12;
			d = (dayOfMonth(y, m) < d) ? dayOfMonth(y, m) : d;

			year = y;
			month = m;
			day = d;
		}
		
		
		void printDate() {
			std::cout << std::setw(2) << std::setfill('0') << month << "-";
			std::cout << std::setw(2) << std::setfill('0') << day << "-";
			std::cout << std::setw(4) << std::setfill('0') << year << std::endl;
		}
		Date operator+(const Day& x) {
			int d = day + x.val;
			int m = month;
			int y = year;
			int mMax = dayOfMonth(y, m);
			while (d > mMax) {
				d -= mMax;
				m++;
				mMax = dayOfMonth(y , m);
			}
			
			return Date(d, m, y);
		}
		Date operator+(const Month& x) {
			int m = month + x.val;
			int y = year;
			while (m > 12) {
				m -= 12;
				y++;
			}
			
			return Date(day, m, y);
		}
		Date operator+(const Year& x) {
			int y = year + x.val;
			return Date(day, month, y);
		}

};

int main(){
	// Test Case 1
	Date date1(28, 2, 2020);
	date1.printDate();
	date1 = date1 + Year(3);
	date1.printDate();
	date1 = date1 + Month(1);
	date1.printDate();
	date1 = date1 + Day(28);
	date1.printDate();
	date1.printDate();
	date1 = date1 + Year(3);
	date1.printDate();
	date1 = date1 + Month(1);
	date1.printDate();
	date1 = date1 + Day(28);
	date1.printDate();

	// Test Case 2
	Date date2(31, 12, 2019);
	date2.printDate();
	date2 = date2 + Year(1);
	date2.printDate();
	date2 = date2 + Month(1);
	date2.printDate();
	date2 = date2 + Day(1);
	date2.printDate();
	date2.printDate();
	date2 = date2 + Year(1);
	date2.printDate();
	date2 = date2 + Month(11);
	date2.printDate();
	date2 = date2 + Day(31);
	date2.printDate();

	// Test Case 3
	Date date3(30, 1, 2021);
	date3.printDate();
	date3 = date3 + Year(0);
	date3.printDate();
	date3 = date3 + Month(1);
	date3.printDate();
	date3 = date3 + Day(1);
	date3.printDate();
	date3.printDate();
	date3 = date3 + Year(4);
	date3.printDate();
	date3 = date3 + Month(2);
	date3.printDate();
	date3 = date3 + Day(28);
	date3.printDate();

	// Test Case 4
	Date date4(29, 2, 2024);
	date4.printDate();
	date4 = date4 + Year(1);
	date4.printDate();
	date4 = date4 + Month(1);
	date4.printDate();
	date4 = date4 + Day(1);
	date4.printDate();
	date4.printDate();
	date4 = date4 + Year(3);
	date4.printDate();
	date4 = date4 + Month(12);
	date4.printDate();
	date4 = date4 + Day(31);
	date4.printDate();

	// Test Case 5
	Date date5(29, 2, 2000);
	date5.printDate();
	date5 = date5 + Year(100);
	date5.printDate();
	date5 = date5 + Month(1);
	date5.printDate();
	date5 = date5 + Day(29);
	date5.printDate();
	date5.printDate();
	date5 = date5 + Year(4);
	date5.printDate();
	date5 = date5 + Month(2);
	date5.printDate();
	date5 = date5 + Day(1);
	date5.printDate();

	// Test Case 6
	Date date6(15, 6, 2022);
	date6.printDate();
	date6 = date6 + Year(2);
	date6.printDate();
	date6 = date6 + Month(7);
	date6.printDate();
	date6 = date6 + Day(16);
	date6.printDate();
	date6.printDate();
	date6 = date6 + Year(0);
	date6.printDate();
	date6 = date6 + Month(5);
	date6.printDate();
	date6 = date6 + Day(31);
	date6.printDate();

	// Test Case 7
	Date date7(30, 11, 2023);
	date7.printDate();
	date7 = date7 + Year(1);
	date7.printDate();
	date7 = date7 + Month(1);
	date7.printDate();
	date7 = date7 + Day(1);
	date7.printDate();
	date7.printDate();
	date7 = date7 + Year(0);
	date7.printDate();
	date7 = date7 + Month(0);
	date7.printDate();
	date7 = date7 + Day(365);
	date7.printDate();

	// Test Case 8
	Date date8(1, 3, 2023);
	date8.printDate();
	date8 = date8 + Year(1);
	date8.printDate();
	date8 = date8 + Month(11);
	date8.printDate();
	date8 = date8 + Day(365);
	date8.printDate();
	date8.printDate();
	date8 = date8 + Year(2);
	date8.printDate();
	date8 = date8 + Month(0);
	date8.printDate();
	date8 = date8 + Day(30);
	date8.printDate();

	// Test Case 9
	Date date9(30, 4, 2021);
	date9.printDate();
	date9 = date9 + Year(2);
	date9.printDate();
	date9 = date9 + Month(2);
	date9.printDate();
	date9 = date9 + Day(2);
	date9.printDate();
	date9.printDate();
	date9 = date9 + Year(0);
	date9.printDate();
	date9 = date9 + Month(7);
	date9.printDate();
	date9 = date9 + Day(1);
	date9.printDate();

	// Test Case 10
	Date date10(1, 1, 2020);
	date10.printDate();
	date10 = date10 + Year(10);
	date10.printDate();
	date10 = date10 + Month(12);
	date10.printDate();
	date10 = date10 + Day(365);
	date10.printDate();
	date10.printDate();
	date10 = date10 + Year(1);
	date10.printDate();
	date10 = date10 + Month(1);
	date10.printDate();
	date10 = date10 + Day(1);
	date10.printDate();

	// Test Case 11
	Date date11(1, 1, 1900);
	date11.printDate();
	date11 = date11 + Year(200);
	date11.printDate();
	date11 = date11 + Month(6);
	date11.printDate();
	date11 = date11 + Day(365);
	date11.printDate();
	date11.printDate();
	date11 = date11 + Year(123);
	date11.printDate();
	date11 = date11 + Month(11);
	date11.printDate();
	date11 = date11 + Day(999);
	date11.printDate();

	// Test Case 12
	Date date12(1, 3, 2024);
	date12.printDate();
	date12 = date12 + Year(-1);
	date12.printDate();
	date12 = date12 + Month(-2);
	date12.printDate();
	date12 = date12 + Day(-30);
	date12.printDate();
	date12.printDate();
	date12 = date12 + Year(-3);
	date12.printDate();
	date12 = date12 + Month(-1);
	date12.printDate();
	date12 = date12 + Day(-28);
	date12.printDate();

	// Test Case 13
	Date date13(29, 2, 2016);
	date13.printDate();
	date13 = date13 + Year(4);
	date13.printDate();
	date13 = date13 + Year(4);
	date13.printDate();
	date13 = date13 + Year(4);
	date13.printDate();
	date13.printDate();
	date13 = date13 + Month(12);
	date13.printDate();
	date13 = date13 + Day(366);
	date13.printDate();
	date13 = date13 + Year(4);
	date13.printDate();

	// Test Case 14
	Date date14(1, 1, 2022);
	date14.printDate();
	date14 = date14 + Day(500);
	date14.printDate();
	date14 = date14 + Month(24);
	date14.printDate();
	date14 = date14 + Day(1000);
	date14.printDate();
	date14.printDate();
	date14 = date14 + Month(100);
	date14.printDate();
	date14 = date14 + Day(2000);
	date14.printDate();
	date14 = date14 + Year(10);
	date14.printDate();

	// Test Case 15
	Date date15(28, 2, 2100);
	date15.printDate();
	date15 = date15 + Day(1);
	date15.printDate();
	date15 = date15 + Year(4);
	date15.printDate();
	date15 = date15 + Day(365);
	date15.printDate();
	date15.printDate();
	date15 = date15 + Year(4);
	date15.printDate();
	date15 = date15 + Month(2);
	date15.printDate();
	date15 = date15 + Day(29);
	date15.printDate();



	return 0;
}