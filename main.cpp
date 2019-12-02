/*
main.cpp
Stack Project

Created by Mariia Romaniuk

This program uses stacks to evaluate an arithmetic expression in infix notation without
converting it into postfix notation. The program takes as input a numeric expression in
infix notation, such as 3+4*2, and outputs the result.

Operators are +, -, *, /
Assume that the expression is formed correctly so that each operation has two arguments.
The expression can have parenthesis, for example: 3*(4-2)+6.
The expression can have negative numbers.
The expression can have spaces in it, for example: 3  *  (4-2)  +6 .
*/



#include "Stack.hpp"
#include "Stack.cpp"
#include <iostream>
using namespace std;



#define SIZE 100
// function to keep track order of operations
int order(char op);
// function to combine digits with operator and return the result
int operate(char ch, int x, int y);
// function to evaluate an arithmetic expression and print the result
int evaluate(char &input);



int main(){
    char input;
    
    cout << "Enter an arithmetic expression: " << endl;
    input = cin.peek();
    
        try {
            // evaluate an arithmetic expression and print the result
            cout << "Expression evaluates to: " << evaluate(input) << endl;
        }
        // catch if number is divided by zero
        catch (string exceptionString){
            cout << exceptionString << endl;
        }
    return 0;
}



// function to keep track order of operations
int order(char op){
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/')
        return 2;
    return 0;
}


// function to combine digits with operator and return the result
int operate(char ch, int x, int y){
    switch (ch){
        case '+': return x+y;
        case '-': return x-y;
        case '*': return x*y;
        case '/': if (y == 0)
            throw string("Cannot divide by zero.");
        else
            return x/y;
    }
    return 0;
}


// function to evaluate an arithmetic expression and print the result
int evaluate(char & ch){
    
    // create two stacks: one for operators, another for digits
    Stack<char> operators(SIZE);
    Stack<int> digits(SIZE);
    
    // flag to determine if negative digit is added to stack
    bool negFlag = true;
    int num = 0, result = 0, val1 = 0, val2 = 0;
    char oper;
    
    // evaluate the input and store it to the appropriate stack
    while (ch != '\n'){
        if (isspace(ch)){
            ch = cin.get();
            ch = cin.peek();
            continue;
        }
        
        if (ch == '('){
            negFlag = true;
            cin >> ch;
            operators.push(ch);
            ch = cin.peek();
            continue;
        }
        
        if (isdigit(ch)){
            negFlag = false;
            cin >> num;
            digits.push(num);
            ch = cin.peek();
            continue;
        }
        
        if (ch == '-'){
            ch = cin.get();
            ch = cin.peek();
            
            // if the first digit is negative
            if (isdigit(ch) && digits.isEmpty()){
                negFlag = false;
                cin >> num;
                digits.push(num *= -1);
                ch = cin.peek();
                continue;
            }
            
            // if there is an operator after negative and next character
            if (!isdigit(ch) && negFlag == false && !digits.isEmpty() && !operators.isEmpty() && ch != '(' && ch != '-'){
                cin >> num;
                digits.push(num *= -1);
                ch = cin.peek();
                continue;
            }
            
            // if negative is within the parentheses
            if (isdigit(ch) && negFlag == true && operators.top() == '(' ){
                cin >> num;
                digits.push(num *= -1);
                ch = cin.peek();
                continue;
            }
            
            // if negative is used after operator and spaces
            if (isdigit(ch) && negFlag == true && !operators.isEmpty() && operators.top() != '('){
                cin >> num;
                digits.push(num *= -1);
                ch = cin.peek();
                continue;
            }
            
            // all other cases where number must be negated
            else {
                negFlag = true;
                while (!operators.isEmpty() && order('-') <= order(operators.top())){
                    val2 = digits.top();
                    digits.pop();
                    val1 = digits.top();
                    digits.pop();
                    
                    digits.push(operate(operators.top(), val1, val2));
                    result = digits.top();
                    operators.pop();
                }
                operators.push('-');
                ch = cin.peek();
                continue;
            }
        }
        else if (ch == '+' || ch == '*' || ch == '/'){
            negFlag = true;
            cin >> ch;
            // compares operator order when two or more are entered
            while (!operators.isEmpty() && order(ch) <= order(operators.top())){
                val2 = digits.top();
                digits.pop();
                val1 = digits.top();
                digits.pop();
                
                digits.push(operate(operators.top(), val1, val2));
                result = digits.top();
                operators.pop();
            }
            operators.push(ch);
            ch = cin.peek();
            continue;
        }
        // closing parentheses, evaluate expression inside the parentheses
        else if (ch == ')'){
            cin >> ch;
            while (!operators.isEmpty() && operators.top() != '('){
                val2 = digits.top();
                digits.pop();
                val1 = digits.top();
                digits.pop();
                oper = operators.top();
                operators.pop();
                digits.push(operate(oper, val1, val2));
            }
            operators.pop();
            ch = cin.peek();
            continue;
        }
        // miscellaneous operators are entered
        else {
            break;
        }
    }
    
    // return single digit if input is only a single number
    if (operators.isEmpty() == 1){
        result = digits.top();
    }
    
    // evaluate remaining stack digits at end of the string
    while (!operators.isEmpty()){
        val2 = digits.top();
        digits.pop();
        val1 = digits.top();
        digits.pop();
        oper = operators.top();
        operators.pop();
        digits.push(operate(oper, val1, val2));
        result = digits.top();
    }
    return result;
}
