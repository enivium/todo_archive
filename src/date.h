// date.h
// Class for representing dates and holding calendar info

#pragma once

#include <memory>

// Common calendar info
enum Weekdays {sunday, monday, tuesday, wednesday, thursday, friday, saturday};
static const unsigned int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const unsigned int months_in_yr = 12;

struct Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
};	

class Date_Factory {
/* Parses inputs and constructs dates */
	private:
		Date_Factory();
		
		static std::shared_ptr<Date_Factory> instance;
		
		std::shared_ptr<Date> current_date;
		unsigned int current_weekday;
		
		// TODO: Make parsing methods
	public:
		std::shared_ptr<Date_Factory> get_instance();

		std::shared_ptr<Date> get_current_date();		
		unsigned int get_current_weekday();

		std::shared_ptr<Date> make_date(std::string);   
};

// Date comparison operator overloads
bool operator==(const Date &lhs, const Date &rhs); 
bool operator!=(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
