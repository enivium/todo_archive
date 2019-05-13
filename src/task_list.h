// task_list.h
// Base class for objects that can hold Tasks

#pragma once

#include "display.h"
#include "task.h"
#include "date.h"

#include <map>
#include <memory>
#include <string>

class Task_List : public Display {
	protected:
		// Hold references to tasks with different access methods
		std::multimap<std::string, std::shared_ptr<Task>> tasks_by_name;
		std::multimap<Date, std::shared_ptr<Task>> tasks_by_date;

		// Hold child Task_Lists
		std::multimap<std::shared_ptr<Task_List>> child_lists;

		// Maintain reference to parent
		std::shared_ptr<Task_List> parent;

	public:
		Task_List() = default;
		virtual ~Task_List();

		// Display methods
		virtual void display_and_prompt() override;
		virtual void list_display() override;		

		// Menu items
		void add_task();		
		void complete_task();
		void postpone_task();
		void edit_task();
		void assign_task();
		void list_child_lists();
		void search();
		void show_date();	
};
