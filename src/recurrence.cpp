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
	
