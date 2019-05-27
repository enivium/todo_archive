// date.h
// Class for representing dates and holding calendar info

#pragma once

#include <string>

// Common calendar info
enum Weekdays {sunday, monday, tuesday, wednesday, thursday, friday, saturday};
const unsigned int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const unsigned int months_in_yr = 12;
const unsigned int valid_yr_range = 100;
const unsigned int tm_base_yr = 1900;

struct Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;

	Date() = default;

	unsigned int days_in_month();
};	

// Useful date-related functions
int wkdy_to_int(std::string);
std::string wkdy_to_string(unsigned int);

// Date comparison operator overloads
bool operator==(const Date &lhs, const Date &rhs); 
bool operator!=(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);

// Define hash
namespace std {
  template <> struct hash<Date>
  {
    std::size_t operator()(const Date& d) const
    {
      return (d.day * 17 + d.month * 17 + d.year * 3);
    }
  };

}
