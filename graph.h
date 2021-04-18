#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include "heap.h"

typedef struct EDGE
{
	int u;
	int v;
	double weight;
	bool init = false;

}edge;

typedef struct adjList
{
	edge** e;
	int numVertexes;
	int numEdges;
	bool isDirected;
}adjList;



void printAdjList(adjList a);
adjList populateAdjList(std::string* data, adjList a);
adjList initializeAdjList(int numEdges, int numVertexes, bool isDirected);
vertex* shortestPath(adjList* a, int source, int destination, int flag);
vertex* dijkstra(adjList* a, int source, int destination, int flag);
void shortestPath(int source, int destination, vertex* vertexList);
void weightOf(int source, int destination, vertex* vertexList);