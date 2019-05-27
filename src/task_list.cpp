// task_list.cpp
// Base class for objects that can hold Tasks

#include "task_list.h"
#include "date_factory.h"

#include <algorithm>
#include <regex>
#include <ncurses.h>

using namespace std;

bool Task_List::sort_by_priority(std::shared_ptr<Task> &t1, std::shared_ptr<Task> &t2) {
	if (t1->get_overdue()) {
		return true;
	}

	return t1->get_priority() < t2->get_priority();
}

void Task_List::display_tasks(vector<shared_ptr<Task>> &tasks) {
	sort(tasks.begin(), tasks.end(), sort_by_priority);
	unsigned int idx = 1;
	for (shared_ptr<Task> task : tasks) {
		if (task->get_overdue()) {
			attron(COLOR_PAIR(overdue));	
		} else {
			attron(COLOR_PAIR(task->get_priority()));
		}

		printw("%i) ", idx);
		task->list_display();
		printw("\n");
		attrset(A_NORMAL);
	
		++idx;
	}
}

unsigned int Task_List::select_task(unsigned int max_idx) {
	printw("Task:\n");

	unsigned int selected;
	string input;
	regex r("^\\d+$");	
	bool valid_input = false;
	while (!valid_input) {
		printw(">");
		input = prompt_string();

		if (!regex_match(input, r)) {
			printw("ERROR: Invalid Input!\n");
			continue;	
		}

		istringstream input_strm(input);		
		input_strm >> selected;	
		selected -= 1;
		if (selected > max_idx) {
			printw("ERROR: Invalid Input!\n");
			continue;	
		}

		valid_input = true;
	}

	return selected;
}

void Task_List::display_groups(unsigned int indent) {
	for (shared_ptr<Task_List> child : children) {
		for (unsigned int i = 0; i < indent; ++i) {
			printw("\t");
		}

		printw(child->list_display().c_str());
		printw("\n");
		child->display_groups(indent + 1);
	}
}

void Task_List::make_group() {
	shared_ptr<Task_List> parent_ptr(this);
	children.push_back(make_shared<Task_List>(parent_ptr));
}

void Task_List::erase_group() {
	shared_ptr<Task_List> current(this);
	shared_ptr<Task_List> grp_to_erase = select_group(current);
	shared_ptr<Task_List> erase_parent = grp_to_erase->get_parent();

	// If group is root group (e.g. the Todo_List) don't do anything
	if (grp_to_erase->get_parent() != nullptr) {
		// Move all tasks to parent of erased task
		for (auto pr : tasks_by_date) {
			for (shared_ptr<Task> task : pr.second) {
				task->set_group(erase_parent);
			}
		}

		// Tell all children to move tasks to parent of erased task
		for (auto child : children) {
			child->erase_group(erase_parent);
		}
	
		// Tell parent to remove reference, which causes shared_ptr to call destructor
		parent->remove_child(current);
	}
}

void Task_List::erase_group(shared_ptr<Task_List> erase_parent) {
	// Move all tasks to parent of erased task
	for (auto pr : tasks_by_date) {
		for (shared_ptr<Task> task : pr.second) {
			task->set_group(erase_parent);
		}
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

	typedef unordered_multimap<string, shared_ptr<Task>>::iterator multi_iter;
	pair<multi_iter, multi_iter> search_results;
	search_results = tasks_by_name.equal_range(search_name);

	erase();
	
	if (search_results.first == search_results.second) {
		printw("No search results found.");
		refresh();
		getch();
		return;
	}

	vector<shared_ptr<Task>> result_vector;
	for (auto iter = search_results.first; iter != search_results.second; ++iter) {
		result_vector.push_back(iter->second);
	}

	display_tasks(result_vector);
	unsigned int selected = select_task(result_vector.size() - 1);

	result_vector.at(selected)->display_and_prompt();	
}		
		
void Task_List::present_date() {
	printw("Date:\n");
	
	shared_ptr<Date> date;
	bool valid_input = false;
	while(!valid_input) {
		printw(">");
		string date_string = prompt_string();
		date = df->make_date(date_string);

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
	shared_ptr<Task_List> current(this);
	shared_ptr<Task_List> to_view = select_group(current);
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

void Task_List::display_and_prompt() {
	command = 0;

	vector<shared_ptr<Task>> current_tasks;
	auto iter = tasks_by_date.find(*current_view);
	if (iter == tasks_by_date.cend()) {
		printw("No tasks to show for this day.\n");
	} else {
		current_tasks = iter->second;
	}

	// Exit loop when command is 'q' or (if its not the root list) when it is 'b'
	while (command != 'q' && !(command == 'b' && parent != nullptr)) {
		erase();
		// Print tasks
		display_tasks(current_tasks);			
		printw("\n");

		// Print groups
		if (!children.empty()) {
			printw("Groups:\n");
			attron(A_BOLD);
			display_groups(1);
			attrset(A_NORMAL);			
		}

		printw("[c]omplete task\n");
		printw("[a]dd task\n");
		printw("[r]eschedule task\n");
		printw("[f]ocus task\n");
		printw("[d]elete task\n");
		printw("[s]earch task\n");
		printw("\n");

		printw("[m]ake group\n");
		printw("[e]rase group\n");
		printw("[v]iew group\n");
		printw("[p]resent date\n");
		if (parent != nullptr) {
			printw("[b]ack\n");
		}
		printw("[q]uit\n");

		command = getch();		
		refresh();

		switch (command) {
			case 'c':
				complete_task(current_tasks);
				break;
			case 'a':
				add_task();
				break;	
			case 'r':
				reschedule_task(current_tasks);
				break;
			case 'f':
				focus_task(current_tasks);
				break;
			case 'd':
				delete_task(current_tasks);
				break;
			case 's':
				search();
				break;
			case 'm':
				make_group();				
				break;
			case 'e':
				erase_group();
				break;
			case 'v':
				view_group();
				break;
			case 'p':
				present_date();
				break;
		}
	}
}

shared_ptr<Date> Task_List::get_current_view() {
	return current_view;
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

void Task_List::add_task() {
	shared_ptr<Task_List> current(this);
	shared_ptr<Task> new_task = make_shared<Task>(current);		
	string name = new_task->get_name();

	tasks_by_name.insert(make_pair(name, new_task));
	
	// Add each individual word in task name to map for searching
	istringstream name_strm(name);
	string key;
	while (name_strm >> key) {
		tasks_by_name.insert(make_pair(key, new_task));
	}

	Date date = *(new_task->get_due_date());
	vector<shared_ptr<Task>> tasks_on_date = (tasks_by_date.find(date))->second;
	tasks_on_date.push_back(new_task);

	if (parent != nullptr) {
		parent->add_task(new_task);
	}
}

void Task_List::add_task(shared_ptr<Task> new_task) {
	string name = new_task->get_name();

	tasks_by_name.insert(make_pair(name, new_task));
	
	// Add each individual word in task name to map for searching
	istringstream name_strm(name);
	string key;
	while (name_strm >> key) {
		tasks_by_name.insert(make_pair(key, new_task));
	}

	Date date = *(new_task->get_due_date());
	vector<shared_ptr<Task>> tasks_on_date = (tasks_by_date.find(date))->second;
	tasks_on_date.push_back(new_task);

	if (parent != nullptr) {
		parent->add_task(new_task);
	}
}	

void Task_List::complete_task(vector<shared_ptr<Task>> &tasks) {
	unsigned int selected = select_task(tasks.size() - 1);
	tasks.at(selected)->complete();
}

void Task_List::reschedule_task(vector<shared_ptr<Task>> &tasks) {
	unsigned int selected = select_task(tasks.size() - 1);
	tasks.at(selected)->reschedule();
}

void Task_List::delete_task(vector<shared_ptr<Task>> &tasks) {
	unsigned int selected = select_task(tasks.size() - 1);
	tasks.at(selected)->delete_task();	
}

void Task_List::focus_task(vector<shared_ptr<Task>> &tasks) {
	unsigned int selected = select_task(tasks.size() - 1);
	tasks.at(selected)->display_and_prompt();	
}

void Task_List::reschedule_task(shared_ptr<Task> task, Date &old_date) {
	vector<shared_ptr<Task>> current_loc = (tasks_by_date.find(old_date))->second;
	
	// Erase-remove idiom
	current_loc.erase(remove(current_loc.begin(), current_loc.end(), task), current_loc.end());	

	// Add to new date
	Date new_date = *(task->get_due_date());
	vector<shared_ptr<Task>> new_tasks = (tasks_by_date.find(new_date))->second;
	new_tasks.push_back(task);

	if (parent != nullptr) {
		parent->reschedule_task(task, old_date);
	}
}

void Task_List::delete_task(shared_ptr<Task> task) {
	Date task_date = *(task->get_due_date());
	vector<shared_ptr<Task>> date_vec = (tasks_by_date.find(task_date))->second;
	
	// Erase-remove idiom
	date_vec.erase(remove(date_vec.begin(), date_vec.end(), task), date_vec.end());

	string name = task->get_name();
	typedef unordered_multimap<string, shared_ptr<Task>>::iterator multi_iter;
	pair<multi_iter, multi_iter> search_results;
	search_results = tasks_by_name.equal_range(name);

	for (auto iter = search_results.first; iter != search_results.second; ++iter) {
		if (iter->second == task) {
			tasks_by_name.erase(iter);
		}
	}

	istringstream name_strm(name);
	string key;
	while (name_strm >> key) {
		search_results = tasks_by_name.equal_range(key);

		for (auto iter = search_results.first; iter != search_results.second; ++iter) {
			if (iter->second == task) {
				tasks_by_name.erase(iter);
			}
		}
	}

	if (parent != nullptr) {
		parent->delete_task(task);
	}
}
