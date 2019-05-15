// todo_list.h
// Todo_List class

#pragma once

#include "task_list.h"

enum colorscheme {p1 = 1, p2 = 2, p3 = 3, overdue = 4};

class Todo_List : public Task_List {
	private:
		static std::shared_ptr<Todo_List> instance;	// Singleton instance 
		Todo_List();

	public:
		std::shared_ptr<Todo_List> init();
		virtual ~Todo_List();
};
