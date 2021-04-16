#include "util.h";
#include <fstream>;
#include <iostream>;


std::string* parseFileData(std::string fileName)
{
	int numVertexes, numEdges;
	std::string line;
	std::string word;
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		file >> numVertexes;
		file >> numEdges;
		std::string* data = new std::string[numEdges];
		for (int i = 0; i < numEdges; i++)
		{
			word = "";
			file >> line; 
			word += (line + " ");
			file >> line; 
			word += (line + " ");
			file >> line; 
			word += (line + " ");
			file >> line;
			word += (line + " ");
			data[i] = word;	
		}
		return data;
	}
	return NULL;
}
int getFileVertexes(std::string fileName)
{
	int numVertexes = INT_MAX;
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		file >> numVertexes;
	}
	return numVertexes;
}
int getFileEdges(std::string fileName)
{
	int numEdges = INT_MAX;
	int numVertexes = INT_MAX;
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		file >> numVertexes;
		file >> numEdges;
	}
	return numEdges;
}
adjList getCommand(adjList a)
{
	std::string line;
	std::string command;
	int source, destination, flag;
	int s, d;

	while (1)
	{
		std::cin >> line;
		command = line.substr(0, line.find(" "));
		if (command == "find") {
			std::cin >> source; std::cin >> destination; std::cin >>flag;
			if (source == NULL || destination == NULL || !(flag == 0 || flag == 1) )
			{
				std::cout << "Error: invalid find query\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin.clear();
				line = "";
				command = "";
			}
			else {
				std::cout << "find" << " -> Source:" << source << " " << "Dest:" << destination << " " << "Flag:" << flag << " " << std::endl;
				shortestPath(&a, source, destination, flag);
			}
		}
		else if (command == "write") { 
			/*
			std::cin >> line; std::cin >> s; std::cin >> d;
			std::cout << "write path" << " -> s:" << s << " " << "d:" << d <<  std::endl;
			if (getQueryCount() == 0)
			{
				std::cout << "Error: no path computation done\n";

			}
			else if (!(isQueried(s, d)))
			{
				std::cout << "Error: invalid source destination pair\n";
			}
			else if(!(isQueriedPathShortest(s,d)))
			{
				std::cout << "Shortest path: " << queriedPath(s,d) << std::endl;
				std::cout << "The path weight is :" << queriedWeight(s,d) << std::endl;
			}
			else
			{
				std::cout << "Path not known to be shortest :" << queriedPath(s, d) << std::endl;
				std::cout << "The path weight is :" << queriedWeight(s, d) << std::endl;
				//No s-d path exists in the graph G.
				//No s-d path has been computed.
			}
			*/
		}
		else if (command == "stop") { std::cout << "stop" << std::endl; garbage(a); exit(0); }
		else if (command == "") {}
		else { std::cout << "invalid input" << command << std::endl; }
		line = "";
		std::cin.clear();

		//find <source> <destination> <flag>
		//write path <s> <d>
		//stop


	}
	return a;
}
void garbage(adjList a)
{
	//free memory
}