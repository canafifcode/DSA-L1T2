#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"
#include "linkedList.h"

class AdjacencyMatrixGraph : public GraphADT
{
private:
    // TODO: Consider necessary private members as per your discretion
    int **matrix;
    int size = 0;
    int capacity;
    int *nodeID;

    void resizeMatrix()
    {
        int newCapacity = capacity;
        if (size >= capacity)
        {
            newCapacity = capacity * 2;
        }
        else if (size < capacity / 2 && capacity > 2)
        {
            newCapacity = capacity / 2;
        }
        else
        {
            return;
        }

        int **newMatrix = new int *[newCapacity];
        for (int i = 0; i < newCapacity; ++i)
        {
            newMatrix[i] = new int[newCapacity]();
        }
        int *newNodeID = new int[newCapacity]();

        for (int i = 0; i < size; ++i)
        {
            newNodeID[i] = nodeID[i];
            for (int j = 0; j < size; ++j)
            {
                newMatrix[i][j] = matrix[i][j];
            }
        }

        for (int i = 0; i < capacity; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] nodeID;

        matrix = newMatrix;
        nodeID = newNodeID;
        capacity = newCapacity;
    }

    int findNodeIndex(int v) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (nodeID[i] == v)
            {
                return i;
            }
        }
        return -1; // Node not found
    }

public:
    AdjacencyMatrixGraph()
    {
        capacity = 2;
        size = 0;
        matrix = new int *[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            matrix[i] = new int[capacity];
            for (int j = 0; j < capacity; ++j)
            {
                matrix[i][j] = 0;
            }
        }
        nodeID = new int[capacity];
    }

    void AddNode(int v) override
    {
        if (findNodeIndex(v) != -1)
        {
            printf("Node %d already exists\n", v);
            return;
        }
        if (size >= capacity)
            resizeMatrix();
        nodeID[size] = v;
        for (int i = 0; i <= size; ++i)
        {
            matrix[i][size] = 0;
            matrix[size][i] = 0;
        }
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
        if (matrix[uIndex][vIndex] == 0)
        {
            matrix[uIndex][vIndex] = 1;
            matrix[vIndex][uIndex] = 1;
            //printf("Edge added between %d and %d\n", u, v);
        }
        else
        {
            //printf("Edge already exists between %d and %d\n", u, v);

        }
    }

    bool CheckEdge(int u, int v) const override
    {
        // TODO: Check whether there is an edge between two nodes u and v
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //printf("Node not found\n");
            return false;
        }
        return matrix[findNodeIndex(u)][findNodeIndex(v)] == 1;
    }

    void RemoveNode(int v) override
    {
        // TODO: Remove a node.
        int index = findNodeIndex(v);
        if (index == -1)
        {
            //printf("Node %d not found\n", v);
            return;
        }
        // upshift
        for (int i = index; i < size - 1; ++i)
        {
            for (int j = 0; j < size; ++j)
                matrix[i][j] = matrix[i + 1][j];
        }
        // leftshift
        for (int i = 0; i < size; ++i)
        {
            for (int j = index; j < size - 1; ++j)
                matrix[i][j] = matrix[i][j + 1];
        }
        // fixnodeID
        for (int i = index; i < size - 1; ++i)
        {
            nodeID[i] = nodeID[i + 1];
        }
        size--;
        resizeMatrix();
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
            //printf("Node not found\n");
            return;
        }
        if (matrix[uIndex][vIndex] == 1)
        {
            matrix[uIndex][vIndex] = 0;
            matrix[vIndex][uIndex] = 0;
            //printf("Edge removed between %d and %d\n", u, v);
        }
        else
        {
           // printf("No edge exists between %d and %d\n", u, v);
        }
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        // SEARCH in nodeid if u and v exist
        int uIndex = findNodeIndex(u);
        int vIndex = findNodeIndex(v);
        if (uIndex == -1 || vIndex == -1)
        {
           // std::cout << "Node not found\n";
            return false;
        }
        int *queue = new int[size];
        bool *visited = new bool[size];
        for (int i = 0; i < size; ++i)
        {
            visited[i] = false;
        }
        int front = 0, rear = 0;
        queue[rear++] = uIndex;
        visited[uIndex] = true;

        while (front < rear)
        {
            int current = queue[front++];

            if (current == vIndex)
            {
                delete[] queue;
                delete[] visited;
                return true;
            }

            for (int i = 0; i < size; ++i)
            {
                if (matrix[current][i] == 1 && !visited[i])
                {
                    visited[i] = true;
                    queue[rear++] = i;
                }
            }
        }
        delete[] queue;
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
           // printf("Node not found\n");
            return;
        }
        int *queue = new int[size];
        bool *visited = new bool[size];
        int *prev = new int[size];
        for (int i = 0; i < size; ++i)
        {
            visited[i] = false;
            prev[i] = -1;
        }
        int front = 0, rear = 0;
        queue[rear++] = uIndex;
        visited[uIndex] = true;
        while (front < rear)
        {
            int current = queue[front++];

            if (current == vIndex)
            {
                break;
            }

            for (int i = 0; i < size; ++i)
            {
                if (matrix[current][i] == 1 && !visited[i])
                {
                    visited[i] = true;
                    prev[i] = current;
                    queue[rear++] = i;
                }
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
        if (pathLength == 0 || (pathLength == 1 && path[0] != uIndex))
        {
            std::cout << "No path found between " << u << "and " << v << std::endl;
        }
        else
        {
            std::cout << "Shortest path: ";
            for (int i = pathLength - 1; i >= 0; --i)
            {
                std::cout << nodeID[path[i]] << " ";
            }
            std::cout << std:: endl;
        }
        delete[] queue;
        delete[] visited;
        delete[] prev;
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
        int *queue = new int[size];
        bool *visited = new bool[size];
        int *prev = new int[size];
        for (int i = 0; i < size; ++i)
        {
            visited[i] = false;
            prev[i] = -1;
        }
        int front = 0, rear = 0;
        queue[rear++] = uIndex;
        visited[uIndex] = true;
        while (front < rear)
        {
            int current = queue[front++];
            if (current == vIndex)
            {
                break;
            }
            for (int i = 0; i < size; ++i)
            {
                if (matrix[current][i] == 1 && !visited[i])
                {
                    visited[i] = true;
                    prev[i] = current;
                    queue[rear++] = i;
                }
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
        delete[] queue;
        delete[] visited;
        delete[] prev;
        if (pathLength == 0 || (pathLength == 1 && path[0] != uIndex))
        {
            std::cout << "No path found between " << u << " and " << v << "\n";
            return -1;
        }
        return pathLength - 1;
    }

    linkedList GetNeighbors(int u) const override
    {
        // TODO return a list of neighbors of node u
        linkedList neighbors;
        int uIndex = findNodeIndex(u);
        if (uIndex == -1 || uIndex >= size)
        {
            printf("Node %d not found\n", u);
            return neighbors;
        }
        for (int i = 0; i < size; ++i)
        {
            if (matrix && matrix[uIndex] && matrix[uIndex][i] == 1) // Check matrix validity
            {
                neighbors.append(nodeID[i]);
            }
        }
        return neighbors;
    }

    ~AdjacencyMatrixGraph()
    {
        for (int i = 0; i < capacity; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] nodeID;
    }
};

#endif // ADJACENCY_MATRIX_GRAPH_H
