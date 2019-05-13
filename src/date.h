// date.h
// Class for representing dates and holding calendar info

#pragma once

// Common calendar info
enum Weekdays {sunday, monday, tuesday, wednesday, thursday, friday, saturday};
const unsigned int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const unsigned int months_in_yr = 12;
const unsigned int valid_yr_range = 100;
const unsigned int tm_base_yr = 1900;

class Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;

	Date() = default;
	Date(Date &) = default;

	unsigned int days_in_month();
};	

// Date comparison operator overloads
bool operator==(const Date &lhs, const Date &rhs); 
bool operator!=(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
