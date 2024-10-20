CC = g++
CFLAGS = -I . -Wall -O3# -Wextra
SEARCHDIR = $(SRCDIR)/SearchAlg
SEARCHDIRR = $(SRCDIR)/Heuristics
SRCDIR = src
OBJDIR = obj

OBJECTS = $(addprefix $(OBJDIR)/, main.o Puzzle.o Search.o)

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/Search.o: $(SEARCHDIR)/Search.cpp | $(OBJDIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR):	
	mkdir $(OBJDIR)

clean:
ifeq ($(OS),Windows_NT)
	-del /Q $(OBJDIR) $(BINDIR)
	-del main.exe
else
	-rm main
	-rm -rf $(OBJDIR) $(BINDIR)
endif

test:
	./main -astar 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
	./main -bfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
	./main -idastar 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
	./main -idfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
	./main -gbfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
	./main -astar 7 11 8 3 14 0 6 15 1 4 13 9 5 12 2 10,12 9 0 6 8 3 5 14 2 4 11 7 10 1 15 13,13 0 9 12 11 6 3 5 15 8 1 10 4 14 2 7