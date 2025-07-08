#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

/**
 * Queue - Abstract Data Type (ADT) that follows the First-In-First-Out (FIFO) principle
 * This interface defines the operations that any queue implementation must support
 */
class Queue
{
public:
    /**
     * Enqueues an element at the back of the queue
     * @param value The element to enqueue
     */
    virtual void enqueue(int value) = 0;

    /**
     * Removes and returns the element at the front of the queue
     * @return The element at the front of the queue
     */
    virtual int dequeue() = 0;

    /**
     * Clears all elements from the queue
     */
    virtual void clear() = 0;

    /**
     * Returns the element at the front of the queue without removing it
     * @return The element at the front of the queue
     */
    virtual int front() const = 0;

    /**
     * Returns the element at the back of the queue without removing it
     * @return The element at the back of the queue
     */
    virtual int back() const = 0;

    /**
     * Checks if the queue is empty
     * @return true if the queue is empty, false otherwise
     */
    virtual bool empty() const = 0;

    /**
     * Returns the current number of elements in the queue
     * @return The number of elements in the queue
     */
    virtual int size() const = 0;

    /**
     * Prints the elements in the queue from front to back
     */
    virtual string toString() const = 0;

    /**
     * Virtual destructor
     */
    virtual ~Queue() = default;
};

/**
 * ListQueue - Implementation of Queue ADT using a singly linked list
 * Provides efficient queue operations with dynamic memory allocation per element
 */
class ListQueue : public Queue
{
private:
    /**
     * Node - Structure representing a single element in the linked list
     */
    struct Node
    {
        int data;   // Value stored in this node
        Node *next; // Pointer to the next node in the list

        /**
         * Node constructor
         * @param value The value to store in this node
         * @param next_node Pointer to the next node (default: nullptr)
         */
        Node(int value, Node *next_node = nullptr) : data(value), next(next_node) {}
    };

    Node *front_node; // Pointer to the front node of the queue
    Node *rear_node;  // Pointer to the rear node of the queue
    int current_size; // Number of elements currently in the queue

public:
    /**
     * Constructor - Creates an empty queue
     */
    ListQueue()
    {
        // TODO: Initialize front_node and rear_node
        front_node = nullptr;
        rear_node = nullptr;

        // TODO: Initialize current_size to 0
        current_size = 0;
    }
    /**
     * Destructor - Cleans up any dynamically allocated memory
     */
    ~ListQueue()
    {
        // TODO: Deallocate all nodes in the linked list
        // TODO: Consider using the clear() method
        clear();
    }
    // Queue interface implementation
    void enqueue(int item) override
    {
        // TODO: Create a new node with the given item
        Node *new_node = new Node(item, nullptr);
        // TODO: Link the new node to the rear
        if (rear_node == nullptr)
        {
            front_node = new_node;
        }
        else
        {
            rear_node->next = new_node;
        }
        // TODO: Update the rear_node
        rear_node = new_node;
        // TODO: Increment the current size
        current_size++;
    }

    int dequeue() override
    {
        if (front_node == nullptr)
        {
            cout << "Queue is empty, cannot dequeue." << endl;
            throw std::runtime_error("Queue is empty");
        }
        int info = front_node->data;
        Node *old_front = front_node;
        front_node = front_node->next;
        if (front_node == nullptr)
        {
            rear_node = nullptr;
        }
        delete old_front;
        current_size--;
        return info;
    }

    void clear() override
    {
        Node *temp = front_node;
        while (temp != nullptr)
        {
            Node *nextnode = temp->next;
            delete temp;
            temp = nextnode;
        }
        front_node = nullptr;
        rear_node = nullptr;
        current_size = 0;
    }

    int front() const override
    {
        if (front_node == nullptr)
        {
            cerr << "Queue is empty, cannot access front." << endl;
            throw std::runtime_error("Queue is empty");
        }
        return front_node->data;
    }

    int back() const override
    {
        if (rear_node == nullptr)
        {
            cerr << "Queue is empty, cannot access back." << endl;
            throw std::runtime_error("Queue is empty");
        }
        return rear_node->data;
    }

    bool empty() const override
    {
        return front_node == nullptr;
    }

    int size() const override
    {
        return current_size;
    }

    string toString() const override
    {
        string result = "<";
        Node *current = front_node;
        while (current != nullptr)
        {
            result += std::to_string(current->data);
            current = current->next;
            if (current != nullptr)
            {
                result += ", ";
            }
        }
        result += "|";
        return result;
    }
};

#endif // QUEUE_H