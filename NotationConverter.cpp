// Blake McFarlane & Matthew Sharp
// Notation conversion using a deque

#include "NotationConverter.hpp"
#include "deque.hpp"
#include <iostream>

using namespace std;

// Sub class which inherits from NotationConverterInterface 'super' class
class NotationConverter : public NotationConverterInterface {
private:
    Deque primaryDeque;      // Primary queue for conversion
    Deque operandsDeque;     // Stores operands when converting between notations
    Deque operatorsDeque;    // Stores operators when converting between notations

public:

    // Postfix to Infix
    std::string postfixToInfix(std::string inStr){

        // Check if the input string is in postfix format
         if (!isalpha(inStr[0])) {
            // Return error
            return "Error: Input must start with an alphabetic character.";
        }

        // Iterate over the string to separate operators and operands
        for (char c : inStr) {
            if (c != ' ') { // Skip spaces
                if (c == '+' || c == '-' || c == '*' || c == '/') {
                    // Collect operators for processing
                    operatorsDeque.enqueueRear(c);
                } else {
                    // Queue up the operands for the infix format
                    operandsDeque.enqueueRear(c);
                }
            }
        }

        // Validate postfix is correct
        if(operatorsDeque.getSize() != operandsDeque.getSize() - 1) {
            return "Error: Invalid postfix notation.";
        }
        
        primaryDeque.enqueueRear('(');
        int operator_count = operatorsDeque.getSize();
        
        // Insert parenthesis depending on operator count
        for(int i = 1; i < operator_count-1; ++i) {
            primaryDeque.enqueueRear('(');
        };

        // Retrieve operands and operators from the temporary deques and insert them into the main deque
        while(!operandsDeque.isEmpty()){
            primaryDeque.enqueueRear(operandsDeque.getFront());
            operandsDeque.dequeueFront();

            // Remaining operators if any get put into the main deque
            if(!operatorsDeque.isEmpty()){
                
                // Insert from the back of the operators deque if there are 2 operators left
                if(operatorsDeque.getSize() == 2){
                    primaryDeque.enqueueRear(')');
                    primaryDeque.enqueueRear(operatorsDeque.getRear());
                    operatorsDeque.dequeueRear();
                    primaryDeque.enqueueRear('(');
                }
                else{
                    primaryDeque.enqueueRear(operatorsDeque.getFront());
                    operatorsDeque.dequeueFront();
                }
            }
        }

        primaryDeque.enqueueRear(')');

        // Insert remaining parenthesis needed to make the infix notation correct
        for(int i=1; i < operator_count-1; ++i) {
            primaryDeque.enqueueRear(')');
        };

        // Return elements in the main deque as a single string
        return toString();
    }

    // Takes a string of postfix notation and returns a string in prefix notation
    std::string postfixToPrefix(std::string inStr){
        return infixToPrefix(postfixToInfix(inStr));
    }

    // Takes a string of infix notation and returns a string in postfix notation
    std::string infixToPostfix(std::string inStr){

        // Validate input is infix
        if(inStr[0] != '(') {
            return "Error: Input must be in infix format.";
        }
        
        for(size_t i=0; i < inStr.length(); ++i){
            
            // Remove parenthesis from the infix notation
            while(inStr[i] != *inStr.end() && inStr[i] != ')'){
                if(inStr[i] != ' '){
                    // Store operators in the temporary deque
                    if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/'){
                        operatorsDeque.enqueueRear(inStr[i]);
                    }
                    // Store operands in the main deque
                    else if(inStr[i] != '(') {
                        primaryDeque.enqueueRear(inStr[i]);
                    }
                }
                i++;
            }

            int count = operatorsDeque.getSize();
            for(int i = 0; i < count; i++){
        
                // Insert from the back of the operators deque if there are 2 operators left
                if(operatorsDeque.getSize() == 2){
                    primaryDeque.enqueueRear(operatorsDeque.getRear());
                    operatorsDeque.dequeueRear();
                }
                else{
                    primaryDeque.enqueueRear(operatorsDeque.getFront());
                    operatorsDeque.dequeueFront();
                }
            }
        }

        // Return elements in the main deque as a single string
        return toString();
    }

    // Takes a string of infix notation and returns a std::string in prefix notation
    std::string infixToPrefix(std::string inStr){

        // Validate input is infix
        if(inStr[0] != '(') {
            return "Error: Input must be in infix format.";
        }

        for(size_t i=0; i < inStr.length(); ++i){

            // Remove parenthesis from the infix notation
            while(inStr[i] != ')' && inStr[i] != *inStr.end()){
                if(inStr[i] != ' '){
                    if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/'){

                        // Insert the operator to the front of the main deque if it is next to parenthesis
                        if(inStr[i-2] == ')'){
                            primaryDeque.enqueueFront(inStr[i]);
                        }

                        // Else insert to the back of the main deque
                        else primaryDeque.enqueueRear(inStr[i]);
                    }

                    // Insert the operands into the temporary operands deque
                    else if(inStr[i] != '(') operandsDeque.enqueueRear(inStr[i]);
                }
                i++;
            }

            // Insert operands from the operands deque into the main deque
            int count = operandsDeque.getSize();
            for(int i=0; i < count; ++i){
                primaryDeque.enqueueRear(operandsDeque.getFront());
                operandsDeque.dequeueFront();
            }
        }

        // Return elements in the main deque as a single string
        return toString();
    }

    // Takes a string of prefix notation and returns a string in infix notation
    std::string prefixToInfix(std::string inStr){

        // Vaidate input is prefix
        if(inStr[0] != '+' && inStr[0] != '-' && inStr[0] != '*' && inStr[0] != '/') {
            return "Error: Input must be in prefix format.";
        }

        // Determine if parenthesis are needed and store count to make sure there is an even amount
        bool parenthesis = false;
        int par_count= 0;

        for(size_t i=0; i < inStr.size(); ++i){
            if(inStr[i] != ' '){

                // Insert operators into operators deque
                if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/'){
                    operatorsDeque.enqueueRear(inStr[i]);
                    primaryDeque.enqueueRear('(');
                    par_count++;
                    parenthesis = false; // No operand found yet
                }
                else{
                    // Insert operands into main deque
                    primaryDeque.enqueueRear(inStr[i]);

                    // Insert a parenthesis after an operator in between two operands is inserted
                    if(parenthesis == true){
                        primaryDeque.enqueueRear(')');
                        par_count--; // Decrement count each time a closing parenthesis is inserted to keep at 0
                    }

                    // Insert the operator from the operands deque into the main deque
                    if(operatorsDeque.isEmpty() == false){
                        primaryDeque.enqueueRear(operatorsDeque.getRear());
                        operatorsDeque.dequeueRear();
                        parenthesis = true; // Parenthesis is now needed in the next iteration of the loop
                    }
                }
            }
        }

        // Check if there are a correct amount of opening and closing parenthesis and fix as needed
        if(par_count != 0){
            while(par_count != 0){
                primaryDeque.enqueueRear(')');
                par_count--;
            }
        }

        // Return elements in the main deque as a single string
        return toString();
    }

    // Takes a string of prefix notation and returns a string in postfix notation
    std::string prefixToPostfix(std::string inStr){
        return infixToPostfix(prefixToInfix(inStr));
    }

    // Converts elements in the deque into a single string to be returned
    std::string toString(){
        std::string output;

        // Checks if the deque is empty
        if(primaryDeque.isEmpty()) {
            return output;
        }

        int dequeLength = primaryDeque.getSize();

        // Fix formatting as instructed
        for(int i=0; i < dequeLength; ++i){
            if(primaryDeque.getFront() == ')') output.pop_back();
                output += primaryDeque.getFront();
            if(primaryDeque.getFront() != '(') output += ' ';
                primaryDeque.dequeueFront();
        }

        // Remove extra space
        output.pop_back();

        // Return the string
        return output;
    }
};