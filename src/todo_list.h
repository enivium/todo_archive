// todo_list.h
// Core to-do list class

#pragma once

#include "task_list.h"

class Todo_List : public Task_List {
	private:
		// Singleton items
		static std::shared_ptr<Todo_List> instance;
		Todo_List() = default;

	public:
		static std::shared_ptr<Todo_List> init();
		virtual ~Todo_List() = default;
};
