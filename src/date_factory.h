// date_factory.h
// Class for constructing dates from input

#pragma once

#include "date.h"
#include "date_parser.h"

#include <memory>

class Date_Factory {
/* Parses inputs and constructs dates */
	private:
		Date_Factory();
		
		// Info variables
		static std::shared_ptr<Date_Factory> instance;
		std::shared_ptr<Date> current_date;
		unsigned int current_weekday;

		// Start of parser chain
		std::shared_ptr<Date_Parser> parser;

	public:
		// Retrieve info
		std::shared_ptr<Date_Factory> get_instance();
		const std::shared_ptr<Date> get_current_date();		
		const unsigned int get_current_weekday();

		// Make new dates
		std::shared_ptr<Date> make_date(std::string);   
		std::shared_ptr<Date> make_date(std::string, std::shared_ptr<Date>);

		// Methods for working with dates
		bool is_valid_date(std::shared_ptr<Date>);
		unsigned int get_weekday(std::shared_ptr<Date>);
};
