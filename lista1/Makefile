CC = g++
CFLAGS = -Wall -I. # -Wextra
OBJS = main.o ManhattanDistance.o'

SRCDIR = src
OBJDIR = obj

OBJECTS = $(addprefix $(OBJDIR)/, main.o ManhattanDistance.o BFS8Puzzle.o)

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR):	
	mkdir $(OBJDIR)

clean:
ifeq ($(OS),Windows_NT)
	-del /Q $(OBJDIR) $(BINDIR)
else
	-rm -rf $(OBJDIR) $(BINDIR)
endif
