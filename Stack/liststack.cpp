#include "stack.h"
#include <iostream>

// Constructor implementation
ListStack::ListStack() {
    // TODO: Initialize head to nullptr
    // TODO: Initialize current_size to 0
    current_size=0;
    head= nullptr;
}

// Destructor implementation
ListStack::~ListStack() {
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Push implementation
void ListStack::push(int item) {
    // TODO: Create a new node with the given item
    // TODO: Make the new node point to the current head
    // TODO: Update head to point to the new node
    // TODO: Increment current_size
    Node* new_node= new Node(item, head);
    head= new_node;    
    current_size++;
}

// Pop implementation
int ListStack::pop() {
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Store the data from the head node
    // TODO: Update head to point to the next node
    // TODO: Delete the old head node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    if(empty()){
        throw std:: runtime_error("Stack is empty!");
    }
    int element = head->data;
    Node *temp= head;
    head= temp->next;
    delete temp;
    current_size--;

    return element;
}

// Clear implementation
void ListStack::clear() {
    // TODO: Traverse the linked list, deleting each node
    // TODO: Reset head to nullptr
    // TODO: Reset current_size to 0
    while(head!=nullptr){
        Node *temp= head;
        head= temp->next;
        delete temp;
    }
    current_size=0;
}

// Size implementation
int ListStack::size() const {
    // TODO: Return the current size (current_size)
    return current_size;
}

// Top implementation
int ListStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the data from the head node without removing it
    if(empty()){
        throw std:: runtime_error("Stack is empty!");
    }
    int element = head->data;
    return element;
}

// Empty implementation
bool ListStack::empty() const {
    // TODO: Return whether head is nullptr
    if(head==nullptr) return true;
    else return false;
}

// Print implementation
void ListStack::print() const {
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    // TODO: Traverse the linked list from head, printing each node's data
    if (empty()) {
        std::cout << "Empty Stack" << std::endl;
        return;
    }
    std:: cout << "|";
    Node *temp=head;
    while(temp->next!=nullptr){
        std::cout <<  temp->data;
        std:: cout << ", ";
        temp= temp->next;
    }
    std::cout <<  temp->data;
    std:: cout << ">"<< std:: endl;
}