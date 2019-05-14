// task.h
// Class to represent tasks

#pragma once

#include "display.h"
#include "date.h"

#include <string>
#include <memory>

class Task : Display {
	private:
		std::string name;
		std::shared_ptr<Date> due_date;
		unsigned int priority;
		std::string recurrence;

	public:
		Task() = default;
		Task(std::string, Date, unsigned int, std::string);

		virtual void display_and_prompt() override;		
		virtual void list_display() override;
};
