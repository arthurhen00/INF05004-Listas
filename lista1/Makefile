CC = g++
CFLAGS = -Wall -I. # -Wextra
OBJS = main.o ManhattanDistance.o BFS.o

main: $(OBJS)
	$(CC) -o main $(OBJS)
	rm *.o

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

ManhattanDistance.o: src/Heuristics/ManhattanDistance.cpp
	$(CC) -c src/Heuristics/ManhattanDistance.cpp $(CFLAGS)

BFS.o: src/SearchAlg/BFS.cpp
	$(CC) -c src/SearchAlg/BFS.cpp $(CFLAGS)

clean:
	rm main *.o