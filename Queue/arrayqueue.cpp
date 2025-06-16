#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    if (initial_capacity <= 0) {
        initial_capacity = 2;
    }

    capacity = initial_capacity;
    front_idx = 0;
    rear_idx = 0;
    // TODO: Allocate memory for the array with the specified initial capacity
    data = new int[capacity];
}


// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
    data= nullptr;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    bool flag = false;
    if((rear_idx+1) % capacity == front_idx) {
        flag = true;
    }
    // TODO: If full, resize the array to double its current capacity
    if(flag==true){
        int new_capacity = capacity * 2;
        resize(new_capacity);
    }
    // TODO: Add the new element to the rear of the queue
    data[rear_idx]= item;
    rear_idx= (rear_idx+1)%capacity;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if(rear_idx==front_idx){
        throw std::underflow_error("THE QUEUE IS EMPTY");
    }
    int current_size= size();
    if(current_size<= capacity/4 && capacity>2){
        int new_capacity = max(2,capacity / 2);
        resize(new_capacity);
    }
    // TODO: Decrement current_size and return the element at the front of the queue
    int returntitem= data[front_idx];
    data[front_idx]=0;
    // TODO: Update front index
    front_idx=(front_idx+1)%capacity;
    // TODO: Return the dequeued element
    return returntitem;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    delete[] data;
    capacity = 2;
    data = new int[capacity];
    front_idx = 0;
    rear_idx = 0;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    int current_size= (front_idx<=rear_idx)? (rear_idx-front_idx):  (capacity+rear_idx-front_idx) ;
    return current_size;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if(rear_idx==front_idx){
        throw std::underflow_error("THE QUEUE IS EMPTY");

    }
    // TODO: Return the element at the front of the queue without removing it
    int returntitem= data[front_idx];
    return returntitem;
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if(rear_idx==front_idx){
        throw std::underflow_error("THE QUEUE IS EMPTY");

    }
    // TODO: Return the element at the back of the queue without removing it
    int returntitem= data[(rear_idx-1+capacity)%capacity];

    return returntitem;
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    if(size()==0) return true;
    return false;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    string result = "<";
    int current_size = size();
    for (int i = 0; i < current_size; ++i){
        result += std::to_string(data[(front_idx + i) % capacity]);
        if (i < current_size - 1) {
            result += ", ";
        }
    }
    result += "|";
    return result;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    if (new_capacity < 2) return;
    // TODO: Create a new array with the new capacity
    int *new_arr= new int[new_capacity];
    int akar=size();
    // TODO: Copy elements from the old array to the new array
    for(int i=0; i< akar; i++){
        new_arr[i]= data[(front_idx+i)%capacity];
    }
    // TODO: Delete the old array
    delete[] data;
    // TODO: Update the data pointer and capacity
    data= new_arr;
    capacity = new_capacity;
    // TODO: Update front and rear indices
    front_idx =0;
    rear_idx= akar;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}