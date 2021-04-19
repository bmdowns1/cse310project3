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
		file.close();
		return data;
	}
	return NULL;
}
int getFileVertexes(std::string fileName)
{
	int numVertexes = 214748364;
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
	int numEdges = 214748364;
	int numVertexes = 214748364;
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
	int s = 0;
	int d = 0;
	vertex* vertexList = new vertex();

	while (1)
	{
		std::cin >> line;
		command = line.substr(0, line.find(" "));
		if (command == "find") {
			std::cin >> source; std::cin >> destination; std::cin >>flag;
			if (source == NULL || destination == NULL || !(flag == 0 || flag == 1) || source > a.numVertexes || source <= 0 )
			{
				std::cout << "Error: invalid find query\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin.clear();
				line = "";
				command = "";
			}
			else {
				std::cout << "Query: find " << source << " " << destination << " " << flag << std::endl;
				s = source;
				d = destination;
				delete vertexList;
				vertexList = dijkstra(&a, source, destination, flag);
			}
		}
		else if (command == "write") { 
			std::cin >> line; std::cin >> source; std::cin >> destination;
			if (s == 0 || d == 0)
			{
				std::cout << "Error: no path computation done\n" << std::endl;
			}
			if (source == NULL || destination == NULL || source > a.numVertexes || destination > a.numVertexes || source <= 0 || destination <= 0 || s != source)
			{
				std::cout << "Query: write " << source << " " << destination << std::endl;
				std::cout << "Error: invalid source destination pair\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin.clear();
				line = "";
				command = "";
			}
			else {
				std::cout << "Query: write " << source << " " << destination << std::endl;
				/*case 1 THE SHORTEST PATH HAS BEEN COMPUTED */
				//IF BOTH NODES ARE BLACK OR IF DJISTRA VERTEXLIST = VERTEXLIST

				if (( (vertexList[destination - 1].color == 2 && vertexList[source - 1].color == 2) /* ||
					vertexList == dijkstra(&a, source, destination, 0)*/))
				{
					std::cout << "Shortest path: "; 
					shortestPath(source, destination, vertexList);
					std::cout << "The path weight is : ";
					weightOf(source, destination, vertexList);
				}
				/*case 2 THE PATH IS COMPUTED BUT IS NOT KNOWN TO BE THE SHORTEST */
				//IF THE DESTINATION IS STILL IN THE HEAP (GREY) AND DJI(SOURCE, DESTINATION).DISTANCE != INFINITY
				else if (vertexList[destination - 1].distance != 214748364 && vertexList[destination-1].color == 1){
					std::cout << "Path not known to be shortest : ";
					shortestPath(source, destination, vertexList);
					std::cout << "The path weight is: ";
					weightOf(source, destination, vertexList);
				}
				/*case 4 THE PATH DOES NOT EXIST */
				//IF THE QUEUE IS EMPTY AND DESTINATION IS WHITE
				//isHeapEmpty() && vertexList[destination - 1].color == 0
				else if (isHeapEmpty() && vertexList[destination - 1].color == 0) { std::cout << "No " << source << "-" << destination << " path exists." << std::endl; }
				/*case 3 THE PATH HAS NOT BEEN COMPUTED YET BUT COULD STILL EXIST */
				//IF THE QUEUE IS NOT EMPTY AND DESTINATION IS WHITE
				// old if (!(isHeapEmpty())) && vertexList[destination - 1].color == 0
				else if (vertexList[destination -1].color == 1 || vertexList[destination - 1].distance == 214748364)
				{
					std::cout << "No " << source << "-" << destination << " path has been computed." << std::endl;
				}
				/*unforeseen case 5*/
				else{ std::cout << "case 5" << std::endl; }
			}
		}
		else if (command == "stop") { printf("Query: stop\n");/*FREE vertexList */exit(0); }
		else if (command == "") {}
		else { std::cout << "invalid input" << command << std::endl; }
		line = "";
		std::cin.clear();
	}
	return a;
}
void garbage(adjList a)
{
	//free memory
}