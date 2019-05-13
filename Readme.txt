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
