// date.cpp
// Class to represent date

#include "date.h"

#include <algorithm>
#include <sstream>

using namespace std;

Date_Factory::instance = nullptr;
Date_Factory::current_date = nullptr;

/*--- Date_Factory Methods ---*/
Date_Factory::Date_Factory() {
	time_t current_raw = time(0);
	tm current;
	localtime_s(&current, &current_raw);	

	current_date = make_shared<Date>();
	current_date->day = current.tm_mday;		
	current_date->month = current.tm_mon + 1;
	current_date->year = current.tm_year + 1900;
	current_weekday = current.tm_wday;
}

shared_ptr<Date_Factory> Date_Factory::get_instance() {
	if (instance == nullptr) {
		instance = make_shared<Date_Factory>();
	}

	return instance;
}

shared_ptr<Date> get_current_date() {
	return current_date;
}
	
unsigned int get_current_weekday() {
	return current_weekday;
}

shared_ptr<Date> make_date(string date_string) {
	// TODO: Implement
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
