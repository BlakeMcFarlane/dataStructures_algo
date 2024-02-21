// Deques method definitions

#include "deque.hpp"
#include <iostream>

using namespace std;

Deque::Deque() : front(nullptr), rear(nullptr), size(0) {}          // Constructor  

Deque::~Deque() {                                                   // Destructor
    while (front != nullptr) {                                      // Clearing queue
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    size = 0;
}

// Returns 1 if queue is empty else 0.
bool Deque::isEmpty () {                                         
    return size == 0;
}

// Return the number of items in the deque
int Deque::getSize() const{
    return size;
}

// Inserts a character at the end of the queue
void Deque::enqueueRear (int value) {
    Node* newNode = new Node(value);                        // Allocating memory for node
    if (isEmpty()) {                                        // Checking if the queue is empty
        front = rear = newNode;                             // - if empty: Point the front and rear to newNode
    }
    else {                                                  // - if NOT empty:
        rear->next = newNode;                               //   rear node points to the newNode
        newNode->prev = rear;                               //   newNodes previous points to the rear
        rear = newNode;                                     //   newNode is the new rear
    }
    size++;                                                 // Increment size of queue
}

// Inserts a character at the front of the queue
void Deque::enqueueFront (int value) {
    Node* newNode = new Node(value);                        // Allocating memory for node
    if (isEmpty()) {                                        // Checking if the queue is empty
        front = rear = newNode;                             // - if empty: Point the front and rear to newNode
    }   
    else {                                                  // - if NOT empty:
        newNode->next = front;                              //   newNode points to the front of the queue
        front->prev = newNode;                              //   fronts previous points from null to newNode
        front = newNode;                                    //   newNode is the new front
    }   
    size++;                                                 // Increment size of queue
}

// Removes a character from the front of the queue
void Deque::dequeueFront () {                               
    if (isEmpty()) {                                        // Checking if the queue is empty
        cout << "Queue is empty!" << endl;                  // - if empty: Print to the terminal
        return;                                             //   end run
    }
    Node* temp = front;                                     // Assign temp pointer node to the front
    if (front == rear) {                                    // - If the queue is only of size 1
        front = rear = nullptr;                             //   set front and rear pointers to null.
    }
    else {                                                  // - Else size > 1
        front = front->next;                                //   front is now the second node
        front->prev = nullptr;                              //   point the new fronts previous node to null
    }
    delete temp;                                            //   delete temporary pointer
    size--;                                                 // Decrement size of queue
}

// Removes a value from the back of the queue
void Deque::dequeueRear () {            
    if (isEmpty()) {                                        // Checking if the queue is empty
        cout << "Queue is empty!" << endl;                  // - if empty: Print to the terminal
        return;                                             //   end run
    }
    Node* temp = rear;                                      // Assign temp pointer node to the rear
    if (front == rear) {                                    // - If the queue is only of size 1
        front = rear = nullptr;                             //   set front and rear pointers to null.
    }
    else {                                                  // - Else size > 1
        rear = rear->prev;                                  //   rear is now the second from the last node
        rear->next = nullptr;                               //   set the new rears next pointer to null
    }
    delete temp;                                            //   delete temporary pointer
    size--;                                                 // Decrement size of queue

}

// Gets the front character
int Deque::getFront() {         
    if (isEmpty()) {                                        // if queue is empty
        cout << "Deque is empty" << endl;                   // - print to terminal
        return -1;                                          //   return -1
    }
    return front->data;                                     // else return the front nodes value
}

// Gets the rear character
int Deque::getRear() {  
    if (isEmpty()) {                                        // if queue is empty
        cout << "Deque is empty" << endl;                   // - print to terminal
        return -1;                                          //   return -1
    }
    return rear->data;                                      // else return the rear nodes value
}
