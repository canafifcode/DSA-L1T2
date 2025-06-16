#pragma once

/**
 * Stack - Abstract Data Type (ADT) that follows the Last-In-First-Out (LIFO) principle
 * This interface defines the operations that any stack implementation must support
 */
class Stack {
public:
    /**
     * Pushes an element onto the top of the stack
     * @param value The element to push
     */
    virtual void push(int value) = 0;
    
    /**
     * Removes and returns the element at the top of the stack
     * @return The element at the top of the stack
     */
    virtual int pop() = 0;
    
    /**
     * Clears all elements from the stack
     */
    virtual void clear() = 0;
    
    /**
     * Returns the element at the top of the stack without removing it
     * @return The element at the top of the stack
     */
    virtual int top() const = 0;
    
    /**
     * Checks if the stack is empty
     * @return true if the stack is empty, false otherwise
     */
    virtual bool empty() const = 0;
    
    /**
     * Returns the current number of elements in the stack
     * @return The number of elements in the stack
     */
    virtual int size() const = 0;
    
    /**
     * Prints the elements in the stack from top to bottom
     */
    virtual void print() const = 0; 
    
    /**
     * Virtual destructor
     */
    virtual ~Stack() = default;
};


/**
 * ArrayStack - Implementation of Stack ADT using a dynamic array
 * Provides efficient stack operations with automatic resizing when needed
 */
class ArrayStack : public Stack {
private:
    int* data;     // Pointer to dynamically allocated array
    int capacity;  // Maximum number of elements the array can currently hold
    int current_size;  // Number of elements currently in the stack

public:
    /**
     * Constructor
     * @param capacity Initial capacity of the stack (default: 10)
     */
    ArrayStack(int capacity = 10);
    
    /**
     * Destructor - Cleans up any dynamically allocated memory
     */
    ~ArrayStack();

    // Stack interface implementation
    void push(int value) override;
    int pop() override;
    void clear() override;
    int top() const override;
    bool empty() const override;
    int size() const override;
    void print() const override; 
    
private:
    /**
     * Resizes the internal array when it becomes full or too empty
     * @param new_capacity The new capacity of the array
     */
    void resize(int new_capacity);
};


/**
 * ListStack - Implementation of Stack ADT using a singly linked list
 * Provides efficient stack operations with dynamic memory allocation per element
 */
class ListStack : public Stack {
private:
    /**
     * Node - Structure representing a single element in the linked list
     */
    struct Node {
        int data;    // Value stored in this node
        Node* next;  // Pointer to the next node in the list
        
        /**
         * Node constructor
         * @param value The value to store in this node
         * @param next_node Pointer to the next node (default: nullptr)
         */
        Node(int value, Node* next_node = nullptr) : data(value), next(next_node) {}
    };

    Node* head;     // Pointer to the top node of the stack
    int current_size;       // Number of elements currently in the stack
    
public:
    /**
     * Constructor - Creates an empty stack
     */
    ListStack();
    
    /**
     * Destructor - Cleans up any dynamically allocated memory
     */
    ~ListStack();

    // Stack interface implementation
    void push(int value) override;
    int pop() override;
    void clear() override;
    int top() const override;
    bool empty() const override;
    int size() const override;
    void print() const override;
};