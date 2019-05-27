// display.cpp
// Class for items that can be displayed and have menu options

#include "display.h"
#include "task_list.h"

#include <ncurses.h>
#include <regex>

using namespace std;

string Display::prompt_string() {
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

shared_ptr<Task_List> Display::select_group(shared_ptr<Task_List> base) {
	printw("Group:\n");
	while (true) {
		string base_string(base->list_display());
		if (base_string == "") {
			base_string = "None";
		}
		base_string = "1) " + base_string + "\n";
		printw(base_string.c_str());

		vector<shared_ptr<Task_List>> children = base->get_children();
		unsigned int idx = 2;
		for (shared_ptr<Task_List> child : children) {
			string child_string(to_string(idx) + ")\t" + child->list_display() + "\n");
			printw(child_string.c_str());
		}
		
		bool parent_exists = false; 
		if (base->get_parent() != nullptr) {
			printw("[u]p a level\n");
			parent_exists = true;
		}

		string input;
		unsigned int selected;
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

			if (!regex_match(input, r)) {
				printw("ERROR: Invalid Input!\n");
				continue;	
			}

			istringstream input_strm(input);		
			input_strm >> selected;	
			if (selected > children.size() + 1) {
				printw("ERROR: Invalid Input!\n");
				continue;
			}

			valid_input = true;
		}

		if (input == "1") {
			return base;
		} else if (input == "u") {
			base = base->get_parent();
		} else {
			base = children.at(selected - 2);
		}
	}
}
