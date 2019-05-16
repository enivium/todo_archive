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
// Useful date-related functions
int wkdy_to_int(string day) {
	if (date_string == "sunday" || date_string == "sun") {
		return sunday;
	} else if (date_string == "monday" || date_string == "mon") {
		return monday;
	} else if (date_string == "tuesday" || date_string == "tue") {
		return tuesday;
	} else if (date_string == "wednesday" || date_string == "wed") {
		return wednesday;
	} else if (date_string == "thursday" || date_string == "thur" || date_string == "thurs") {
		return thursday;
	} else if (date_string == "friday" || date_string == "fri") {
		return friday;
	} else if (date_string == "saturday" || date_string == "sat") {
		return saturday;
	} else {
		return -1;
	}
}

string wkdy_to_string(unsigned int day) {
	switch (day) {
		case sunday:
			return "sunday";
		case monday:
			return "monday";
		case tuesday:
			return "tuesday";
		case wednesday:
			return "wednesday";
		case thursday:
			return "thursday";
		case friday:
			return "friday";
		case saturday:
			return "sanurday";
		default:
			return "";
	}		
}

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
