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