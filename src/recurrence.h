// recurrence.h
// An interface and classes to store recurrence information and handle recurrences

#pragma once

#include "date.h"
#include "date_factory.h"

#include <memory>
#include <vector>

class Recurrence {
	protected:
		std::shared_ptr<Date_Factory> df;

	public:
		Recurrence();
	
		virtual void recurr(std::shared_ptr<Date>) = 0;
};

class Unit_Recurrence : public Recurrence {
/* Handles recurrences at regular intervals */
	private:
		unsigned int interval;
		std::string unit;

	public:
		Unit_Recurrence(unsigned int, std::string);

		virtual void recurr(std::shared_ptr<Date>) override;
};

class Weekday_Recurrence : public Recurrence {
/* Handles recurrences on days of the week */
	private:
		std::vector<unsigned int> days;
		unsigned int idx;

	public:
		Weekday_Recurrence(std::vector);	

		virtual void recurr(std::shared_ptr<Date>) override;
};
