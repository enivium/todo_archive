// main.cpp
// Initialize objects and run application

#include "todo_list.h"

using namespace std;

int main(int argc, char **argv) {
	shared_ptr<Todo_List> todo_list = Todo_List::init();	
	todo_list->display_and_prompt();
}
