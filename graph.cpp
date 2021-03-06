#include "graph.h"
using namespace std;
adjList initializeAdjList(int numEdges, int numVertexes, bool isDirected)
{
	adjList* a = new adjList();
	a->isDirected = isDirected;
	a->numEdges = numEdges;
	a->numVertexes = numVertexes;
	a->e = new edge*[numVertexes]; 

	for (int i = 0; i < numVertexes; i++)
	{
		a->e[i] = new edge();
	}
	return *a;
}
adjList populateAdjList(string* data, adjList a)
{
	for (int i = 0; i < a.numEdges; i++)
	{
		std::string delimiter = " ";
		std::string tIndex = data[i].substr(0, data[i].find(delimiter));
		std::string tmp = data[i].substr(data[i].find(delimiter) + 1, data[i].length());
		std::string tUVertex = tmp.substr(0, tmp.find(delimiter));
		tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.length());
		std::string tVVertex = tmp.substr(0, tmp.find(delimiter));
		tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.length());
		std::string tWeight = tmp.substr(0, data[i].length());
		int uVertex = atoi(tUVertex.c_str());
		int vVertex = atoi(tVVertex.c_str());
		double weight = stod(tWeight.c_str());
		//Route 1: leave the duplicate edges in, djis will take care of it
		//route 2: handle the duplicates, but then we have to manually relax the weight
		edge* node = a.e[uVertex - 1];
		if (!(a.e[uVertex - 1]->init)) {

			node->u = uVertex;
			node->v = vVertex;
			node->init = true;
			node->weight = weight;
		}
		else { 
			bool noDuplicate = true;
			if (noDuplicate)
			{
				edge* initial = new edge();
				initial->u = uVertex;
				initial->v = vVertex;
				initial->init = true;
				initial->weight = weight;
				initial->next = a.e[uVertex - 1];
				a.e[uVertex - 1] = initial;
			}
		}
		//IS UNDIRECTED
		if (!a.isDirected)
		{
			edge* undirectedNode = a.e[vVertex - 1];
			if (!(a.e[vVertex - 1]->init)) {

				undirectedNode->u = vVertex;
				undirectedNode->v = uVertex;
				undirectedNode->init = true;
				undirectedNode->weight = weight;
			}
			else {
				bool noDuplicate = true;
			/* BROKE - HALF WORKS
				edge* iterator = a.e[vVertex - 1];
				while (iterator != NULL)
				{
					if (iterator->v == uVertex)
					{
						noDuplicate = false;
					}
					iterator = iterator->next;
				}
				delete iterator;
				*/
				if (noDuplicate)
				{
					edge* initial = new edge();
					initial->u = vVertex;
					initial->v = uVertex;
					initial->init = true;
					initial->weight = weight;
					initial->next = a.e[vVertex - 1];
					a.e[vVertex - 1] = initial;
				}
			}
		}


	}
	return a;
}

void printAdjList(adjList a)
{
	edge* iterator = NULL;
	cout << "ADJ LIST:" << endl;
	for (int i = 0; i < a.numVertexes; i++)
	{
		cout << "[" << i+1 << "]\t";
		iterator = a.e[i];
		while (iterator != NULL)
		{
			cout << iterator->v << " ";
			iterator = iterator->next;
		}
		cout << endl;
	}
	delete iterator;
}


vertex* dijkstra(adjList* adjList, int source, int destination, int flag) //1
{
	//populate vertex list
	vertex* vertexList = new vertex[adjList->numVertexes]; //create vertex list
	for (int i = 0; i < adjList->numVertexes; i++) {vertexList[i].id = i+1;} //populate vertex list ids
	HEAP* queue = initializeHeap(adjList->numVertexes); //make a heap with capacity = numVertexes
	vertex* src = new vertex(); //create the source vertex
	src->id = source; //populate source id
	src->color = 1; //populate source data to GREY
	src->distance = 0;//populate source distance to itself = 0
	src->predecessor = 0;//populate source distance pred as no pred              //was NULL	
	insertHeap(queue, src, flag); //insert the vertex into the heap
	while (queue->size != 0) { //While Q != Empty
		vertex* extracted = extractMin(queue, flag); //Pop the min of the heap
		extracted->color = 2; // u.color = black
		vertexList[extracted->id - 1] = *extracted; //update data records
		if (extracted->id == destination) //if u == t
		{
			vertexList[extracted->id - 1] = *extracted; //return 0
			delete src;
			delete queue;
			return vertexList; //return 0 THE SOURCE HAS FOUND DESTINATION
		}
		//CODE THAT LOOPS THRU LINKED LIST AT adjList->e[extracted->id] and gets v
		edge* iterator = adjList->e[extracted->id - 1];
		while (iterator != NULL)
		{
			vertex* neighbor = &vertexList[iterator->v - 1];
			if (neighbor->color == 0) { //if neighbor is white
				neighbor->distance = extracted->distance + iterator->weight; // v.d = u.d + w(u,v)
				neighbor->predecessor = extracted->id;
				neighbor->color = 1;
				if (!(isInHeap(queue, *neighbor))) {
					{
						insertHeap(queue, neighbor, flag);
					}
				}
			}
			else if (neighbor->distance > extracted->distance + iterator->weight) // else if v.d > u.d +w(u,v)
			{
				neighbor->predecessor = extracted->id;
				decreaseKey(queue, neighbor, extracted->distance + iterator->weight, flag);										//FIX ME
			}
			iterator = iterator->next;
			}
			/*
			for (int i = 0; i < adjList->numVertexes; i++) { //iterate through each endpoint/neighbor in Adjacency List for u
				if (adjList->e[extracted->id - 1][i].init) { //if the neighbor is initialized																		FIX ME
					vertex* neighbor = &vertexList[adjList->e[extracted->id - 1][i].v - 1]; //neighbor v is neighbor of u											fix me
					if (neighbor->color == 0){ //if neighbor is white

						neighbor->distance = extracted->distance + adjList->e[extracted->id - 1][i].weight; // v.d = u.d + w(u,v)									FIX ME
						neighbor->predecessor = extracted->id; //v.pi = u
						neighbor->color = 1; //v.color = grey
						if (!(isInHeap(queue, *neighbor))){
							{
								insertHeap(queue, neighbor, flag);
							}
						}
					}

					else if (neighbor->distance > extracted->distance + adjList->e[extracted->id - 1][i].weight) // else if v.d > u.d +w(u,v)
					{
						neighbor->predecessor = extracted->id;
						decreaseKey(queue, neighbor, extracted->distance + adjList->e[extracted->id - 1][i].weight, flag);										//FIX ME
					}
				}
			}
			*/
		delete iterator;
	}
		delete src;
		delete queue;
		return vertexList;
}

void shortestPath(int source, int destination, vertex* vertexList)
{
	int path[100];
	for (int i = 0; i < 100; i++)
	{
		path[i] = -1;
	}
	path[99] = destination;
	int j = 98;
	int i = destination;
	while (vertexList[i - 1].predecessor != source)
	{
		path[j] = vertexList[i - 1].predecessor;
		i = vertexList[i - 1].predecessor;
		j--;
	}
	path[j] = source;
	cout << "<";

	for (int i = 0; i < 100; i++)
	{
		if (path[i] != -1)
		{
			cout << path[i];
			if (i != 99)
			{
				cout << ", ";
			}
		}
	}
	cout << ">" << endl;
}
void weightOf(int source, int destination, vertex* vertexList)
{
	printf("The path weight is: %12.4f\n", vertexList[destination - 1].distance);
}
