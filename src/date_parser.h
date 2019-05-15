// date_parser.h
// Interface and implementations for parsing algorithms for different styles of dates

#pragma once

#include "date.h"

#include <memory>
#include <string>

class Date_Parser {
	private:
		std::shared_ptr<Date_Parser> next;
	protected:
		static void add_days(std::shared_ptr<Date>, unsigned int);
	public:
		Date_Parser();

		void register_next(std::shared_ptr<Date_Parser>) final;
		virtual std::shared_ptr<Date> parse(std::string, 
						    const std::shared_ptr<Date>, 
						    const unsigned int) = 0;
};	

class Slash_Dash_Parser : public Date_Parser {
	public:
		virtual std::shared_ptr<Date> parse(std::string,
						    const std::shared_ptr<Date>, 
						    const unsigned int) override;
};

class Month_Word_Parser : public Date_Parser {
	public:
		virtual std::shared_ptr<Date> parse(std::string,
						    const std::shared_ptr<Date>, 
						    const unsigned int) override;
};

class Day_Word_Parser : public Date_Parser {
	public:
		virtual std::shared_ptr<Date> parse(std::string,
						    const std::shared_ptr<Date>, 
						    const unsigned int) override;
};

class Num_Units_Parser : public Date_Parser {
	public:
		virtual std::shared_ptr<Date> parse(std::string,
						    const std::shared_ptr<Date>, 
						    const unsigned int) override;
};
