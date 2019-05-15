// recurrence.h
// An interface and classes to store recurrence information and handle recurrences

#pragma once

#include "date.h"
#include "date_factory.h"

#include <memory>
#include <vector>
#include <string>

class Recurrence {
	protected:
		std::shared_ptr<Date_Factory> df;

	public:
		Recurrence();
	
		virtual void recurr(std::shared_ptr<Date>, const std::shared_ptr<Date>) = 0;
		virtual std::string display_string() = 0;
};

class Unit_Recurrence : public Recurrence {
/* Handles recurrences at regular intervals */
	private:
		unsigned int interval;
		std::string unit;

	public:
		Unit_Recurrence(unsigned int, std::string);

		virtual void recurr(std::shared_ptr<Date>, const std::shared_ptr<Date>) override;
		virtual std::string display_string() override;
};

class Weekday_Recurrence : public Recurrence {
/* Handles recurrences on days of the week */
	private:
		std::vector<unsigned int> days;

	public:
		Weekday_Recurrence(std::vector<unsigned int>);	

		virtual void recurr(std::shared_ptr<Date>, const std::shared_ptr<Date>) override;
		virtual std::string display_string() override;
};
