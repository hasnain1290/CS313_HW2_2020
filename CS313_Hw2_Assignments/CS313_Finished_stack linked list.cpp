//Header File: linkedStack.h 

#ifndef H_StackType
#define H_StackType
//ifndef equivalent to pragma once
#include <iostream>
#include <cassert> 
#include "stackADT.h"

using namespace std;

//Definition of the node 
template <class Type>//using template class of Type
struct nodeType//creating a usable node
{
    Type info;//information of the node
    nodeType<Type> *link;//link to the node
};

template <class Type>//using same template class type
class linkedStackType: public stackADT<Type>//linkedStack type inherits from stackADT<type> 
{
public:
    const linkedStackType<Type>& operator=
                              (const linkedStackType<Type>&);
      //Overloaded the assignment operator

    bool isEmptyStack() const;
      //Function to determine whether the stack is empty.
      //Postcondition: Returns true if the stack is empty;
      //               otherwise returns false.

    bool isFullStack() const;
      //Function to determine whether the stack is full.
      //Postcondition: Returns false.

    void initializeStack();
      //Function to initialize the stack to an empty state. 
      //Postcondition: The stack elements are removed; 
      //               stackTop = nullptr;

    void push(const Type& newItem);
      //Function to add newItem to the stack.
      //Precondition: The stack exists and is not full.
      //Postcondition: The stack is changed and newItem 
      //               is added to the top of the stack.

    Type top() const;
      //Function to return the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: If the stack is empty, the program 
      //               terminates; otherwise, the top 
      //               element of the stack is returned.

    void pop();
      //Function to remove the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: The stack is changed and the top 
      //               element is removed from the stack.

    linkedStackType(); 
      //Default constructor
      //Postcondition: stackTop = nullptr;

    linkedStackType(const linkedStackType<Type>& otherStack); 
      //Copy constructor

    ~linkedStackType();
      //Destructor
      //Postcondition: All the elements of the stack are 
      //               removed from the stack.

private:
    nodeType<Type> *stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack); 
      //Function to make a copy of otherStack.
      //Postcondition: A copy of otherStack is created and
      //               assigned to this stack.
};


    //Default constructor
template <class Type> 
linkedStackType<Type>::linkedStackType()//default constructor that called inline from class LinkedStackType
{
    stackTop = nullptr;//have the stacktop pointed to a nullptr
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const//calling the isEmptyStack as inline from class LinkedStackType
{
    return(stackTop == nullptr);//if the stacktop is equal to nullptr return it
} //end isEmptyStack

template <class Type>
bool linkedStackType<Type>::isFullStack() const//calling the isFullStack() function inline from class LinkedStackType
{
    return false;//return false for the isFullStack function
} //end isFullStack

template <class Type>
void linkedStackType<Type>:: initializeStack()//inline prefix to use initializeStack inline from class LinkedStackType
{
    nodeType<Type> *temp; //pointer to delete the node

    while (stackTop != nullptr)  //while there are elements in 
                              //the stack
    {
        temp = stackTop;    //set temp to point to the 
                            //current node
        stackTop = stackTop->link;  //advance stackTop to the
                                    //next node
        delete temp;    //deallocate memory occupied by temp
    }
} //end initializeStack


template <class Type>
void linkedStackType<Type>::push(const Type& newElement)//push function inline prefix used from LinkedStackType
{
    nodeType<Type> *newNode;  //pointer to create the new node

    newNode = new nodeType<Type>; //create the node

    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode;       //set stackTop to point to the 
                              //top node
} //end push


template <class Type>
Type linkedStackType<Type>::top() const//top function inline prefix used from linkedstackType
{
    assert(stackTop != nullptr); //if stack is empty,
                              //terminate the program
    return stackTop->info;    //return the top element 
}//end top

template <class Type>
void linkedStackType<Type>::pop()//pop function to pop the stacktop off using inline prefix from linkedStackType
{
    nodeType<Type> *temp;   //pointer to deallocate memory

    if (stackTop != nullptr) //if the stacktop is not nullptr
    {
        temp = stackTop;  //set temp to point to the top node

        stackTop = stackTop->link;  //advance stackTop to the 
                                    //next node
        delete temp;    //delete the top node
    }
    else //if the top of the stack is a nullptr
        cout << "Cannot remove from an empty stack." << endl;//cout the following string
}//end pop

template <class Type> 
void linkedStackType<Type>::copyStack
                     (const linkedStackType<Type>& otherStack)//function used to copy the stack from the linkedlist passed in
{
    nodeType<Type> *newNode, *current, *last;

    if (stackTop != nullptr) //if stack is nonempty, make it empty
        initializeStack();//initialize the stack to empty

    if (otherStack.stackTop == nullptr)//if the second Stack is pointing to a nullptr
        stackTop = nullptr;//then put the stackTop to nullptr
    else
    {
        current = otherStack.stackTop;  //set current to point
                                   //to the stack to be copied

            //copy the stackTop element of the stack 
        stackTop = new nodeType<Type>;  //create the node

        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the link field of the
                                //node to nullptr
        last = stackTop;        //set last to point to the node
        current = current->link;    //set current to point to
                                    //the next node

            //copy the remaining stack
        while (current != nullptr)//while the current is not a nullptr
        {
            newNode = new nodeType<Type>;//create a new node

            newNode->info = current->info;//copy the info from newNode to current
            newNode->link = nullptr;//set the link of the newNode to nullptr
            last->link = newNode;//set the last link of node to new node
            last = newNode;//set last equal to new node
            current = current->link;//traverse the stack
        }//end while
    }//end else
} //end copyStack

    //copy constructor
template <class Type>   
linkedStackType<Type>::linkedStackType(
                      const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr; //set stacktopto nullptr
    copyStack(otherStack);//call copystack function on the otherStack
}//end copy constructor

    //destructor
template <class Type> 
linkedStackType<Type>::~linkedStackType()//~ means it is automatically a destructor
{
    initializeStack();//initialize the stack to empty
}//end destructor

    //overloading the assignment operator
template <class Type>   
const linkedStackType<Type>& linkedStackType<Type>::operator=
    			  (const linkedStackType<Type>& otherStack)
{ 
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);

    return *this; 
}//end operator=

#endif