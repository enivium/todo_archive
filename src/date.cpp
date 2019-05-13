// date.cpp
// Class to represent date

#include "date.h"

using namespace std;

/*--- Date Methods ---*/
unsigned int Date::days_in_month() {
	if (month < 1 || month > months_in_yr) {
		return 0;
	}

	unsigned int num_days = days_in_months[month-1];
	if (month == 2) {
		if ((year % 4 == 0) && (year % 100 != 0)) {
			num_days += 1;
		}
	}
	return num_days;
}


/*--- General Functions ---*/
// Comparison operator overloads
bool operator==(const Date &lhs, const Date &rhs) {
	return (lhs.day == rhs.day) && 
	       (lhs.month == rhs.month) && 
	       (lhs.year == rhs.year);
}

bool operator!=(const Date &lhs, const Date &rhs) {
	return !operator==(lhs, rhs);
}

bool operator<(const Date &lhs, const Date &rhs) {
	if (lhs.year == rhs.year) {
		if (lhs.month == rhs.month) {
			return lhs.day < rhs.day;
		}

		return lhs.month < rhs.month;	
	}

	return lhs.year < rhs.year;
}

bool operator>(const Date &lhs, const Date &rhs) {
	return operator<(rhs, lhs);
}

bool operator<=(const Date &lhs, const Date &rhs) {
	return !operator>(lhs, rhs);
}

bool operator>=(const Date &lhs, const Date &rhs) {
	return !operator<(lhs, rhs);
}
