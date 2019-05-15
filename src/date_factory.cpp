// date_factory.cpp
// Class for constructing dates from input

#include "date_factory.h"

using namespace std;

// Set static variable to nullptr until called
Date_Factory::instance = nullptr;

/*--- Date_Factory Methods ---*/
Date_Factory::Date_Factory() {
	// Set current_time
	time_t current_raw = time(0);
	tm current;
	localtime_s(&current, &current_raw);	

	current_date = make_shared<Date>();
	current_date->day = current.tm_mday;		
	current_date->month = current.tm_mon + 1;
	current_date->year = current.tm_year + tm_base_yr;
	current_weekday = current.tm_wday;

	// Create parser chain
	parser = make_shared<Day_Word_Parser>();
	parser->register_next(make_shared<Month_Word_Parser>());
	parser->register_next(make_shared<Num_Units_Parser>());
	parser->register_next(make_shared<Slash_Dash_Parser>());
}

shared_ptr<Date_Factory> Date_Factory::get_instance() {
	if (instance == nullptr) {
		instance = make_shared<Date_Factory>();
	}

	return instance;
}

shared_ptr<Date> Date_Factory::get_current_date() {
	return current_date;
}
	
unsigned int Date_Factory::get_current_weekday() {
	return current_weekday;
}


shared_ptr<Date> Date_Factory::make_date(string date_string) {
	for (auto &c : date_string) {
		tolower(c);
	}

	return parser->parse(date_string, current_date, current_weekday);	
}

shared_ptr<Date> Date_Factory::make_date(string date_string, shared_ptr<Date> ref_date) {
	for (auto &c : date_string) {
		tolower(c);
	}

	return parser->parse(date_string, ref_date, get_weekday(ref_date));
}

bool Date_Factory::is_valid_date(shared_ptr<Date> date) {
	if (date->year < (current_date->year - valid_yr_range) {	
		return false;
	}

	if (date->year > current_date->year + valid_yr_range) {
		return false;
	}

	unsigned int mdays = date->days_in_month();
	if (mdays == 0) {
		// The month is not valid
		return false;
	}

	if (date->day < 1 || date->day > mdays) {
		return false;
	}

	return true;
}

unsigned int Date_Factory::get_weekday(shared_ptr<Date> date) {
	// Set current_time
	time_t current_raw = time(0);
	tm current;
	localtime_s(&current, &current_raw);	

	current.tm_mday = date->day;
	current.tm_mon = date->month - 1;
	current.tm_year = date->year - tm_base_yr;

	mktime(&current);

	return current.tm_wday;
}
