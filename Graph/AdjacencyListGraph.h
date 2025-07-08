#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include "linkedList.h"
#include "queue.h"

class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    linkedList *adjacencyList;
    int size;
    int capacity;
    int *nodeID;

    int findNodeIndex(int v) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (nodeID[i] == v)
            {
                return i;
            }
        }
        return -1;
    }

    void resizeList()
    {
        // Resize the adjacency list and nodeID array if necessary
        if (size < capacity / 2)
        {
            capacity /= 2;
        }
        else if (size >= capacity)
        {
            capacity *= 2;
        }
        else
        {
            return;
        }
        linkedList *newList = new linkedList[capacity];
        int *newNodeID = new int[capacity];
        for (int i = 0; i < size; ++i)
        {
            newList[i] = adjacencyList[i];
            newNodeID[i] = nodeID[i];
        }
        delete[] adjacencyList;
        delete[] nodeID;
        adjacencyList = newList;
        nodeID = newNodeID;
    }

public:
    AdjacencyListGraph(int initialCapacity = 2) : size(0), capacity(initialCapacity)
    {
        adjacencyList = new linkedList[capacity];
        nodeID = new int[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            nodeID[i] = -1;
        }
    }
    ~AdjacencyListGraph() override
    {
        for (int i = 0; i < capacity; ++i)
        {
            adjacencyList[i].clear();
        }
        delete[] adjacencyList;
        delete[] nodeID;
    }
    void AddNode(int v) override
    {
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        int index = findNodeIndex(v);
        if (index != -1)
        {
            // std::cout << "Node " << v << " already exists.\n";
            return;
        }
        resizeList();
        index = size;
        nodeID[size] = v;
        adjacencyList[size] = linkedList();
        size++;
    }
    void AddEdge(int u, int v) override
    {
        // TODO: Add a new edge between the nodes u and v
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1)
        {
            AddNode(u);
            uIndex = findNodeIndex(u);
        }
        if (vIndex == -1)
        {
            AddNode(v);
            vIndex = findNodeIndex(v);
        }
        if (!adjacencyList[uIndex].isPresent(v))
        {
            adjacencyList[uIndex].append(v);
        }
        if (!adjacencyList[vIndex].isPresent(u))
        {
            adjacencyList[vIndex].append(u);
        }
    }

    bool CheckEdge(int u, int v) const override
    {
        // TODO: Check whether there is an edge between two nodes u and v
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //std::cout << "nodes not found.\n";
            return false;
        }
        Node *temp = adjacencyList[uIndex].getHead();
        while (temp != nullptr)
        {
            if (temp->element == v)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void RemoveNode(int v) override
    {
        // TODO: Remove a node.
        int index = findNodeIndex(v);
        if (index == -1)
        {
           // std::cout << "Node " << v << " not found.\n";
            return;
        }
        adjacencyList[index].clear();

        // Remove the node from the adjacency list
        for (int i = 0; i < size; ++i)
        {
            if (i != index)
                adjacencyList[i].deleteItem(v);
        }

        for (int i = index; i < size - 1; ++i)
        {
            adjacencyList[i] = adjacencyList[i + 1];
            nodeID[i] = nodeID[i + 1];
        }
        nodeID[size - 1] = -1;
        size--;
        resizeList();
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //std::cout << "One or both nodes not found.\n";
            return;
        }
        adjacencyList[uIndex].deleteItem(v);
        adjacencyList[vIndex].deleteItem(u);
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //std::cout << "Node not found\n";
            return false;
        }
        bool *visited = new bool[size];
        for (int i = 0; i < size; ++i)
        {
            visited[i] = false;
        }
        ListQueue queue;
        queue.enqueue(uIndex);
        visited[uIndex] = true;

        while (!queue.empty())
        {
            int current = queue.dequeue();
            if (current == vIndex)
            {
                delete[] visited;
                return true;
            }
            Node *temp = adjacencyList[current].getHead();
            while (temp != nullptr)
            {
                int neighborIndex = findNodeIndex(temp->element);
                if (neighborIndex != -1 && !visited[neighborIndex])
                {
                    visited[neighborIndex] = true;
                    queue.enqueue(neighborIndex);
                }
                temp = temp->next;
            }
        }
        delete[] visited;
        return false;
    }

    void FindShortestPath(int u, int v) const override
    {
        // TODO: Find the shortest path between the nodes u and v and print it.
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //std::cout << "Node not found\n";
            return;
        }
        bool *visited = new bool[size];
        int *prev = new int[size];
        for (int i = 0; i < size; ++i)
        {
            visited[i] = false;
            prev[i] = -1;
        }
        ListQueue queue;
        queue.enqueue(uIndex);
        visited[uIndex] = true;
        while (!queue.empty())
        {
            int current = queue.dequeue();
            if (current == vIndex)
            {
                break;
            }
            Node *temp = adjacencyList[current].getHead();
            while (temp != nullptr)
            {
                int neighborIndex = findNodeIndex(temp->element);
                if (neighborIndex != -1 && !visited[neighborIndex])
                {
                    visited[neighborIndex] = true;
                    prev[neighborIndex] = current;
                    queue.enqueue(neighborIndex);
                }
                temp = temp->next;
            }
        }
        int path[size];
        int pathLength = 0;
        int start = vIndex;
        while (start != -1)
        {
            path[pathLength++] = start;
            start = prev[start];
        }
        delete[] visited;
        delete[] prev;
        if (pathLength == 0 || (pathLength == 1 && path[0] != uIndex))
        {
            //std::cout << "No path found between " << u << " and " << v << "\n";
            return;
        }
        std::cout << "Shortest path from " << u << " to " << v << ": ";
        for (int i = pathLength - 1; i >= 0; --i)
        {
            std::cout << nodeID[path[i]] << " ";
        }
        std::cout << "\n";
    }

    int FindShortestPathLength(int u, int v) const override
    {
        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //std::cout << "Node not found\n";
            return -1;
        }
        bool *visited = new bool[size];
        int *prev = new int[size];
        for (int i = 0; i < size; ++i)
        {
            visited[i] = false;
            prev[i] = -1;
        }
        ListQueue queue;
        queue.enqueue(uIndex);
        visited[uIndex] = true;
        while (!queue.empty())
        {
            int current = queue.dequeue();
            if (current == vIndex)
            {
                break;
            }
            Node *temp = adjacencyList[current].getHead();
            while (temp != nullptr)
            {
                int neighborIndex = findNodeIndex(temp->element);
                if (neighborIndex != -1 && !visited[neighborIndex])
                {
                    visited[neighborIndex] = true;
                    prev[neighborIndex] = current;
                    queue.enqueue(neighborIndex);
                }
                temp = temp->next;
            }
        }
        int path[size];
        int pathLength = 0;
        int start = vIndex;
        while (start != -1)
        {
            path[pathLength++] = start;
            start = prev[start];
        }
        delete[] visited;
        delete[] prev;
        if (pathLength == 0 || (pathLength == 1 && path[0] != uIndex))
        {
            return -1;
        }
        return pathLength - 1;
    }

    linkedList GetNeighbors(int u) const override
    {
        // TODO: Return the list of neighbors.
        linkedList neighbors;
        int uIndex = findNodeIndex(u);
        if (uIndex == -1 || uIndex >= size)
        {
            //std::cout << "Node " << u << " not found\n";
            return neighbors;
        }
        Node *temp = adjacencyList[uIndex].getHead();
        while (temp != nullptr)
        {
            neighbors.append(temp->element);
            temp = temp->next;
        }
        return neighbors;
    }
    /*
    bool CheckPath(int u, int v) const override
    {
    int uIndex = findNodeIndex(u);
    int vIndex = findNodeIndex(v);
    if (uIndex == -1 || vIndex == -1)
    {
        std::cout << "Node not found\n";
        return false;
    }

    bool* visited = new bool[size];
    for (int i = 0; i < size; ++i)
        visited[i] = false;

    ListStack stack;
    stack.push(uIndex);

    while (!stack.empty())
    {
        int current = stack.pop();

        if (current == vIndex)
        {
            delete[] visited;
            return true;  // Path found
        }

        if (!visited[current])
        {
            visited[current] = true;

            Node* temp = adjacencyList[current].getHead();
            while (temp != nullptr)
            {
                int neighborIndex = findNodeIndex(temp->element);
                if (neighborIndex != -1 && !visited[neighborIndex])
                {
                    stack.push(neighborIndex);
                }
                temp = temp->next;
            }
        }
    }

    delete[] visited;
    return false;  // No path found
    }

    */
};

#endif // ADJACENCY_LIST_GRAPH_H
