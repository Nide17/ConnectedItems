/*
 *     Author: kompalli
 *     Co-Author: Parmenide
 */
#include "ConnectedItems.h"

// BREADTH FIRST SEARCH FUNCTION TO FIND CONNECTED GROUPS USING BREADTH-FIRST SEARCH
void ConnectedItems::breadthFirstSearch(const Vertex &begin, const map<Vertex, VerticesList> &adjacencyLists, map<Vertex, bool> &visitedVertices, map<Vertex, int> &allVerticesGroup, int gNo)
{
    queue<Vertex> tempQueue;                // A TEMPORARY QUEUE TO STORE THE VERTICES
    tempQueue.push(begin);                  // PUSHING THE STARTING VERTEX TO THE QUEUE

    visitedVertices[begin] = true;          // MARKING THE STARTING VERTEX AS VISITED
    allVerticesGroup[begin] = gNo;          // ADDING THE STARTING VERTEX TO THE GROUP WITH THE GROUP NUMBER

    while (!tempQueue.empty())              // WHILE THE QUEUE IS NOT EMPTY - PROCESS THE QUEUE
    {
        Vertex currV = tempQueue.front();   // GET THE CURRENT VERTEX
        tempQueue.pop();                    // POP THE CURRENT VERTEX FROM THE QUEUE

        const VerticesList &list = adjacencyLists.at(currV);  // GET THE VERTICES OF THE CURRENT VERTEX

        // ITERATE THROUGH THE VERTICES OF THE CURRENT VERTEX
        for (int i = 0; i < list.size(); i++)
        {
            Vertex lt = list[i];                              // GET THE CURRENT VERTEX

            // CHECK IF THE VERTEX IS NOT VISITED BEFORE
            if (visitedVertices[lt] == false)
            {
                visitedVertices[lt] = true;                   // MARK THE VERTEX AS VISITED IF IT IS NOT VISITED BEFORE
                allVerticesGroup[lt] = gNo;                   // ADD THE VERTEX TO THE GROUP WITH THE GROUP COUNT
                tempQueue.push(lt);                           // PUSH THE VERTEX TO THE QUEUE TO PROCESS IT LATER
            }
        }
    }
}

// A STATIC FUNCTION TO GET CONNECTED ITEMS FROM INPUT FILE AND GENERATE OUTPUT FILE WITH SORTED GROUPS
void ConnectedItems::getConnectedItems(char *inputFilePath, char *outputFilePath)
{
    // OPENING THE INPUT FILE FOR READING
    FILE *inFileStream = fopen(inputFilePath, "r");
    if (!inFileStream)
    {
        char message[1024];
        sprintf(message, "Cannot open input file for reading: %s", inputFilePath);
        throw std::ios_base::failure(message);
    }

    // OPENING THE OUTPUT FILE FOR WRITING
    FILE *outFileStream = fopen(outputFilePath, "w");
    if (!outFileStream)
    {
        char message[1024];
        sprintf(message, "Cannot open output file for writing: %s", outputFilePath);
        throw std::ios_base::failure(message);
    }

    // READING THE INPUT FILE LINE BY LINE AND STORING THE DATA IN ADJACENCY LIST
    char line[1024];

    // A MAP TO STORE THE ADJACENCY LIST OF THE GRAPH
    map<Vertex, VerticesList> adjacencyLists;

    // READING THE INPUT FILE LINE BY LINE
    while (fgets(line, 1024, inFileStream) != NULL)
    {
        // READING THE LINE AND CONVERTING THE LINE TO A PAIR OF COORDINATES
        int x1, y1, x2, y2, connected;
        sscanf(line, "(%d, %d, %d, %d, %d)", &x1, &y1, &x2, &y2, &connected);

        // CHECK IF THE TWO VERTICES ARE CONNECTED AND IF THEY ARE, ADD THEM TO THE ADJACENCY LIST
        if (connected == 1)
        {
            // CONVERTING THE COORDINATES TO A VERTEX
            Vertex coord1 = {x1, y1}; 
            Vertex coord2 = {x2, y2};

            // ADDING THE VERTEX TO THE ADJACENCY LIST
            adjacencyLists[coord1].push_back(coord2); 
            adjacencyLists[coord2].push_back(coord1);         
        }
    }

    // FINDING ALL VERTICES THAT ARE CONNECTED TO EACH OTHER THROUGH SOME OTHER VERTICES USING BFS - CONNECTED GROUPS
    map<Vertex, bool> visitedVertices;          // A MAP TO STORE THE VISITED VERTICES
    map<Vertex, int> allVerticesGroup;          // A MAP TO STORE EACH VERTEX WITH THE GROUP IT BELONGS TO 
    int gNo = 1;                                // A VARIABLE TO STORE THE GROUP COUNT

    // ADDING GROUP NUMBER TO EVERY VERTEX WITH THE GROUP IT BELONGS TO - allVerticesGroup
    // FINDING ALL VERTICES THAT ARE CONNECTED TO EACH OTHER THROUGH SOME OTHER VERTICES USING BFS - CONNECTED GROUPS
    for (const auto &list : adjacencyLists)
    {
        // CHECK IF THE VERTEX IS NOT VISITED BEFORE - IF NOT, THEN CALL THE BFS FUNCTION TO FIND THE CONNECTED GROUPS
        if (visitedVertices[list.first] == false)
        {
            // CALLING THE BFS FUNCTION TO FIND THE CONNECTED GROUPS 
            breadthFirstSearch(list.first, adjacencyLists, visitedVertices, allVerticesGroup, gNo);
            
            gNo++; // WHEN FINISHED CONNECTED GROUPS, INCREMENT THE GROUP COUNT
        }
    }

    map<int, VerticesList> verticesGroups;              // A MAP TO STORE THE GROUPS WITH THE GROUP NUMBER AS THE KEY

    // PUTTING THE GROUPS IN THE MAP FOR SORTING PURPOSES - groups
    for (auto edg = allVerticesGroup.begin(); edg != allVerticesGroup.end(); edg++)
    {
        int groupIndex = edg->second;                   // GET THE GROUP NUMBER OF THE CURRENT VERTEX
        Vertex coord = edg->first;                      // GET THE CURRENT VERTEX
        verticesGroups[groupIndex].push_back(coord);    // ADD THE CURRENT VERTEX TO THE CORRESPONDING GROUP
    }

    vector<Group> sortedGroupsList;                  // A VECTOR TO STORE THE SORTED GROUPS - SORTED BY SIZE OF THE GROUP, X1 AND Y1
    sortedGroupsList.reserve(verticesGroups.size()); // RESERVING THE MEMORY FOR THE VECTOR TO STORE THE GROUPS

    // CONVERT THE GROUP MAP TO A VECTOR FOR SORTING PURPOSES
    for (auto &vGrp : verticesGroups)
    {
        // ADDING THE GROUP TO THE VECTOR - sortedGroupsList
        sortedGroupsList.push_back(make_pair(vGrp.first, vGrp.second));
    }

    // SORTING THE GROUPS IN THE VECTOR - sortedGroupsList - IN THE FOLLOWING ORDER: 1. BY SIZE OF THE GROUP 2. BY X1 3. BY Y1
    sort(sortedGroupsList.begin(), sortedGroupsList.end(), [](const Group &grp1, const Group &grp2)
         {

        // IF THE SIZES ARE EQUAL, THEN SORT BY X1 AND THEN BY Y1
		if (grp1.second.size() == grp2.second.size())
		{
			int x1grp1 = grp1.second[0].first;  // x1 FOR GROUP 1
			int y1grp1 = grp1.second[0].second; // y1 FOR GROUP 1
			int x1grp2 = grp2.second[0].first;  // x1 FOR GROUP 2
			int y1grp2 = grp2.second[0].second; // y1 FOR GROUP 2

            // IF X1 IS EQUAL, THEN SORT BY Y1
			if (x1grp1 == x1grp2)
			{
				return y1grp1 < y1grp2;
			}

            // ELSE SORT BY X1
			else
			{
				return x1grp1 < x1grp2;
			}
		}

        // ELSE SORT BY SIZE OF THE GROUP
		else
		{
			return grp1.second.size() > grp2.second.size(); // SORTING BY SIZE OF THE GROUP - DESCENDING ORDER
		}});


    // PRINTING THE GROUPS IN THE OUTPUT FILE - TITLE
    fprintf(outFileStream, "Format: (x1, y1, x2, y2, group number)\n");

    // PRINTING THE GROUPS IN THE OUTPUT FILE - CONTENT
    for (int i = 0; i < sortedGroupsList.size(); i++) // LOOPING THROUGH THE GROUPS
    {
        for (int j = 0; j < sortedGroupsList[i].second.size() - 1; j++) // LOOPING THROUGH THE VERTICES IN THE GROUP
        {
            int x1 = sortedGroupsList[i].second[j].first;       // x1 FOR THE CURRENT VERTEX
            int y1 = sortedGroupsList[i].second[j].second;      // y1 FOR THE CURRENT VERTEX
            int x2 = sortedGroupsList[i].second[j + 1].first;   // x2 FOR THE NEXT VERTEX
            int y2 = sortedGroupsList[i].second[j + 1].second;  // y2 FOR THE NEXT VERTEX

            // PRINTING THE VERTICES IN THE OUTPUT FILE
            fprintf(outFileStream, "(%d, %d, %d, %d, %d)\n", x1, y1, x2, y2, i + 1);
        }
    }

    fclose(outFileStream); // CLOSING OUT FILE STREAM
}