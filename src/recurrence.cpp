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

void Unit_Recurrence::recurr(shared_ptr<Date> date, shared_ptr<Date> ref_date) {
	date = df->make_date(to_string(interval) + " " + unit, ref_date);	
}

string Unit_Recurrence::display_string() {
	string disp("Every ");
	if (unit > 1) {
		disp += to_string(interval) + " " + unit + "s";
	} else {
		disp += unit;
	}

	return disp;
}

/*--- Weekday_Recurrence Methods ---*/
Weekday_Recurrence::Weekday_Recurrence(vector<unsigned int> d) : days(d) {
	// Empty constructor body
}

void Weekday_Recurrence::recurr(shared_ptr<Date> date, shared_ptr<Date> ref_date) {
	// Find the index of last occurrence, then go one past
	unsigned int new_day;
	unsigned int old_day = df->get_weekday(ref_date);
	unsigned int i = 0;
	do {
		new_day = days.at(i);	
		++i;
	while (new_day < old_day);
	new_day = days.at(i%days.size());

	string date_string = wkdy_to_string(new_day);
	date = df->make_date(date_string, ref_date);
}	

string Unit_Recurrence::display_string() {
	string disp;
	
	auto iter = days.cbegin();
	disp += wkdy_to_string(*iter);
	++iter;

	for (; iter != days.cend(); ++iter) {
		disp += ", " + wkdy_to_string(*iter);
	}
	
	return disp;
}
