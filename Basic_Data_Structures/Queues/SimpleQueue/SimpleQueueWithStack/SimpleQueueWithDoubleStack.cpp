#include <iostream>
#include <stack>
using namespace std;

class QueueUsingStacks {
private:
    stack<int> inputStack; 
    stack<int> outputStack;

public:

    void enqueue(int item) {
        inputStack.push(item);
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }

        if (outputStack.empty()) {
            while (!inputStack.empty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }

        int frontItem = outputStack.top();
        outputStack.pop();
        return frontItem;
    }

    bool isEmpty() {
        return inputStack.empty() && outputStack.empty();
    }
};

int main() {
    QueueUsingStacks q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl; 

    return 0;
}
