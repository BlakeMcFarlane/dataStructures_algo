// Blake McFarlane and Matthew Sharp
// Project 1

/*Driver function to test your code. DO NOT MODIFY THIS FILE*/

#include "IntDList.hpp"
#include <iostream>
#include <string>

using namespace  std;
int main()
{


    IntDLList myList;
    myList.insertInOrder(1);
    myList.insertInOrder(2);
    myList.insertInOrder(9);
    myList.insertInOrder(4);
    myList.insertInOrder(6);

    myList.insertInOrder(3);

    cout<< myList.addToString()<<endl;//should print "123469"


    myList.deleteFromHead();

    cout<< myList.addToString()<<endl;//should print "23469"


    myList.deleteNode(4);

    cout<< myList.addToString()<<endl;//should print "2369"


    myList.deleteFromTail();

    cout<< myList.addToString()<<endl;//should print "236"



}
