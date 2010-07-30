all: Edge.o Graph.o
	g++ -DDEBUG -msse2 -ffast-math -O3 -Wall DC_cooling.cpp Graph.o Edge.o -o cooling_paths
Edge.o: Edge.hpp Edge.cpp
	g++ -DDEBUG -msse2 -ffast-math -O3 -Wall -c Edge.cpp
Graph.o: Graph.hpp Graph.cpp
	g++ -DDEBUG -msse2 -ffast-math -O3 -Wall -c Graph.cpp
clean:
	rm -f cooling_paths Graph.o Edge.o
