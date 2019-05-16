// task.cpp
// Class to represent tasks

#include "task.h"

#include <ncurses.h>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <regex>

using namespace std;

/*--- Task Methods ---*/
void Task::display_info() {
	string name_string("Name: " + name + "\n");
	printw(name_string.c_str());

	printw("Due Date: ");
	if (due_date > *(parent->get_current_date)) {
		attron(COLOR_PAIR(overdue));
	}
	string date_string(to_string(due_date->month) + "/" + to_string(due_date->day) + "/" + 
			   to_string(due_date->year) + "\n");
	printw(date_string.c_str());
	attrset(A_NORMAL);

	string rec_string("Recurrence: " + recurrence->display_string() + "\n");
	printw(rec_string.c_str());

	printw("Recurr From: ");
	if (recurr_from_current) {
		printw("Current Date");
	} else {
		printw("Due Date");
	}
	printw("\n");

	printw("Priority: ");
	attron(COLOR_PAIR(priority));
	string priority_string(to_string(priority) + "\n");
	printw(priority_string.c_str());
	attrset(A_NORMAL);

	printw("Group: ");
	attron(A_BOLD);	
	string group_string(parent->list_display() + "\n");
	printw(group_string.c_str());
	attrset(A_NORMAL);
}

string Task::prompt_string() {
	char input = 0;
	string input_str;

	echo();
	while (input != '\n') {
		input = getch();
		refresh();
		if (input != '\n') {
			input_str += to_string(input);
		}
	}
	noecho();

	return input_str;
}

void Task::prompt_name() {
	printw("Task Name:\n");
	printw(">");
	name = prompt_string();
}	

void Task::prompt_date() {
	printw("Due Date:\n");

	bool valid_input = false;
	while (!valid_input) {
		printw(">");
		new_date = df->make_date(prompt_string(), parent->get_current_view());

		if (new_date == nullptr) {
			printw("ERROR: Invalid Format!\n");
			continue;
		}
	
		if (!df->is_valid_date(new_date)) {
			printw("ERROR: Invalid Date!\n");
			continue;
		}

		valid_input = true;
	}

	date = new_date;
}

void Task::prompt_recurrence() {
	char input = 0;

	printw("Recurrence:\n");
	printw("[w]eekdays\n");
	printw("[i]ntervals\n");
	printw("[n]one\n");
	refresh();
	
	while (input != 'w' && input != 'i') {
		input = getch();
	}

	if (input == 'w') {
		set<unsigned int> wdays_set;

		bool valid_input = false;
		while (!valid_input) {
			printw("Weekdays:\n");
			printw(">");		
			string wdays(prompt_string());
			replace(wdays.begin(), wdays.end(), ',', ' ');
			istringstream wdays_strm(wdays);

			string wday;
			while (wdays_strm >> wday) {
				for (auto &c : wday) {
					tolower(c);
				}
				int wday_int = wkday_to_int(wday);
				if (wday_int != -1) {
					wdays_set.insert(wday_int);
				}
			}

			if (wdays_set.empty()) {
				printw("ERROR: Invalid Input!\n");
				continue;
			}

			valid_input = true;
		}

		vector<unsigned int> wday_vec;
		copy(wdays_set.begin(), wdays_set.end(), back_inserter(wday_vec)); 
		sort(wdays_vec.begin(), wdays_vec.end());
		recurrence = make_shared<Weekday_Recurrence(wdays_vec);
	} else if (input == 'i') {
		char u = 0;

		printw("Units:\n");		
		printw("[d]ays\n");
		printw("[w]eeks\n");
		printw("[m]onths\n");
		printw("[y]ears\n");
		refresh();

		while (u != 'd' && u != 'w' && u != 'm' && u != 'y') {
			u = getch();		
		}

		string units;
		switch (u) {
			case 'd':
				units = "day";
				break;
			case 'w':
				units = "week";
				break;
			case 'm':
				units = "month";
				break;
			case 'y':		
				units = "year";
				break;
		}

		printw("Interval:\n");
		string interval_str;
		regex r("^\d+$");	

		bool valid_input = false;
		while (!valid_input) {
			printw(">");
			interval_str = prompt_string();

			if (!regex_match(interval_str, r)) {
				printw("ERROR: Invalid Input!\n");
				continue;	
			}

			valid_input = true;
		}

		unsigned int interval;
		istringstream interval_strm(interval_str);
		interval_strm >> interval;

		recurrence = make_shared<Unit_Recurrence>(interval, units);
	} else {
		recurrence = nullptr;
	}

	if (input == 'w' || input == 'i') {
		char rec = 0;			

		printw("Recurr From:\n");		
		printw("[c]urrent date\n");
		printw("[d]ue date\n");
		refresh();

		while (rec != 'c' && rec != 'd') {
			rec = getch();		
		}

		if (rec == 'c') {
			recurr_from_current = true;
		} else {
			recurr_from_current = false;
		}
}

void Task::prompt_priority() {
	printw("Priority:\n");	
	attron(COLOR_PAIR(p1));
	printw("[1]\n");
	attron(COLOR_PAIR(p2));
	printw("[2]\n");
	attron(COLOR_PAIR(p3));
	printw("[3]\n");
	attrset(A_NORMAL);
	refresh();

	char input = 0;
	while (input != '1' && input != '2' && input != '3') {
		input = getch();
	}

	switch (input) {
		case '1':
			priority = 1;
			break;
		case '2':
			priority = 2;
			break;
		case '3':
			priority = 3;
			break;
	}
}

void Task::prompt_group() {
	printw("Group:\n");
	
	bool group_selected = false;
	while (!group_selected) {
		string parent_string(parent->list_display());
		if (parent_string == "") {
			parent_string = "None";
		}
		parent_string = "1) " + parent_string + "\n";
		printw(parent_string.c_str());

		vector<shared_ptr<Task_List>> children = parent->get_children();
		unsigned int idx = 2;
		for (shared_ptr<Task_List> child : children) {
			string child_string(to_string(idx) + ")\t" + child->list_display() + "\n");
			printw(child_string.c_str());
		}
		
		bool parent_exists = false; 
		if (parent->get_parent() != nullptr) {
			printw("[u]p a level\n");
			parent_exists = true;
		}

		string input;
		regex r;	
		if (parent_exists) {
			r.assign("^(\d+|u)$");
		} else {
			r.assign("^\d+$");
		}
		bool valid_input = false;
		while (!valid_input) {
			printw(">");
			input = prompt_string();

			if (!regex_match(interval_str, r)) {
				printw("ERROR: Invalid Input!\n");
				continue;	
			}

			valid_input = true;
		}

		if (input == "1") {
			group_selected = true;	
		} else if (input == "u") {
			parent = parent->get_parent();
		} else {
			unsigned int new_parent;
			istringstream input_strm(input);		
			input_strm >> new_parent;	
			parent = children.at(new_parent - 2);
		}
	}
}	

Task::Task(shared_ptr<Task_List> pa) : parent(pa) {
	df = Date_Factory::get_instance();
	prompt_name();
	prompt_date();
	prompt_recurrence();
	prompt_priority();	
	prompt_group();
}
	
void Task::display_and_prompt() {
	char command = 0;

	while (command != 'q' && command != 'b') {
		erase();
		// Print task info
		display_info();
		printw("\n");

		printw("[c]omplete\n");
		printw("[r]eschedule\n");
		printw("[e]dit\n");
		printw("[d]elete\n");
		printw("[b]ack\n");
		printw("[q]uit\n");

		command = getch();		
		refresh();

		switch (command) {
			case 'c':
				complete();
				break;
			case 'r':
				reschedule();
				break;
			case 'e':
				postpone();
				break;
			case 'd':
				parent->delete_task();
				return;
		}
	}

	if (command == 'q') {
		parent->quit();	
	}

	return;
}

string Task::list_display() {
	string group(parent->list_display());
	if (group == "") {
		return name;
	}

	return name + " (" + group + ")";
}

void Task::complete() {
	if (recurrence == nullptr) {
		parent->delete_task();			
		return;
	}

	if (recurr_from_current) {
		recurrence->recurr(due_date, parent->get_current_date());
	} else {	
		recurrence->recurr(due_date, due_date);
	}

	parent->change_task_date(due_date);
}

void Task::reschedule() {
	erase();
	prompt_date();	
	parent->change_task_date(due_date);
}

void Task::edit() {
	char command = 0;
	
	while (command != 'b' && command != 'q') {
		// Print task info
		erase();
		display_info();
		printw("\n");

		printw("Edit:\n");
		printw("[n]ame\n");
		printw("[r]ecurrence\n");
		printw("[p]riority\n");
		printw("[g]roup\n");
		printw("[b]ack\n");
		printw("[q]uit\n");

		command = getch();
		refresh();

		switch (command) {
			case 'n':
				erase();
				prompt_name();
				break;
			case 'r':
				erase();
				prompt_recurrence();
				break;
			case 'p':
				erase();
				prompt_priority();
				break;
			case 'g':
				erase();
				prompt_group();
				break;
		}
	}

	if (command == 'q') {
		parent->quit();
	}

	return;
}
