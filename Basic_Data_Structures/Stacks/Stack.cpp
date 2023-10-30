#include <iostream>
using namespace std;

class StackNode
{
private:
    int data;
    StackNode *prev;

public:
    StackNode(int val) : data(val), prev(NULL) {}

    int getData() const
    {
        return data;
    }

    StackNode *getPrev() const
    {
        return prev;
    }

    friend class Stack;
};

class Stack
{
private:
    StackNode *top;

public:
    Stack() : top(NULL) {}

    bool isEmpty() const
    {
        return top == NULL;
    }

    void push(int value)
    {
        StackNode *newNode = new StackNode(value);
        newNode->prev = top;
        top = newNode;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }

        int poppedValue = top->data;
        StackNode *toDelete = top;
        top = top->prev;
        delete toDelete;
        return poppedValue;
    }

    int peek() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return top->data;
    }
};

int main()
{
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top of the stack: " << s.peek() << endl;

    cout << "Popped from stack: " << s.pop() << endl;

    cout << "Top of the stack: " << s.peek() << endl;

    return 0;
}
