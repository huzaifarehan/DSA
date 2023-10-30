#include <iostream>
#include <stack>
#include <algorithm>
#include <cctype>
using namespace std;

int getPrecedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

string infixToPrefix(string expr) {
    stack<char> operators;
    stack<string> operands;
    
    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];
        
        if (isalpha(c)) {
            operands.push(string(1, c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                string operand2 = operands.top(); operands.pop();
                string operand1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                operands.push(op + operand1 + operand2);
            }
            operators.pop(); // remove '('
        } else {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(c)) {
                string operand2 = operands.top(); operands.pop();
                string operand1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                operands.push(op + operand1 + operand2);
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        string operand2 = operands.top(); operands.pop();
        string operand1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        operands.push(op + operand1 + operand2);
    }

    return operands.top();
}

int main() {
    string infix = "a+b*(c^d-e)^(f+g*h)-i";
    string prefix = infixToPrefix(infix);
    cout << "Infix: " << infix << endl;
    cout << "Prefix: " << prefix << endl; 

    return 0;
}
