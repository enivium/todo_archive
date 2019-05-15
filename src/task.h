// task.h
// Class to represent tasks

#pragma once

#include "display.h"
#include "date.h"
#include "recurrence.h"

#include <string>
#include <memory>

// Forward declaration to prevent circular inclusion
class Task_List;

class Task : public Display {
	private:
		// Variables
		std::string name;
		unsigned int priority;
		bool recurr_from_current;

		// Object references
		std::shared_ptr<Date> due_date;
		std::shared_ptr<Recurrence> recurrence;
		std::shared_ptr<Task_List> parent;

		// Menu and display methods
		void display_info();

	public:
		Task() = default;
		Task(std::string, unsigned int, std::shared_ptr<Date>, std::shared_ptr<Recurrence>,
		     bool, std::shared_ptr<Task_List>);

		// Display overrides
		virtual void display_and_prompt() override;		
		virtual std::string list_display() override;

		// Menu option functions
		void complete();
		void reschedule();
		void edit();
		void delete_task();
		void back();
		void quit();

		// Utility methods
		std::shared_ptr<Date> prompt_date();
};
