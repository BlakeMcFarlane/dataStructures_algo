// Blake McFarlane & Matthew Sharp
// Project 1

#include "IntDList.hpp"
#include "IntDList_node.hpp"

#include <sstream>

IntDLList::~IntDLList() {}


void IntDLList::addToHead(int val) {                        // Add to head method which adds a node to the front of the linked list
    IntDLLNode* newNode = new IntDLLNode(val);              // Allocate memory for new node

    if (ListHead == nullptr) {                              // If node is empty, set the head to the new node.
        ListHead = newNode;
    }
    else {
        newNode->next = ListHead;                           // NewNode->next is the new head.
        ListHead->prev = newNode;                           // ListHead previous pointer points to the new node
        ListHead = newNode;                                 // NewNode is the new ListHead
    }   
}


void IntDLList::insertInOrder(int val) {
    IntDLLNode* newNode = new IntDLLNode(val);              // 1. Allocate memory for new node

    if (ListHead == nullptr || val < ListHead->info) {      // 2. Checks to see if the list is empty or if newNode should be first node.
        newNode->next = ListHead;                           // 3. Puts newNode at the head of list.
        if (ListHead != nullptr) {                          // 4. If the head of list is not null but inserted value is less than head value
            ListHead->prev = newNode;                       //    - Point the head previous node to newNode
        }
        ListHead = newNode;                                 // 5. newNode becomes head of list.
    }
    else {                                                                  // ELSE
        IntDLLNode* current = ListHead;                                     // Initialize current variable to head of list
        while (current->next != nullptr && current->next->info < val) {     // While current doesn't point to null and currents next value is less than the value.    
            current = current->next;                                        // Traverse 
        }

        newNode->next = current->next;                                      // Inserting newNode
        if (current->next != nullptr) {                                     // If the node after current is not null
            current->next->prev = newNode;                                  // - Node after current previous pointer points to newNode
        }   
        newNode->prev = current;                                            // NewNode previous pointer points to current
        current->next = newNode;                                            // Current node points to the newNode
    }
}


void IntDLList::addToTail(int val) {
    IntDLLNode* newNode = new IntDLLNode(val);              // 1. Allocate memory for new node

    if (ListHead == nullptr) {                              // 2. If list is empty, set newNode as ListHead
        ListHead = newNode;
    }
    else {
        IntDLLNode* current = ListHead;                     // 3. Make current object to traverse
        while (current->next != nullptr) {
            current = current->next;                        // 4. Traverse
        }
        current->next = newNode;                            // 5. Point last node to the newNode
        newNode->prev = current;                            // 6. Point newNode previous pointer to the node before.
    }
}


int IntDLList::deleteFromHead() {
    if (ListHead == nullptr) {                              // 1. List is empty
        return 0;                       
    }
    else if (ListHead->next == nullptr) {                   // 2. If list only has one node
        int temp = ListHead->info;                          //    a. Temp value to store the first nodes value
        ListHead = nullptr;                                 //    b. Set first node to null
        return temp;                                        //    c. Return value 
    }
    else {                                                  // 3. List has multiple nodes
        IntDLLNode* temp = ListHead;                        //    a. Temp value to store first nodes value
        ListHead = ListHead->next;                          //    b. Set the first node to the second node
        ListHead->prev = nullptr;                           //    c. Set the new first nodes previous node to null
        int tempValue = temp->info;                         //    d. Temp int value to store the value to return
        delete temp;                                        //    d. Delete the first node
        return tempValue;                                   //    e. Return the value of the deleted node.
    }
} // delete the head and return its info;


int IntDLList::deleteFromTail() {
    if (ListHead == nullptr) {                              // 1. List is empty
        return 0;
    }
    else if(ListHead->next == nullptr) {                    // 2. If list only has one node
        int temp = ListHead->info;                          //    a. Temp value to store the first nodes value
        ListHead = nullptr;                                 //    b. Set first node to null
        return temp;                                        //    c. Return value 
    }
    else {                                                  // 3. List has multiple nodes
        IntDLLNode* current = ListHead;                     //    a. Temp value to store first nodes value
        while (current->next->next != nullptr) {            //    b. Set the first node to the second node
            current = current->next;                        //    c. Traverse
        }
        int tempValue = current->next->info;                //    d. Temp value to store the value in the tail node
        IntDLLNode* toBeDeleted = current->next;
        current->next = nullptr;                            //    e. Setting the new last nodes previous value to null
        delete toBeDeleted;                               //    f. Deteling the last node.
        return tempValue;                                   //    g. return
    }
} // delete the tail and return its info;


void IntDLList::deleteNode(int val) {
    if (ListHead == nullptr) {                              // 1. List is empty
        return;
    }

    IntDLLNode* current = ListHead;                         // 2. Current node made to traverse through list

    while (current != nullptr) {                            // WHILE
        if (current->info == val) {                         //  Current node has the value we want to delete.
            if (current->next == nullptr){                  //    Node to delete is at END of list
                deleteFromTail();
            }
            else if (current->prev == nullptr){             //    Node to delete is at the START of the list
                deleteFromHead();
            }
            else {                                          //    Node to delete is not at the edge
                current->prev->next = current->next;        //      Pointing the previous node to the node after the deleted node
                current->next->prev = current->prev;        //      Pointing the next node to the node before the deleted node.
                delete current;
            }
            return;
        }
        current = current->next;                            // Traverse
    }
}


bool IntDLList::isInList(int val) const {               // Method to see if a value is in the list
    if (ListHead == nullptr) {                          // List is empty, has no values
        return false;
    }

    IntDLLNode* current = ListHead;                     // Initialze current variable to traverse

    while (current != nullptr) {                
        if (current->info == val) {                     // Looping until a value matches a value in the list
            return true;
        }
        current = current->next;                        
    }
    return false;                                       // Value not found
}


string IntDLList::addToString() const {                 // Method to output linked list
    string output;                                      // Declaring output variable
    IntDLLNode* current = ListHead;                     // Initializing current variable to traverse linked list
    while (current != nullptr) {
        output += std::to_string(current->info);        // Convert current->info to string and append to output
        current = current->next;
    }
    return output;                                      // Return output
}