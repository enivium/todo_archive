// task.cpp
// Class to represent tasks

#include "task.h"

#include <ncurses.h>

using namespace std;

/*--- Task Methods ---*/
void Task::display_info() {
	printw("Name: " + name + "\n");

	printw("Due Date: ");
	if (due_date > *(parent->get_current_date)) {
		attron(COLOR_PAIR(overdue));
	}
	printw(due_date->month + "/" + due_date->day + "/" + due_date->year + "\n");
	attrset(A_NORMAL);

	printw("Recurrence: " + recurrence->display_string() + "\n");

	printw("Recurr From: ");
	if (recurr_from_current) {
		printw("Current Date");
	} else {
		printw("Due Date");
	}
	printw("\n");

	printw("Priority: ");
	attron(COLOR_PAIR(priority));
	printw(to_string(priority) + "\n");
	attrset(A_NORMAL);

	printw("Group: ");
	attron(A_BOLD);	
	printw(parent->list_display() + "\n");
	attrset(A_NORMAL);
}
	
Task::Task(string n, unsigned int pr, shared_ptr<Date> d, shared_ptr<Recurrence> r,
	   bool f, shared_ptr<Task_List> pa)
	: name(n), priority(pr), due_date(d), recurrence(r), recurr_from_current(f), parent(pa)
{
	// Empty constructor body
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
				delete_task();
				break;
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
		delete_task();			
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
	due_date = prompt_date();	
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
				name = prompt_name();
				break;
			case 'r':
				erase();
				recurrence = prompt_recurrence();
				recurr_from_current = prompt_recurr_ref();
