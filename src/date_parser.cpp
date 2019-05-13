// date_parser.cpp
// Interface and implementations for parsing algorithms for different styles of dates

#include "date_parser.h"

#include <regex>
#include <sstream>
#include <algorithm>

using namespace std;

/*--- Date_Parser Methods ---*/
Date_Parser::Date_Parser() : next(nullptr) {
	// Empty constructor body
}

void Date_Parser::add_days(shared_ptr<Date> date, unsigned int days_to_add) {
	if (days_to_add == 0) {
		return;
	}

	date->day += days_to_add;

	bool leap_year = false;
	if ((date->year % 4 == 0) && (date->year % 100 != 0)) {
		leap_year = true;
	}

	unsigned int mdays = days_in_months[date->month];
	if (date->month == 2 && leap_year) {
		mdays += 1;
	}

	while (date->day > mdays) {
		date->day -= mdays;
		date->month += 1;

		if (date->month > months_in_yr) {
			date->month -= months_in_yr;
			date->year += 1;
			if ((date->year % 4 == 0) && (date->year % 100 != 0)) {
				leap_year = true;
			} else {
				leap_year = false;
			}
		}

		mdays = days_in_months[date->month];
		if (date->month == 2 && leap_year) {
			mdays += 1;
		}
	}
}	

void Date_Parser::register_next(shared_ptr<Date_Parser> p) {
	if (next == nullptr) {
		next = p;
	} else {
		next->register_next(p);
	}
}
		
/*--- Slash_Dash_Parser Methods ---*/
shared_ptr<Date> Slash_Dash_Parser::parse(string date_string, shared_ptr<Date> current_date,
					  unsigned int current_weekday) 
{
/* Handles dates in slash- or dash-separated format */
	regex r("^\d{1,2}[/\-]\d{1,2}([/\-]\d{2}|\d{4})?$");
	
	if (regex_match(date_string, r)) {
		replace(date_string.begin(), date_string.end(), '/', ' ');
		replace(date_string.begin(), date_string.end(), '-', ' ');
		istringstream date_strm(date_string);

		shared_ptr<Date> new_date = make_shared<Date>();	
		date_string >> new_date->month >> new_date->day;

		unsigned int yr;
		// Check if year not provided
		if(!(date_string >> yr)) {
			yr = current_date->year;
		}	

		// Check for two-digit year
		if (yr < 100) {
			yr += current_date->year / 100 * 100;
		}

		new_date->year = yr;

		return new_date;
	}

	if (next != nullptr) {
		return next->parse(date_string);
	}

	return nullptr;
}

/*--- Month_Word_Parser Methods ---*/
shared_ptr<Date> Month_Word_Parser::parse (string date_string, shared_ptr<Date> current_date,
					   unsigned int current_weekday) 
{
/* Handles dates formatted with the month as a word */
	string months("january|jan|february|feb|march|mar|april|apr|may|june|jun|july|jul|"
		      "august|aug|september|sept|sep|october|oct|november|novdecember|dec");
	string days("\d?(\d|1st|2nd|3rd|4th|5th|6th|7th|8th|9th|0th)");
	string years("'?\d{2}|\d{4}");

	regex r("^(" + months + ") " + days + ",? (" + years + ")?$|"
		"^" + days + " (" + months + ") (" + years + ")?$|");
	
	if (regex_match(date_string, r)) {
		// Configure regex searches and use to extract info
		regex month_regex(months);
		regex num_regex("\d+");

		smatch month_match;
		smatch num_match;	

		regex_search(date_string, month_match, month_regex);
		regex_search(date_string, num_match, num_regex);

		// Load info into new_date
		shared_ptr<Date> new_date = make_shared<Date>();	

		string m = *(month_match.begin());
		if (m == "january" || m == "jan") {
			new_date->month = 1;
		} else if (m == "february" || m == "feb") {
			new_date->month = 2;
		} else if (m == "march" || m == "mar") {
			new_date->month = 3;
		} else if (m == "april" || m == "apr") {
			new_date->month = 4;
		} else if (m == "may") {
			new_date->month = 5;
		} else if (m == "june" || m == "jun") {
			new_date->month = 6;
		} else if (m == "july" || m == "jul") {
			new_date->month = 7;
		} else if (m == "august" || m == "aug") {
			new_date->month = 8;
		} else if (m == "september" || m == "sept" || m == "sep") {
			new_date->month = 9;
		} else if (m == "october" || m == "oct")
			new_date->month = 10;
		} else if (m == "november" || m == "nov") {
			new_date->month = 11;
		} else {
			new_date->month = 12;
		}
	
		string d;
		string y;

		auto iter = num_match.begin()
		d = *iter;
		++iter;
		y = *iter;

		istringstream d_strm(d);
		istringstream y_strm(y);

		d_strm >> new_date->day;
		y_strm >> new_date->year;

		return new_date;
	}

	if (next != nullptr) {
		return next->parse(date_string);
	}

	return nullptr;
}

/*--- Day_Word_Parser Methods ---*/
shared_ptr<Date> Day_Word_Parser::parse(string date_string, shared_ptr<Date> current_date,
					  unsigned int current_weekday) 
{
/* Handles words that indicate the day */
	
	if (date_string == "today") {
		return current_date;
	} 

	unsigned int days_to_add;
	bool day_word = false;
	
	if (date_string == "tomorrow") {
		days_to_add = 1;
	} else if (date_string == "sunday" || date_string == "sun") {
		days_to_add = sunday - current_weekday;
		day_word = true;
	} else if (date_string == "monday" || date_string == "mon") {
		days_to_add = monday - current_weekday;
		day_word = true;
	} else if (date_string == "tuesday" || date_string == "tue") {
		days_to_add = tuesday - current_weekday;
		day_word = true;
	} else if (date_string == "wednesday" || date_string == "wed") {
		days_to_add = wednesday - current_weekday;
		day_word = true;
	} else if (date_string == "thursday" || date_string == "thur" || date_string == "thurs") {
		days_to_add = thursday - current_weekday;
		day_word = true;
	} else if (date_string == "friday" || date_string == "fri") {
		days_to_add = friday - current_weekday;
		day_word = true;
	} else if (date_string == "saturday" || date_string == "sat") {
		days_to_add = saturday - current_weekday;
		day_word = true;
	}

	if (day_word) {
		if (days_to_add == 0) {
			days_to_add = 7;
		}

		shared_ptr<Date> new_date = make_shared<Date>(*current_date);	
		add_days(new_date, days_to_add);

		return new_date;
	}

	if (next != nullptr) {
		return next->parse(date_string);
	}

	return nullptr;
}

/*--- Num_Units_Parser Methods ---*/
shared_ptr<Date> Num_Units_Parser::parse(string date_string, shared_ptr<Date> current_date,
					  unsigned int current_weekday) 
{
/* Handles dates set some number of days, weeks, months, or years in the future */
	regex r("^(in )?\d+ (days?|d|weeks?|wks?|months?|mon|years?|yrs?)$");
	
	if (regex_match(date_string, r)) {
		istringstream date_strm(date_string);

		unsigned int num_units;
		date_strm >> num_units;
		if (date_strm.fail()) {
			date_strm.clear();
			string dummy;
			date_strm >> dummy >> num_units;
		}

		string units;
		date_strm >> units;	

		shared_ptr<Date> new_date = make_shared<Date>(*current_date);	

		if (units == "day" || units == "days" || units == "d") {
			add_days(new_date, num_units);
		} else if (units == "week" || units == "weeks"|| units == "wk" || units == "wks") {
			add_days(new_date, num_units * 7);
		} else if (units == "month" || units == "months" || units == "mon") {
			new_date->month += num_units;
			while (new_date->month > months_in_yr) {
				new_date->month -= months_in_yr;
				new_date->year += 1;
			}	
		} else {
			new_date->year += num_units;
		}	

		return new_date;
	}

	if (next != nullptr) {
		return next->parse(date_string);
	}

	return nullptr;
}
