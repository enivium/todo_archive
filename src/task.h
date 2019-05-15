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

		// Object references
		std::shared_ptr<Date> due_date;
		std::shared_ptr<Recurrence> recurrence;
		std::shared_ptr<Task_List> parent;

	public:
		Task() = default;
		Task(std::string, unsigned int, std::shared_ptr<Date>, std::shared_ptr<Recurrence>,
		     std::shared_ptr<Task_List>);

		// Display overrides
		virtual void display_and_prompt() override;		
		virtual void list_display() override;

		// Menu option functions
		void complete_task();
		void postpone_task();
		void edit_task();
		void assign_task();
		void delete_task();
};
