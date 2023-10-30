#include <iostream>
using namespace std;

class QueueNode
{
public:
    int data;
    QueueNode *prev;
    QueueNode(int val) : data(val), prev(NULL) {}
};
class Queue
{
private:
    QueueNode *front;
    QueueNode *rear;
    int count = 0;

public:
    Queue() : front(NULL), rear(NULL){};
    void enqueue(int val)
    {
        QueueNode *current = new QueueNode(val);
        count++;
        if (rear == NULL)
        {
            rear = current;
            front = current;
            return;
        }
        rear->prev = current;
        rear = current;
    }
    int dequeue()
    {
        if (count <= 0)
        {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        count--;
        int current = front->data;
        QueueNode *todelete = front;
        front = front->prev;
        delete todelete;
        return current;
    }
    int frontElement()
    {
        if (count <= 0)
        {
            cout << "Queue is Empty No frontend Element" << endl;
            return -1;
        }
        return front->data;
    }
    void print()
    {
        while (front != NULL)
        {
            cout << front->data << endl;
            front = front->prev;
        }
    }
    int size()
    {
        return count;
    }
};

int main()
{
    Queue q;

    for (int i = 1; i <= 50; i++)
    {
        q.enqueue(i);
    }
    cout << "Queue size: " << q.size() << endl;

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();

    cout << "Front element: " << q.frontElement() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Front element after dequeue: " << q.frontElement() << endl;
    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);
    q.enqueue(104);

    cout << "Queue size: " << q.size() << endl;

    return 0;
}
