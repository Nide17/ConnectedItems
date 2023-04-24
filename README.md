# Connected Items Solution

This repository contains a C++ implementation of the Breadth-First Search (BFS) algorithm to solve the connected items problem. The solution reads input data from a file and stores it in an adjacency list, then applies BFS to find connected groups of items. The groups are sorted based on their sizes, x1 and y1 values, and the results are written to an output file

## Problem Definition

The connected items problem involves finding groups of vertices in a graph that are connected and sorting them based on size and location. The input is a file containing a list of edges in the format (x1, y1, x2, y2, connected), where the connected value 1 indicates that the two vertices (x1, y1) and (x2, y2) are connected and not connected otherwise. The goal is to output the edges in the format (x1, y1, x2, y2, group number), where the group number is a unique identifier for each connected group.

## Implementation Details

The solution reads input data from a file and stores it in an adjacency list. It then applies the BFS algorithm to find connected groups of items. The groups are sorted based on their sizes, x1 and y1 values, and the results are written to an output file.

The code consists of two main functions: breadthFirstSearch() and getConnectedItems(). The breadthFirstSearch() function takes a starting vertex, the adjacency lists representing the graph, a map to store the visited vertices, and a map to store the group number of each vertex. It implements the BFS algorithm by using a queue to store the vertices to be processed. It starts from a selected starting vertex, marks it as visited, adds it to the group with the group number, and then iterates through the adjacent vertices, marking them as visited and adding them to the queue. This process continues until the queue is empty, which means all vertices connected to the starting vertex have been visited and processed.

The getConnectedItems() function reads input data from a file using file I/O operations. It opens the input file for reading and the output file for writing. It reads the input file line by line, parsing the data to extract the coordinates and the connection status of the items with the help of the fgets and sscanf functions. For each connected item, it is added to the queue to be processed later. This process continues until the queue becomes empty, indicating that all reachable vertices have been visited.

After BFS traversal, the program prints out the order in which the vertices were visited during the traversal. This can be useful in analyzing the connectivity of the graph and identifying any isolated vertices.

Overall, this program provides a simple implementation of BFS traversal on an undirected graph using an adjacency list representation. However, it can be extended to handle directed graphs and other representations, such as adjacency matrices or edge lists.

## Dependencies

The solution requires a C++ compiler that supports C++11 or higher. It also uses the following libraries:

    chrono: for tracking time statistics
    unistd.h: for getting memory statistics

##### Input File Format

**The input file should contain lines in the following format:**

    (x1, y1, x2, y2, connected)

Where:

    x1 and y1 are the coordinates of the first vertex
    x2 and y2 are the coordinates of the second vertex
    connected is 1 if the vertices are connected, else 0

For example:

    (1, 2, 3, 4, 1)
    (3, 4, 5, 6, 0) 
    (5, 6, 7, 8, 1)

This would contain 3 vertices: (1, 2), (3, 4) and (5, 6). (1, 2) is connected to (3, 4) but (3, 4) is not connected to (5, 6).

##### Output File Format

The output file will contain the connected groups in the following format:

    (x1, y1, x2, y2, group number)

Where:

    x1 and y1 are the coordinates of the first vertex in the group
    x2 and y2 are the coordinates of the second vertex in the group
    group number is the group number for that group

The groups will be sorted by:

    Size of the group (descending order)
    x1 coordinate (ascending order)
    y1 coordinate (ascending order)

For example, for the input file above, the output would be:

    Format: (x1, y1, x2, y2, group number)
    (1, 2, 3, 4, 1) 
    (5, 6, 7, 8, 2)

Group 1 contains (1, 2) and (3, 4) while Group 2 contains (5, 6) and (7, 8).

### Compilation

**Requirements**

To compile and run this program, you will need the following:

    CMake - Install cmake and make if they are not already installed on your system.
    A C++ compiler (such as GCC or Clang)

**Building**

To build the program, follow these steps:

    Clone or download this repository.
    Navigate to the root directory of the repository.
    Create a new directory called bin.
    Navigate to the bin directory.
    Run cmake ...
    Run make.

To run the program, use:

    ./homework inputFilePath outputFilePath

Where inputFilePath is the path to the input file and outputFilePath is the path where the output file should be generated.

#### Authors

    Suryaprakash Kompalli
    Niyomwungeri Parmenide Ishimwe
