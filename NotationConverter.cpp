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

    // Converts an infix expression to postfix notation
    std::string infixToPostfix(std::string inStr) {

        // Ensure the expression starts with an opening parenthesis to confirm infix format
        if (inStr[0] != '(') {
            return "Error: Expected infix expression to start with '('.";
        }
        
        // Iterate through each character in the expression
        for (size_t i = 0; i < inStr.length(); ++i) {
            
            // Skip closing parenthesis and continue processing
            while (inStr[i] != *inStr.end() && inStr[i] != ')') {
                // Ignore spaces to focus on operators and operands
                if (inStr[i] != ' ') {
                    // Queue operators for later addition to the postfix expression
                    if (inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') {
                        operatorsDeque.enqueueRear(inStr[i]);
                    }
                    // Directly add operands to the postfix expression queue
                    else if (inStr[i] != '(') {
                        primaryDeque.enqueueRear(inStr[i]);
                    }
                }
                i++;
            }

            // Manage the operators' integration into the postfix expression
            int operatorCount = operatorsDeque.getSize();
            for (int j = 0; j < operatorCount; j++) {
                // Special handling for when exactly two operators remain
                if (operatorsDeque.getSize() == 2) {
                    primaryDeque.enqueueRear(operatorsDeque.getRear());
                    operatorsDeque.dequeueRear();
                } else {
                    // Sequentially add operators from the deque to the postfix expression
                    primaryDeque.enqueueRear(operatorsDeque.getFront());
                    operatorsDeque.dequeueFront();
                }
            }
        }

        // Compile and return the postfix expression as a single string
        return toString();
    }


    // This method transforms an infix expression into its prefix form.
    std::string infixToPrefix(std::string inStr) {

        // Check the first character to ensure the format is indeed infix.
        if (inStr[0] != '(') {
            return "Error: Expected expression to follow infix conventions.";
        }

        // Iterate over the input string to process each character.
        for (size_t i = 0; i < inStr.length(); ++i) {

            // Skip past closing parentheses and process till the end of the string.
            while (inStr[i] != ')' && inStr[i] != *inStr.end()) {
                // Ignore whitespace characters.
                if (inStr[i] != ' ') {
                    // For operators, decide their placement in the prefix expression.
                    if (inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') {

                        // Prioritize operators close to parentheses by placing them at the start.
                        if (inStr[i - 2] == ')') {
                            primaryDeque.enqueueFront(inStr[i]);
                        } else {
                            // Otherwise, operators are appended to the end.
                            primaryDeque.enqueueRear(inStr[i]);
                        }
                    } else if (inStr[i] != '(') { // Queue operands for later addition to the expression.
                        operandsDeque.enqueueRear(inStr[i]);
                    }
                }
                i++;
            }

            // Transfer operands from their queue to the primary deque for final assembly.
            int operandCount = operandsDeque.getSize();
            for (int j = 0; j < operandCount; ++j) {
                primaryDeque.enqueueRear(operandsDeque.getFront());
                operandsDeque.dequeueFront();
            }
        }

        // Compile and return the prefix notation as a consolidated string.
        return toString();
    }


    // Converts a prefix expression into its infix equivalent.
    std::string prefixToInfix(std::string inStr) {

        // Ensure the expression starts with a valid operator to confirm prefix format.
        if (inStr[0] != '+' && inStr[0] != '-' && inStr[0] != '*' && inStr[0] != '/') {
            return "Error: Expected prefix expression to start with an operator.";
        }

        // Track the need for parentheses and their balance within the expression.
        bool needParenthesis = false;
        int parenthesisCount = 0;

        // Process each character in the prefix expression.
        for (size_t i = 0; i < inStr.length(); ++i) {
            if (inStr[i] != ' ') { // Ignore spaces.

                // Queue operators for later processing and mark the need for opening parenthesis.
                if (inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') {
                    operatorsDeque.enqueueRear(inStr[i]);
                    primaryDeque.enqueueRear('('); // Prepare to wrap the upcoming operands.
                    parenthesisCount++;
                    needParenthesis = false; // Reset flag until next operand is encountered.
                } else { // For operands, directly add them to the primary queue.
                    primaryDeque.enqueueRear(inStr[i]);

                    // Close the parenthesis if the previous element was an operand, ensuring proper grouping.
                    if (needParenthesis) {
                        primaryDeque.enqueueRear(')'); // Close the current group.
                        parenthesisCount--; // Balance the count of open and close parentheses.
                    }

                    // Add the next operator from the queue to maintain prefix order.
                    if (!operatorsDeque.isEmpty()) {
                        primaryDeque.enqueueRear(operatorsDeque.getRear());
                        operatorsDeque.dequeueRear();
                        needParenthesis = true; // Indicate that another parenthesis may be needed.
                    }
                }
            }
        }

        // Ensure all opened parentheses are properly closed.
        while (parenthesisCount > 0) {
            primaryDeque.enqueueRear(')');
            parenthesisCount--;
        }

        // Compile and return the infix notation as a single string from the deque.
        return toString();
    }


    // Converts a prefix expression directly into postfix notation.
    std::string prefixToPostfix(std::string inStr) {
        // This leverages the conversion from prefix to infix and then from infix to postfix
        // to accomplish the transformation in a two-step process.
        return infixToPostfix(prefixToInfix(inStr));
    }

    // Assembles and returns the content of the primaryDeque as a formatted string.
    std::string toString() {
        std::string output; // Initialize an empty string to build the output.

        // Return immediately if there's nothing to process.
        if (primaryDeque.isEmpty()) {
            return output; // Return an empty string if the deque has no elements.
        }

        int dequeLength = primaryDeque.getSize(); // Get the total number of elements in the deque.

        // Sequentially process each element in the deque to format the output string.
        for (int i = 0; i < dequeLength; ++i) {
            // Skip adding a space before a closing parenthesis for proper formatting.
            if (primaryDeque.getFront() == ')') output.pop_back();
            
            // Append the current element to the output string.
            output += primaryDeque.getFront();
            
            // Add a trailing space for separation, except before a '(' to maintain formatting.
            if (primaryDeque.getFront() != '(') output += ' ';
            
            // Move to the next element in the deque.
            primaryDeque.dequeueFront();
        }

        // Eliminate the trailing space added after the last element for correct formatting.
        output.pop_back();

        // Deliver the assembled string, now representing the deque's content.
        return output;
    }

};