#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    
    Node (int value) : data(value), next(nullptr), prev(nullptr) {}
};

class Deque {
private:
    Node* front;
    Node* rear;
    int size;
    
public:
    Deque();

    ~Deque();
    
    bool isEmpty ();

    int getSize() const;

    void enqueueRear (int value);

    void enqueueFront (int value);

    void dequeueFront ();

    void dequeueRear ();

    int getFront();

    int getRear();
};

#endif
