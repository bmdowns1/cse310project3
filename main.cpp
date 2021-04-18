#include "util.h"
using namespace std;
int main(int argc, char** argv)
{
	string fileName = "test.txt";
	bool isDirected = true;
	//command line interpreter for ./dijkstra <graph> <direction>
	/*
	if (argc > 2) //correct num of arguments
	{
		fileName = argv[2]; //set fileName to <graph>
		if (argv[3] == "directed") //user specified directed
		{
			isDirected = true;
		}
		else if(argv[3] == "undirected") //user specified undirected
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
		badArguments();
		exit(0);
	}
	*/

	string* data = parseFileData(fileName);
	int numVertexes = getFileVertexes(fileName);
	int numEdges = getFileEdges(fileName);
	adjList a = initializeAdjList(numEdges, numVertexes, isDirected);
	a = populateAdjList(data, a);
	printAdjList(a);
	while (1) { a = getCommand(a); }


}