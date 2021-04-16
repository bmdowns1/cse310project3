#include "graph.h"
using namespace std;
adjList initializeAdjList(int numEdges, int numVertexes, bool isDirected)
{
	//declare and intialize an adjlist
	adjList* a = ((adjList*)malloc(sizeof(adjList)));
	a->numEdges = (int)malloc(sizeof(numEdges));
	a->numVertexes = (int)malloc(sizeof(numVertexes));
	a->isDirected = (int)malloc(sizeof(bool));
	a->isDirected = isDirected;
	a->numEdges = numEdges;
	a->numVertexes = numVertexes;
	

	edge** e = new edge*[numVertexes]; 
	for (int i = 0; i < numVertexes; ++i)
	{
		e[i] = new edge[numVertexes];
		e[i]->u = new int();
		e[i]->v = new int();
		e[i]->weight = new int();
		e[i]->init = new int();
		e[i]->init = false;
	}
	a->e = e;
	a->numEdges = numEdges;
	a->numVertexes = numVertexes;
	a->isDirected = isDirected;
	return *a;
}
adjList populateAdjList(string* data, adjList a)
{
	for (int i = 0; i < a.numEdges; i++)
	{
		int* index = ((int*)malloc(sizeof(int)));
		int* uVertex = ((int*)malloc(sizeof(int)));
		int* vVertex = ((int*)malloc(sizeof(int)));
		int* weight = ((int*)malloc(sizeof(int)));
		string word = "";
		int counter = 0;
		for (int j = 0; j < 8; j++)
		{
			if (data[i][j] == ' ')
			{
				if (counter == 0) { *index = atoi(word.c_str()); counter++; }
				else if (counter == 1) { *uVertex = atoi(word.c_str()); counter++;}
				else if (counter == 2) { *vVertex = atoi(word.c_str()); counter++;}
				else if (counter == 3) { *weight = atoi(word.c_str()); counter = 0; }
				else {}
				word = "";
			}
			else
			{
				word = word + data[i][j];
			}
		}

		for (int i = 0; i < a.numVertexes; i++)
		{
			if (*uVertex == i + 1)
			{
				for (int j = 0; j < a.numVertexes; j++)
				{
					if (a.e[i][j].init != true)
					{
						a.e[i][j].u = uVertex;
						a.e[i][j].v = vVertex;
						a.e[i][j].weight = weight;
						a.e[i][j].init = true;
						break;
					}
				}
			}
			if (a.isDirected && *vVertex == i + 1)
			{
				for (int j = 0; j < a.numVertexes; j++)
				{
					if (a.e[i][j].init != true)
					{
						a.e[i][j].u = vVertex;
						a.e[i][j].v = uVertex;
						a.e[i][j].weight = weight;
						a.e[i][j].init = true;
						break;
					}
				}
			}
		}
	}
	return a;
}
void printAdjList(adjList a)
{
	cout << "ADJ LIST:" << endl;
	for (int i = 0; i < a.numVertexes; i++)
	{
		cout <<"[" <<i+1 <<"]  ";
		for (int j = 0; j < a.numVertexes; j++)
		{
			if (a.e[i][j].init == true)
			{
				cout << *a.e[i][j].v << " ";
			}
		}
		cout << endl;
	}
}

void shortestPath(adjList* a, int source, int destination, int flag)
{
	bool print = false;
	if (flag == 1) { print = true; } //get counter functionality
	vertex* vertexList = dijkstra(a, source, destination, flag);
	
}
vertex* dijkstra(adjList* a, int source, int destination, int flag) //1
{
	vertex* vertexList = new vertex[a->numVertexes]; 
	HEAP* q = initializeHeap(a->numVertexes, source);
	decreaseKey(q, source, 0, flag);
	while (!isEmpty(q)) 
	{
		vertex* u = extractMin(q, flag); 
		if (u->id = destination)
		{
			return vertexList;
		}
		for (int i = 0; i < a->numVertexes; i++) //10
		{
			if (a->e[u->id - 1][i].init)
			{
				int alt = u->d + *a->e[u->id - 1][i].weight;
				if (alt < q->v[*a->e[u->id][i].v - 1]->d)
				{
					int value = q->v[*a->e[u->id][i].v - 1]->d;
					q->v[*a->e[u->id][i].v - 1]->d = alt;
					q->v[*a->e[u->id][i].v - 1]->pi = u->id;
					if (!(isInHeap(q, q->v[*a->e[u->id][i].v - 1]->id)))
					{
						if (value == INT_MAX)
						{
							insertHeap(q, q->v[*a->e[u->id][i].v - 1]);
						}
					}
				}
			}
		} 
		vertexList[u->id] = *u; 
	}
	return vertexList; 
}



/*
1:	function Dijkstra(Graph, source) :
	2 : for each vertex v in Graph :	// Initialization
		3 : dist[v] : = infinity	// initial distance from source to vertex v is set to infinite
		4 : previous[v] : = undefined	// Previous node in optimal path from source
	5 : dist[source] : = 0	// Distance from source to source
	6 : Q : = the set of all nodes in Graph	// all nodes in the graph are unoptimized - thus are in Q
	7 : while Q is not empty :	// main loop
		8 : u : = node in Q with smallest dist[]
		9 : remove u from Q
		10 : for each neighbor v of u :	// where v has not yet been removed from Q.
			11 : alt : = dist[u] + dist_between(u, v) 
			12 : if alt < dist[v]	// Relax (u,v)
				13 : dist[v] : = alt
				14 : previous[v] : = u
	15 : return previous[]
	*/