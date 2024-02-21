#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

using namespace std;

// Defines a node for use in a doubly linked list.
class Node {
public:
    int data;                       // The data held by the Node.
    Node* next;                     // Pointer to the next Node in the list.
    Node* prev;                     // Pointer to the previous Node in the list.
    
    // Constructor initializes the Node with a value, and next/prev pointers as nullptr.
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Defines a Deque (double-ended queue) using a doubly linked list.
class Deque {
private:
    Node* front;                    // Pointer to the front (head) of the deque.
    Node* rear;                     // Pointer to the rear (tail) of the deque.
    int size;                       // Tracks the number of elements in the deque.
    
public:
    Deque();                        // Constructor initializes an empty deque.
    ~Deque();                       // Destructor cleans up all nodes to prevent memory leaks.
    
    bool isEmpty();                 // Returns true if the deque is empty, false otherwise.
    int getSize() const;            // Returns the number of elements in the deque.

    void enqueueRear(int value);    // Adds a new element at the rear of the deque.
    void enqueueFront(int value);   // Adds a new element at the front of the deque.

    void dequeueFront();            // Removes the element at the front of the deque.
    void dequeueRear();             // Removes the element at the rear of the deque.

    int getFront();                 // Returns the value of the front element.
    int getRear();                  // Returns the value of the rear element.
};

#endif // DEQUE_H
