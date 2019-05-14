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
	unsigned int new_day = 0;
	unsigned int old_day = df->get_weekday(date);
	while (new_day < 
			
