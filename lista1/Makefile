CC = g++
CFLAGS = -Wall -I. # -Wextra
OBJS = main.o ManhattanDistance.o

main: $(OBJS)
	$(CC) -o main $(OBJS)
	rm *.o

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

ManhattanDistance.o: ManhattanDistance.cpp
	$(CC) -c ManhattanDistance.cpp $(CFLAGS)

BFS8Puzzle.o: BFS8Puzzle.cpp
	$(CC) -c BFS8Puzzle.cpp $(CFLAGS)

clean:
	rm main *.o
