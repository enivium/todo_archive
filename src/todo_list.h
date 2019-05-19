// todo_list.h
// Core to-do list class

#pragma once

#include "task_list.h"

class Todo_List : public Task_List {
	private:
		// Singleton items
		static std::shared_ptr<Todo_List> instance;
		Todo_List();

	public:
		std::shared_ptr<Todo_List> init();
		virtual ~Todo_List();
};
