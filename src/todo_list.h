// todo_list.h
// Todo_List class declaration

#pragma once

#include "task_list.h"


class Todo_List : public Task_List {
	private:
		static std::shared_ptr<Todo_List> instance;	// Singleton instance 
		Todo_List();

	public:
		std::shared_ptr<Todo_List> get_instance();
		virtual ~Todo_List();
};
