// display.h
// Class for items that can be displayed and have menu options

#pragma once

#include <string>
#include <memory>

// Declaration to avoid circular includes
class Task_List;

class Display {
	private:
		std::string name;
	protected:
		std::string prompt_string();
		std::shared_ptr<Task_List> select_group(std::shared_ptr<Task_List>);
	public:
		virtual void display_and_prompt() = 0;
		virtual std::string list_display() = 0;
		virtual ~Display();
};
