#include "util.h"
using namespace std;
int main(int argc, char** argv)
{
	std::string fileName = "test.txt";
	bool isDirected = false;
	//command line interpreter for ./dijkstra <graph> <direction>
		/*
		fileName = argv[argc-2]; //set fileName to <graph>
		std::string direction = argv[argc - 1];
		
		if (direction == "directed") //user specified directed
		{
			isDirected = true;
		}
		else if(direction == "undirected") //user specified undirected
		{
			isDirected = false;
		}
		//cout << fileName << endl;
		//cout << isDirected << endl;
		*/
		string* data = parseFileData(fileName);
		int numVertexes = getFileVertexes(fileName);
		int numEdges = getFileEdges(fileName);
		adjList a = initializeAdjList(numEdges, numVertexes, isDirected);
		a = populateAdjList(data, a);
		delete[] data;
		//printAdjList(a);
		while (1) { a = getCommand(a); }

	
}