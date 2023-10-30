#include <iostream>
#include <stack>
#include <cmath>
#include <string>
#include <cctype>
using namespace std;

int performOperation(char operation, int operand1, int operand2)
{
    switch (operation)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '^':
        return pow(operand1, operand2);
    default:
        return 0;
    }
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

int evaluatePostfix(const string &expr)
{
    stack<int> s;

    for (int i = 0; i < expr.length(); i++)
    {
        char c = expr[i];
        if (isdigit(c))
        {
            int number = 0;
            while (isdigit(expr[i]))
            {
                number = number * 10 + (expr[i] - '0');
                i++;
            }
            s.push(number);
        }
        else if (isOperator(c))
        {
            int operand2 = s.top(); // In postfix we used second operand as first operand
            s.pop();
            int operand1 = s.top();
            s.pop();
            int result = performOperation(c, operand1, operand2);
            // cout << "result : " << result << endl;
            s.push(result);
        }
        else
        {
            cout << "Invalid Character" << endl;
        }
    }
    return s.top();
}

int getPrecendence(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

string infixToPostfix(const string &expr)
{
    stack<char> s;
    string postfixExpr;
    for (int i = 0; i < expr.length(); i++)
    {
        char c = expr[i];
        if (isdigit(c))
        {
            while (isdigit(expr[i]))
            {
                postfixExpr += expr[i++];
            }
            postfixExpr += ' '; // To differentiate between multi-digit numbers
            i--;
        }
        else if (c == '(')
            s.push(c);
        else if (c == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfixExpr += s.top();
                s.pop();
            }
            s.pop(); // to remove this '('
        }
        else
        {
            while (!s.empty() && getPrecendence(c) <= getPrecendence(s.top()))
            {
                postfixExpr += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty())
    {
        postfixExpr += s.top();
        s.pop();
    }
    return postfixExpr;
}

int main()
{
    string expression = "10+3*5/(16-4*2)";
    string newExpr = infixToPostfix(expression);
    cout << newExpr << endl;
    cout << "Postfix Evaluation Result: " << evaluatePostfix(newExpr) << endl;
    return 0;
}