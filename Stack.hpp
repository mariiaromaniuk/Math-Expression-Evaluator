//
//  Stack.hpp
//  Stack Project
//
//  Created by Mariia Romaniuk
//

#ifndef Stack_hpp
#define Stack_hpp
#include <stdio.h>
using namespace std;


// Stack declaration

template <class T>
class Stack {
    
private:
    
    int sizeStack; //size of the stack
    int topStack; //top of the stack
    T* stackArray; //stack array
    
public:
    
    Stack(int max); //constructor
    
    ~Stack(); //destructor

    Stack(const Stack<T>& other); //copy constructor
    
    void copy(const Stack<T>& other); //copy stack
    
    const Stack<T>& operator=(const Stack<T>& other); //overloading = operator
    
    void push(const T& item); //add item in the stack
    
    void pop(); //remove an item from the stack
    
    T& top(); //return top element without removing
    
    int size(); //return the size of the stack
    
    bool isEmpty(); //check if stack is empty
    
    bool isFull(); //check if stack is full
};

#endif /* Stack_hpp */
