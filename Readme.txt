Project Requirements:
 - Add task
	- Step-by-step or all in one line
	- Allow abbreviations
 - Delete task
 - Set task priority
 - Assign task to group
 - Allow task to recurr
	- From due date
	- From date completed
 - Postpone task
	- Does not change due date
 - Edit task
	- Date
	- Recurrence
	- Priority
	- Group
	- Name
 - Search tasks
 - Show future date
 - Show group

Objects:
	Todo list
	Group
	Project
	Task

Structure:
	Todo list maintains map of dates
	Each date has vector of tasks
	Todo list told which date to display
	Group inherits todo list (basically acts like mini todo list)
	Group and todo list both have display() method
	Search shows day event occurs on

	Everything inherits from Display
	Group, Project, Todo_List inherit from Task_List
	Display calls on children, everything maintains parent
	Project can be sequenced/completed

Future growth:
Add one-line task creation
Add handling of function keys
Add mouse and keyboard interaction
Add undo
Add help messages?
Add way to cancel creating/editing tasks

Lessons Learned:
Use premade stuff as much as possible (tm objects)
Think about what variables and methods should be const (current_date)
Establish MVP and grow from there
Document and test as you go
Use pointers only where necessary
Worry about function/readability first, performance later
Start from interface, work down (task_list.h)
Minimize assumptions (current_date)
