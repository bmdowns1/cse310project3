#include "util.h"
using namespace std;
int main(int argc, char** argv)
{
	string fileName = "test.txt";
	bool isDirected = false;
	//command line interpreter for ./dijkstra <graph> <direction>
	/*
	if (argc > 2) //correct num of arguments
	{
		fileName = argv[argc-1]; //set fileName to <graph>
		if (argv[argc] == "directed") //user specified directed
		{
			isDirected = true;
		}
		else if(argv[argc] == "undirected") //user specified undirected
		{
			isDirected = false;
		}
		else //user had syntax error
		{
			exit(0);
		}
	}
	else //user had incorrect num arguments
	{
		exit(0);
	}
	*/

	string* data = parseFileData(fileName);
	int numVertexes = getFileVertexes(fileName);
	int numEdges = getFileEdges(fileName);
	adjList a = initializeAdjList(numEdges, numVertexes, isDirected);
	a = populateAdjList(data, a);
	delete[] data;
	printAdjList(a);
	while (1) { a = getCommand(a); }


}