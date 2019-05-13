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
