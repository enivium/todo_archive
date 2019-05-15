// recurrence.cpp
// An interface and classes to store recurrence information and handle recurrences

#include "recurrence.h"

using namespace std;

/*--- Recurrence Methods ---*/
Recurrence::Recurrence() {
	df = Date_Factory::get_instance();
}

/*--- Unit_Recurrence Methods ---*/
Unit_Recurrence::Unit_Recurrence(unsigned int i, string u) : interval(i), unit(u) {
	// Empty constructor body
}

void Unit_Recurrence::recurr(shared_ptr<Date> date) {
	date = df->make_date(to_string(interval) + " " + unit, date);	
}

/*--- Weekday_Recurrence Methods ---*/
Weekday_Recurrence::Weekday_Recurrence(vector<unsigned int> d) : days(d) {
	// Empty constructor body
}

void Weekday_Recurrence::recurr(shared_ptr<Date> date) {
	// Find the index of last occurrence, then go one past
	unsigned int new_day;
	unsigned int old_day = df->get_weekday(date);
	unsigned int i = 0;
	do {
		new_day = days.at(i);	
		++i;
	while (new_day < old_day);
	new_day = days.at(i%days.size());

	string date_string;
	switch (new_day) {
		case sunday:
			date_string = "sunday";
			break;
		case monday:
			date_string = "monday";
			break;
		case tuesday:
			date_string = "tuesday";
			break;
		case wednesday:
			date_string = "wednesday";
			break;
		case thursday:
			date_string = "thursday";
			break;
		case friday:
			date_string = "friday";
			break;
		case saturday:
			date_string = "saturday";
			break;
	}		

	date = df->make_date(date_string, date);
}	
