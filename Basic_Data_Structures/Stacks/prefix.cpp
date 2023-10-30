#include <iostream>
#include <stack>
#include <cmath>
#include <string>
#include <cctype>
#include <algorithm>
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
int evaluatePrefix(const string &expr)
{
    stack<int> s;

    for (int i = expr.length() - 1; i >= 0; i--)
    {
        char c = expr[i];
        if (isdigit(c))
        {
            s.push(c - '0'); // because we want data in intergers
        }
        else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
        {
            int operand1 = s.top();
            s.pop();
            int operand2 = s.top();
            s.pop();
            int result = performOperation(c, operand1, operand2);
            s.push(result);
        }
        else
        {
            cout << "Invalid Character" << endl;
        }
    }
    return s.top();
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

int getPrecedence(char c)
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

string infixToPrefix(const string &expr)
{
    stack<char> s;
    string prefixExpr;
    for (int i = expr.length() - 1; i >= 0; i--)
    {
        char c = expr[i];
        if (isalpha(c) || isdigit(c))
        {
            prefixExpr += c;
        }
        else if (c == ')')
            s.push(c);
        else if (c == '(')
        {
            while (!s.empty() && s.top() != ')')
            {
                prefixExpr += s.top();
                s.pop();
            }
            s.pop(); // to remove this ')'
        }
        else
        {
            while (!s.empty() && getPrecedence(c) <= getPrecedence(s.top()))
            {
                prefixExpr += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty())
    {
        prefixExpr += s.top();
        s.pop();
    }
    reverse(prefixExpr.begin(), prefixExpr.end());
    return prefixExpr;
}

string infixToPostfix(const string &expr)
{
    stack<char> s;
    string postfixExpr;

    for (char c : expr)
    {
        if (isdigit(c) || isalpha(c))
        {
            postfixExpr += c;
        }
        else if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfixExpr += s.top();
                s.pop();
            }
            s.pop(); // remove '('
        }
        else
        {
            while (!s.empty() && getPrecedence(c) <= getPrecedence(s.top()))
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

string infixToPrefixGPT(const string &expr)
{
    // Reverse the infix expression
    string reversedExpr = expr;
    reverse(reversedExpr.begin(), reversedExpr.end());

    // Replace opening brackets with closing and vice-versa
    for (int i = 0; i < reversedExpr.length(); i++)
    {
        if (reversedExpr[i] == '(')
        {
            reversedExpr[i] = ')';
        }
        else if (reversedExpr[i] == ')')
        {
            reversedExpr[i] = '(';
        }
    }

    // Convert to postfix
    string postfix = infixToPostfix(reversedExpr);

    // Reverse postfix to get prefix
    reverse(postfix.begin(), postfix.end());

    return postfix;
}

int main()
{
    string expression = "a+b*(c^d-e)^(f+g*h)-i";
    string newExpr = infixToPrefix(expression);
    cout << newExpr << endl;
    // cout << "Prefix Evaluation Result: " << evaluatePrefix(expression) << endl;
    return 0;
}