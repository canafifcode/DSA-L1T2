#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    front_node=nullptr;
    rear_node=nullptr;

    // TODO: Initialize current_size to 0
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    Node* new_node= new Node(item,nullptr);
    // TODO: Link the new node to the rear
    if(rear_node == nullptr){
        front_node= new_node;
    }
    else{
        rear_node->next = new_node;
    }
    // TODO: Update the rear_node
    rear_node = new_node;
    // TODO: Increment the current size
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if (front_node == nullptr) {
        cout << "Queue is empty, cannot dequeue." << endl;
        throw std::runtime_error("Queue is empty");
    }
    // TODO: Store the data from the front node
    int info= front_node->data;
    // TODO: Update the front pointer to the next node
    Node* old_front = front_node;
    front_node = front_node->next;
    // TODO: Update the rear pointer if the queue becomes empty
    if (front_node == nullptr) {
        rear_node = nullptr;
    }
    // TODO: Delete the old front node
    delete old_front;
    // TODO: Decrement current_size
    current_size--;
    // TODO: Return the stored data
    return info;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    Node* temp= front_node;
    while (temp != nullptr) {
        Node *nextnode=temp->next;
        delete temp;
        temp=nextnode;
    }
    front_node = nullptr;
    rear_node = nullptr;
    current_size = 0;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (front_node == nullptr) {
        cerr << "Queue is empty, cannot access front." << endl;
        throw std::runtime_error("Queue is empty");
    }
    // TODO: Return the data from the front node without removing it
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (rear_node == nullptr) {
        cerr << "Queue is empty, cannot access back." << endl;
        throw std::runtime_error("Queue is empty");
    }
    // TODO: Return the data from the back node without removing it
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return front_node == nullptr;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
    string result = "<";
    Node* current = front_node;
    while (current != nullptr) {
        result += std::to_string(current->data);
        current = current->next;
        if (current != nullptr) {
            result += ", ";
        }
    }
    result += "|";
    return result;
    
}
