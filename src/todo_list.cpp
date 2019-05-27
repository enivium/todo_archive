// todo_list.cpp
// Core to-do list class

#include "todo_list.h"

#include <ncurses.h>

using namespace std;

shared_ptr<Todo_List> Todo_List::instance = nullptr;

shared_ptr<Todo_List> Todo_List::init() {
	if (instance != nullptr) {
		return instance;
	}

	shared_ptr<Todo_List> inter(new Todo_List());
	instance = inter;

	// Set up ncurses
	initscr();
	cbreak();
	noecho();	

	// Initialize colors
	start_color();
	init_pair(overdue, COLOR_RED, -1);
	init_pair(p1, COLOR_GREEN, -1);
	init_pair(p2, COLOR_CYAN, -1);
	init_pair(p3, COLOR_BLUE, -1);

	// Get current Date
	instance->current_view = instance->df->get_current_date();

	return instance;
}
