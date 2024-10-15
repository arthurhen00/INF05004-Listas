CC = g++
CFLAGS = -Wall -O3 # -Wextra
SEARCHDIR = $(SRCDIR)/SearchAlg
SRCDIR = src
OBJDIR = obj

OBJECTS = $(addprefix $(OBJDIR)/, main.o puzzle.o BFS.o)

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) -c $<  -o $@ $(CFLAGS)

$(OBJDIR)/BFS.o: $(SEARCHDIR)/BFS.cpp | $(OBJDIR)
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