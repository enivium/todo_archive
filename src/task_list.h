// task_list.h
// Base class for objects that can hold Tasks

#pragma once

#include "display.h"
#include "task.h"
#include "date_factory.h"

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

class Task_List : public Display {
	protected:
		// Task containers
		std::unordered_multimap<std::string, std::shared_ptr<Task>> tasks_by_name;
		std::unordered_map<Date, std::vector<std::shared_ptr<Task>>> tasks_by_date;
		static bool sort_by_priority(std::shared_ptr<Task> &, std::shared_ptr<Task> &);

		// Object references
		std::vector<std::shared_ptr<Task_List>> children;
		std::shared_ptr<Task_List> parent;
		std::shared_ptr<Date_Factory> df;

		// State variables
		std::shared_ptr<Date> current_view;
		char command;

		// Display methods
		void display_tasks(std::vector<std::shared_ptr<Task>> &);
		unsigned int select_task(unsigned int);
		void display_groups(unsigned int);

		// Content methods and menu items
		void make_group();
		void erase_group();
		void erase_group(std::shared_ptr<Task_List>);
		void remove_child(std::shared_ptr<Task_List>);
		void search();
		void present_date();	
		void view_group();

	public:
		Task_List();
		Task_List(std::shared_ptr<Task_List>);
		virtual ~Task_List() = default;

		// Display methods
		virtual void display_and_prompt() override;
		virtual std::string list_display() override;		

		// Access methods 
		std::shared_ptr<Date> get_current_view();
		std::vector<std::shared_ptr<Task_List>> & get_children();
		std::shared_ptr<Task_List> get_parent();
		void quit();

		// Menu items
		void add_task();		
		void add_task(std::shared_ptr<Task>);
		void complete_task(std::vector<std::shared_ptr<Task>> &);
		void reschedule_task(std::vector<std::shared_ptr<Task>> &);
		void delete_task(std::vector<std::shared_ptr<Task>> &);
		void focus_task(std::vector<std::shared_ptr<Task>> &);

		// Task methods
		void reschedule_task(std::shared_ptr<Task>, Date &);	
		void delete_task(std::shared_ptr<Task>);
};
