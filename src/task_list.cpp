// task_list.cpp
// Base class for objects that can hold Tasks

#include "task_list.h"
#include "date_factory.h"

#include <algorithm>

using namespace std;

bool Task_List::sort_by_priority(std::shared_ptr<Task> &t1, std::shared_ptr<Task> &t2) {
	if (t1.get_overdue()) {
		return true;
	}

	return t1.get_priority() < t2.get_priority();
}

void Task_List::display_tasks(vector<shared_ptr<Task>> &tasks) {
	sort(tasks.begin(), tasks.end(), sort_by_priority);
	unsigned int idx = 1;
	for (shared_ptr<Task> task : tasks) {
		if (task->get_overdue()) {
			attron(COLOR_PAIR(overdue));	
		} else {
			attron(COLOR_PAIR(task->get_priority));
		}

		printw("%i) ", idx);
		task->list_display();
		printw("\n");
		attrset(A_NORMAL);
	
		++idx;
	}
}

void Task_List::display_groups(unsigned int indent) {
	for (shared_ptr<Task_List> child : children) {
		for (unsigned int i = 0; i < indent; ++i) {
			attron(A_BOLD);
			printw("\t");
			printw(child->list_display().c_str());
			printw("\n");
			attrset(A_NORMAL);
			child->display_groups(indent + 1);
		}
	}
}

void Task_List::make_group() {
	shared_ptr<Task_List> parent_ptr = make_shared<Task_List>(this);
	children.push_back(make_shared<Task_List>(parent_ptr));
}

void Task_List::erase_group() {
	shared_ptr<Task_List> grp_to_erase = select_group(make_shared<Task_List>(this));
	shared_ptr<Task_List> erase_parent = grp_to_erase->get_parent();

	// If group is root group (e.g. the Todo_List) don't do anything
	if (grp_to_erase->get_parent != nullptr) {
		// Move all tasks to parent of erased task
		for (auto pair : events_by_name) {
			pair.second->set_group(erase_parent);
		}

		// Tell all children to move tasks to parent of erased task
		for (auto child : children) {
			child->erase_group(erase_parent);
		}
	
		// Tell parent to remove reference, which causes shared_ptr to call destructor
		parent->remove_child(make_shared<Task_List>(this));
	}
}

void Task_List::erase_group(shared_ptr<Task_List> erase_parent) {
	// Move all tasks to parent of erased task
	for (auto pair : events_by_name) {
		pair.second->set_group(erase_parent);
	}

	// Tell all children to move tasks to parent of erased task
	for (auto child : children) {
		child->erase_group(erase_parent);
	}
}

void Task_List::remove_child(shared_ptr<Task_List> to_remove) {
	// Erase-remove idiom
	children.erase(remove(children.begin(), children.end(), to_remove), children.end());
}

void Task_List::search() {
	printw("Task Name:\n");	
	printw(">");
	string search_name = prompt_string();
	// TODO: Finish implementing	
}		
		
void Task_List::present_date() {
	printw("Date:\n");
	
	bool valid_input = false;
	while(!valid_input) {
		printw(">");
		string date_string = prompt_string();
		shared_ptr<Date> date = df->make_date(date_string);

		if (date == nullptr) {
			printw("ERROR: Invalid format!\n");
			continue;
		}

		if (!(df->is_valid_date(date))) {
			printw("ERROR: Invalid date!\n");
			continue;
		}

		valid_input = true;
	}

	current_view = date;
}

void Task_List::view_group() {
	shared_ptr<Task_List> to_view = select_group(make_shared<Task_List>(this));
	to_view->display_and_prompt();
}

Task_List::Task_List() : parent(nullptr) {
	df = Date_Factory::get_instance();
	current_view = df->get_current_date();	
}

Task_List::Task_List(shared_ptr<Task_List> p) : parent(p) {
	df = Date_Factory::get_instance();
	current_view = df->get_current_date();

	erase();
	printw("Group Name:\n");
	printw(">");
	name = prompt_string();
}

string Task_List::list_display() {
	return name;
}

shared_ptr<Date> Task_List::get_current_view() {
	return current_view();
}

vector<shared_ptr<Task_List>> & Task_List::get_children() {
	return children;
}	

shared_ptr<Task_List> Task_List::get_parent() {
	return parent;
}

void Task_List::quit() {
	command = 'q';
}
