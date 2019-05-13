// display.h
// Class for items that can be displayed and have menu options

#pragma once

class Display {
	public:
		virtual void display_and_prompt() = 0;
		virtual void list_display() = 0;
		virtual ~Display();
};
