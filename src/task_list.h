// task_list.h
// Base class for objects that can hold Tasks

#pragma once

#include "display.h"
#include "task.h"
#include "date_factory.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

class Task_List : public Display {
	protected:
		// Task containers
		std::multimap<std::string, std::shared_ptr<Task>> tasks_by_name;
		std::map<Date, std::vector<std::shared_ptr<Task>>> tasks_by_date;
		bool sort_by_priority(std::shared_ptr<Task> &, std::shared_ptr<Task> &);

		// Child and parent lists
		std::multimap<std::shared_ptr<Task_List>> child_lists;
		std::shared_ptr<Task_List> parent;

		// Object references
		std::shared_ptr<Date_Factory> df;

		// State variables
		shared_ptr<Date> current_view;
		unsigned int focus_task;

	public:
		Task_List() = default;
		virtual ~Task_List();

		// Display methods
		virtual void display_and_prompt() override;
		virtual std::string list_display() override;		

		// Utility methods 
		const std::shared_ptr<Date> get_current_date();

		// Menu items
		void add_task();		
		void complete_task();
		void postpone_task();
		void edit_task();
		void assign_task();
		void delete_task();
		void list_child_lists();
		void search();
		void show_date();	

		void change_task_date(std::shared_ptr<Date>);
};
