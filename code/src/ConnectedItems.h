/*
 *     Author: kompalli
 *     Co-Author: Parmenide
 */
#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <string>
#include <unistd.h>
#include <algorithm> // FOR USING THE SORT FUNCTION
#include <map> 	 	 // FOR USING THE MAP DATA STRUCTURE
#include <queue>     // FOR USING THE QUEUE DATA STRUCTURE
#include "./util/GetMemUsage.h"
#include "./util/LogManager.h"

using namespace std;

// A CLASS TO STORE AND PROCESS CONNECTED ITEMS - VERTICES
class ConnectedItems
{
public:
	typedef pair<int, int> Vertex;
	typedef vector<Vertex> VerticesList;
	typedef pair<int, VerticesList> Group;

	// A STATIC FUNCTION TO GET CONNECTED ITEMS FROM INPUT FILE AND GENERATE OUTPUT FILE WITH SORTED GROUPS
	static void getConnectedItems(char *inputFilePath, char *outputFilePath);

	// BREADTH FIRST SEARCH FUNCTION TO FIND CONNECTED GROUPS USING BREADTH-FIRST SEARCH
	static void breadthFirstSearch(const Vertex &begin, const map<Vertex, VerticesList> &adjacencyList, map<Vertex, bool> &visitedVertices, map<Vertex, int> &allVertices, int gNo);
};

// IMPLEMENTATION STEPS:
// ====================
// 1. READING FROM THE INPUT FILE AND STORING THE VERTICES OF FORM (X, Y) IN ADJACENCY LIST.
// 2. FINDING ALL VERTICES THAT ARE CONNECTED TO EACH OTHER THROUGH SOME OTHER VERTICES USING BFS - CONNECTED GROUPS
// 3. MAKING A HASHMAP: KEY VALUE PAIR WITH THE GROUP COUNT AS THE KEY AND LIST OR VECTOR OF VERTICES AS THE GROUP
// 4. SORTING THE HASHMAP BASED ON THE GROUP(VECTOR) SIZE, CONSIDER X1 AND Y1 IF THE SIZE IS THE SAME, SORT BY GROUP COUNT
// 5. PRINTING THE SORTED VERTICES TO THE OUTPUT FILE IN THE FORMAT (X1, Y1, X2, Y2, group number)  
