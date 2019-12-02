//
//  Stack.cpp
//  Stack Project
//
//  Created by Mariia Romaniuk 
//


#include "Stack.hpp"
#include <iostream>
using namespace std;


// Stack implementation

// constructor
template <class T>
Stack<T>::Stack(int max){
    sizeStack = max;
    topStack = -1;
    stackArray = new T[max];
}


// destructor
template <class T>
Stack<T>::~Stack(){
    delete [] stackArray; // delete dynamic array
}


// copy constructor
template <class T>
Stack<T>::Stack(const Stack<T> &other){
    copy(other);
}


// copy stack
template <class T>
void Stack<T>::copy(const Stack<T> &other){
    if (!isEmpty())
        delete [] stackArray;
    
    sizeStack = other.sizeStack;
    topStack = other.topStack;
    stackArray = new T[sizeStack];
    
    //copy other stack into this stack
    for (int i = 0; i < sizeStack; i++)
        stackArray[i] = other.stackArray[i];
}


// overloading assignment operator
template <class T>
const Stack<T>& Stack<T>::operator=(const Stack<T> &other){
    if (this != &other)
        copy(other);
    return *this;
}


// add item in the stack
template <class T>
void Stack<T>::push(const T& item){
    // if stack is full print out a message
    // else increment topStack and store item in the stackArray
    if (isFull())
        cout << "Stack is full.\n" << endl;
    else
        stackArray[++topStack] = item;
}


// remove an item from the stack
template <class T>
void Stack<T>::pop(){
    // check if stack is not empty and remove top element
    if (isEmpty())
        cout << "Cannot remove from an empty stack.\n" << endl;
    else
        topStack--;
}


// return top element without removing
template <class T>
T& Stack<T>::top(){
    if (isEmpty()){
        cout << "Stack is empty.\n";
        exit(1);
    }
    else {
        T& x = stackArray[topStack];;
        return x;
    }
}


// return the size of the stack
template <class T>
int Stack<T>::size(){
    return sizeStack;
}


// check if stack is empty
template <class T>
bool Stack<T>::isEmpty(){
    // return true if topStack equal to -1, false otherwise
    if (topStack == -1)
        return true;
    else
        return false;
}


// check if stack is full
template <class T>
bool Stack<T>::isFull(){
    // return true if topStack+1 equal to full stack, false otherwise
    if (topStack+1 == sizeStack)
        return true;
    else
        return false;
}
