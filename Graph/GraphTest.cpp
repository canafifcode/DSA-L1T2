#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GraphADT.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
#include <vector>

// Toggle between implementations
//#define USE_ADJACENCY_LIST
#define USE_ADJACENCY_MATRIX

int main()
{
    //std:: cout<<"hello world"<<std::endl;
#ifdef USE_ADJACENCY_LIST
    std::cout << "Using Adjacency List Implementation\n";
    GraphADT* graph = new AdjacencyListGraph();
#elif defined(USE_ADJACENCY_MATRIX)
    std::cout << "Using Adjacency Matrix Implementation\n";
    GraphADT* graph = new AdjacencyMatrixGraph();
#else
    std::cerr << "Please define a graph implementation macro.\n";
    return 1;
#endif

    std::ifstream infile("input.txt");
    //freopen("output.txt", "w", stdout);
    freopen("output2.txt", "w", stdout);
    if (!infile.is_open())
    {
        std::cerr << "Failed to open input.txt\n";
        delete graph;
        return 1;
    }

    int u, v;
    while (infile >> u >> v)
    {
        graph->AddEdge(u, v);
    }
    std::cout << "Graph loaded from file.\n\n";

    // Test shortest paths and their lengths
    int testPairs[][2] = {{1, 10}, {3, 15}, {5, 14}, {2, 8}, {7, 12},{1,12},{2, 11},{6,13}};
    for (auto& pair : testPairs)
    {
        std::cout << "Shortest path from " << pair[0] << " to " << pair[1] << ":\n";
        graph->FindShortestPath(pair[0], pair[1]);
        std::cout << "Length: " << graph->FindShortestPathLength(pair[0], pair[1]) << "\n\n";
    }

    // Test CheckEdge and RemoveEdge
    std::cout << "Edge (5,6) exists? " << (graph->CheckEdge(5, 6) ? 1 : 0)<< "\n";
    graph->RemoveEdge(5, 6);
    std::cout << "Edge (5,6) exists after removal? " << (graph->CheckEdge(5, 6) ? 1 : 0) << "\n\n";

    // Test CheckPath (connectivity)
    int pathTests[][2] = {{1, 15}, {10, 5}, {8, 14}, {1, 100}};
    for (auto& pair : pathTests)
    {
        std::cout << "Path exists from " << pair[0] << " to " << pair[1] << "? ";
        std::cout << (graph->CheckPath(pair[0], pair[1]) ? "Yes" : "No") << "\n";
    }
    std::cout << "\n";

    // Test RemoveNode
    std::cout << "Removing node 7...\n";
    graph->RemoveNode(7);
    std::cout << "Path exists from 1 to 7? " << (graph->CheckPath(1, 7) ? "Yes" : "No") << "\n";
    std::cout << "Edge (6,7) exists? " << graph->CheckEdge(6, 7) << "\n\n";

    // Add some edges/nodes dynamically
    std::cout << "Adding edge (7, 20)...\n";
    graph->AddEdge(7, 20);
    std::cout << "Path exists from 7 to 20? " << (graph->CheckPath(7, 20) ? "Yes" : "No") << "\n";

    // Shortest path after addition
    graph->FindShortestPath(7, 20);
    std::cout << "Length: " << graph->FindShortestPathLength(7, 20) << "\n";

    std::cout << "Neighbors of node 3: ";
    auto neighbors = graph->GetNeighbors(3);
    for (Node* current = neighbors.getHead(); current != nullptr; current = current->next) {
        std::cout << current->element << " ";
    }
    std::cout << "\n";


    delete graph;
    return 0;
}
