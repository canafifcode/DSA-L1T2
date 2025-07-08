// GraphADT.h
#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H

#include "linkedList.h"
// Forward declaration of linkedList (replace with #include if you have a header file for linkedList)
class linkedList;

class GraphADT {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~GraphADT() {}

    // Add a new node v to the graph
    virtual void AddNode(int v) = 0;

    // Add a new edge (u, v) in the graph
    virtual void AddEdge(int u, int v) = 0;

    // Check whether there is an edge (u, v) between node u and node v
    virtual bool CheckEdge(int u, int v) const = 0;

    // Remove node v from the graph
    virtual void RemoveNode(int v) = 0;

    // Remove an edge (u, v) from the graph
    virtual void RemoveEdge(int u, int v) = 0;

    // Check whether a path exists between node u and node v
    virtual bool CheckPath(int u, int v) const = 0;

    // Find the shortest path between node u and node v
    virtual void FindShortestPath(int u, int v) const = 0;

    // Find the length of the shortest path between node u and node v
    virtual int FindShortestPathLength(int u, int v) const = 0;

    // Find the neighbors of the node u. YourListType is the data type of your own list.
    virtual linkedList GetNeighbors(int u) const = 0;

};

#endif // GRAPH_ADT_H
