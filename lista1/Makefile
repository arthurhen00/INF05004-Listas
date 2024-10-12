CC = g++
CFLAGS = -Wall -I. # -Wextra
OBJS = main.o ManhattanDistance.o BFS.o

OBJECTS = $(addprefix $(OBJDIR)/, main.o ManhattanDistance.o BFS8Puzzle.o)

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main $(CFLAGS)

ManhattanDistance.o: Heuristics/ManhattanDistance.cpp
	$(CC) -c Heuristics/ManhattanDistance.cpp $(CFLAGS)

BFS.o: SearchAlg/BFS.cpp
	$(CC) -c SearchAlg/BFS.cpp $(CFLAGS)

clean:
ifeq ($(OS),Windows_NT)
	-del /Q $(OBJDIR) $(BINDIR)
else
	-rm -rf $(OBJDIR) $(BINDIR)
endif
