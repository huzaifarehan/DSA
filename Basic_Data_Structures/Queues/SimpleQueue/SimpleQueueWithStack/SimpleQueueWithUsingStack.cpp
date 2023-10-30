#include <iostream>
#include <stack>
using namespace std;

class QueueUsingStack
{
private:
    stack<int> s;

public:
    void enqueue(int item)
    {
        s.push(item);
    }

    int dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }

        int frontItem = s.top();
        s.pop();

        if (isEmpty())
        {
            return frontItem;
        }

        int dequeuedItem = dequeue();
        s.push(frontItem);

        return dequeuedItem;
    }

    bool isEmpty()
    {
        return s.empty();
    }
};

int main()
{
    QueueUsingStack q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;

    return 0;
}
