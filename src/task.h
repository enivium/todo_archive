// task.h
// Class to represent tasks

#pragma once

#include "display.h"
#include "date.h"
#include "recurrence.h"
#include "date_factory.h"

#include <string>
#include <memory>

enum colorscheme {p1 = 1, p2 = 2, p3 = 3, overdue = 4};

// Forward declaration to prevent circular inclusion
class Task_List;

class Task : public Display {
	private:
		// Variables
		unsigned int priority;
		bool recurr_from_current;
		bool overdue;

		// Object references
		std::shared_ptr<Date> due_date;
		std::shared_ptr<Recurrence> recurrence;
		std::shared_ptr<Task_List> parent;
		std::shared_ptr<Date_Factory> df;

		// Menu and display methods
		void display_info();

		// Prompt methods
		void prompt_name();
		void prompt_date();
		void prompt_recurrence();
		void prompt_priority();

	public:
		// Constructors
		Task() = delete;
		Task(std::shared_ptr<Task_List>);
/*
		Task(std::string, std::shared_ptr<Date>, std::shared_ptr<Recurrence>, bool,
		     std::shared_ptr<Task_List>);
*/

		// Display overrides
		virtual void display_and_prompt() override;		
		virtual std::string list_display() override;

		// Menu option functions
		void complete();
		void reschedule();
		void edit();
		void delete_task();

		// Getters and setters
		unsigned int get_priority();
		bool get_overdue();
		std::string get_name();
		std::shared_ptr<Date> get_due_date();
		void set_group(std::shared_ptr<Task_List>);
};
