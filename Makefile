EXEC = dijkstra
CC = g++
CFLAGS = -c -Wall

$(EXEC) :main.o heap.o util.o graph.o
	$(CC) -o $(EXEC) main.o heap.o util.o graph.o
main.o:main.cpp
	$(CC) $(CFLAGS) main.cpp
heap.o: heap.cpp heap.h 
	$(CC) $(CFLAGS) heap.cpp
util.o: util.cpp util.h
	$(CC) $(CFLAGS) util.cpp
graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) graph.cpp
clean:
	rm *.o