SDIR = src
ODIR = build
CC = g++
CFLAGS = -Wall -g -lncurses

_OBJ = main.o todo_list.o task_list.o task.o date.o date_parser.o date_factory.o display.o\
       recurrence.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

_DEPS = todo_list.h task_list.h task.h date.h date_parser.h date_factory.h display.h recurrence.h
DEPS = $(patsubst %, $(SDIR)/%, $(_DEPS))

todo : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean :
	rm $(ODIR)/*.o
	rm todo
