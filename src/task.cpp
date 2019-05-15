// task.cpp
// Class to represent tasks

#include "task.h"

#include <ncurses.h>

using namespace std;

/*--- Task Methods ---*/
Task::Task(string n, unsigned int pr, shared_ptr<Date> d, shared_ptr<Recurrence> r,
	   shared_ptr<Task_List> pa)
	: name(n), priority(pr), date(d), recurrence(r), parent(pa)
{
// Empty constructor body
}

void Task::display_and_prompt() {
	printw("Name: " + name + "\n");
	printw("Due Date: " + date->month + "/" + date->day + "/" + date->year + "\n");
	printw("Recurrence: 
