#include "graph.h"

using namespace std;
adjList initializeAdjList(int numEdges, int numVertexes, bool isDirected)
{
	//declare and intialize an adjlist
	adjList* a = ((adjList*)malloc(sizeof(adjList)));
	/*a->numEdges = (int)malloc(sizeof(numEdges));
	a->numVertexes = (int)malloc(sizeof(numVertexes));
	a->isDirected = (int)malloc(sizeof(bool));
	*/
	a->isDirected = isDirected;
	a->numEdges = numEdges;
	a->numVertexes = numVertexes;

	edge** e = new edge*[numVertexes]; 
	for (int i = 0; i < numVertexes; ++i)
	{
		e[i] = new edge[numVertexes];
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


		for (int i = 0; i < a.numVertexes; i++) //iterating through v adjlist
		{
			if (uVertex == i + 1)
			{
				//is a.e[i][0] initialized
				if (a.e[i][0].init)
				{
					int index = 0;
					int j = a.numVertexes - 1;
					bool loop = true;
					//grab rightmost node

					while(j > 0 && loop)
					{
						if (a.e[i][j].init)
						{
							index = j;
							loop = false;
						}
						j--;
					}


					while (index != -1)
					{
						a.e[i][index + 1] = a.e[i][index];
						index--;
					}
					//save in first spot
					a.e[i][0].u = uVertex;
					a.e[i][0].v = vVertex;
					a.e[i][0].weight = weight;
					a.e[i][0].init = true;
				}
				else
				{
					a.e[i][0].u = uVertex;
					a.e[i][0].v = vVertex;
					a.e[i][0].weight = weight;
					a.e[i][0].init = true;
				}
			}
		}
	}
	return a;
}
				/*
			if (uVertex == i + 1)
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
			*/
/*
			bool noDuplicateEdge = true;
			if ((!(a.isDirected)) && vVertex == i + 1)
			{
				for (int j = 0; j < a.numVertexes; j++)
				{
					if (a.e[i][j].init != true)
					{
						if (a.e[i][j].v == uVertex)
						{
							noDuplicateEdge = false;
						}
					}
				}
				if (noDuplicateEdge)
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
	}
	/*
	for (int i = 0; i < a.numVertexes; i++) //through rows
	{
		for (int j = 0; j < a.numVertexes-1; j++) //through columns n^2
		{
			if (a.e[i][j].v > a.e[i][j + 1].v && (a.e[i][j + 1].init && a.e[i][j].init))
			{
				edge tmp = a.e[i][j];
				a.e[i][j] = a.e[i][j + 1];
				a.e[i][j + 1] = tmp;
				j = -1;
			}
		}
		
	}
	*/
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
				cout << a.e[i][j].v << " ";
			}
		}
		cout << endl;
	}
}

vertex* shortestPath(adjList* a, int source, int destination, int flag)
{
	vertex* vertexList = dijkstra(a, source, destination, flag);

	return vertexList;
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
	src->predecessor = NULL;//populate source distance pred as no pred
	insertHeap(queue, src, flag); //insert the vertex into the heap
	while (queue->size != 0){ //While Q != Empty
		vertex* extracted = extractMin(queue, flag); //Pop the min of the heap
		extracted->color = 2; // u.color = black
		vertexList[extracted->id - 1] = *extracted; //update data records
		if (extracted->id == destination) //if u == t
		{
			vertexList[extracted->id - 1] = *extracted; //return 0
			return vertexList; //return 0 THE SOURCE HAS FOUND DESTINATION
		}
		for (int i = 0; i < adjList->numVertexes; i++) { //iterate through each endpoint/neighbor in Adjacency List for u
			if (adjList->e[extracted->id - 1][i].init) { //if the neighbor is initialized
				vertex* neighbor = &vertexList[adjList->e[extracted->id - 1][i].v - 1]; //neighbor v is neighbor of u
				if (neighbor->color == 0){ //if neighbor is white
					
					neighbor->distance = extracted->distance + adjList->e[extracted->id - 1][i].weight; // v.d = u.d + w(u,v)
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
					decreaseKey(queue, neighbor, extracted->distance + adjList->e[extracted->id - 1][i].weight, flag);
				}
			}
		} 
	}
	return vertexList; 
}
void shortestPath(int source, int destination, vertex* vertexList)
{
	string path = ">";
	path += std::to_string(destination);
	int i = destination;
	while (vertexList[i - 1].predecessor != source)
	{
		path += " ,";
		path += std::to_string(vertexList[i - 1].predecessor);
		i = vertexList[i - 1].predecessor;
	}
	path += " ,";
	path += std::to_string(vertexList[i - 1].predecessor);
	path += "<";

	//path is the reversed string
	int n = path.length() - 1;
	for (int i = 0; i < (path.length() / 2); i++) {
		//Using the swap method to switch values at each index
		swap(path[i], path[n]);
		n = n - 1;
	}
	std::cout << path << endl;
}
void weightOf(int source, int destination, vertex* vertexList)
{
	printf("%12.4f\n", vertexList[destination - 1].distance);
}
void swap(char* x, char* y)
{
	char tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}