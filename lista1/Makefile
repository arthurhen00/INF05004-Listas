CC = g++
CFLAGS = -Wall -I. # -Wextra
OBJS = main.o ManhattanDistance.o BFS.o

main: $(OBJS)
	$(CC) -o main $(OBJS)
	rm *.o

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

ManhattanDistance.o: Heuristics/ManhattanDistance.cpp
	$(CC) -c Heuristics/ManhattanDistance.cpp $(CFLAGS)

BFS.o: SearchAlg/BFS.cpp
	$(CC) -c SearchAlg/BFS.cpp $(CFLAGS)

clean:
	rm main *.o
