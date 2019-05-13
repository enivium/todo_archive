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
		
		static std::shared_ptr<Date_Factory> instance;
		std::shared_ptr<Date> current_date;
		unsigned int current_weekday;
		std::shared_ptr<Date_Parser> parser;

		bool is_valid_date(std::shared_ptr<Date>);

	public:
		std::shared_ptr<Date_Factory> get_instance();
		std::shared_ptr<Date> get_current_date();		
		unsigned int get_current_weekday();

		std::shared_ptr<Date> make_date(std::string);   
};
