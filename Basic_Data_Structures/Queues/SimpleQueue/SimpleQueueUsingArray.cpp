#include <iostream>
using namespace std;
class Queue
{
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE] = {0};
    int frontIdx;
    int rearIdx;
    int count;

public:
    Queue()
    {
        frontIdx = 0;
        rearIdx = -1;
        count = 0;
    }

    void enqueue(int item)
    {
        if (count >= MAX_SIZE)
        {
            cout << "Queue is full. Cannot enqueue." << endl;
            return;
        }
        rearIdx = (rearIdx + 1) % MAX_SIZE; // Circular queue
        cout << "rearIdx :" << rearIdx << endl;
        arr[rearIdx] = item;
        count++;
    }

    int dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. Cannot dequeue." << std::endl;
            return -1;
        }
        int frontItem = arr[frontIdx];
        arr[frontIdx] = 0;
        frontIdx = (frontIdx + 1) % MAX_SIZE; // Circular queue After full the array It fills the dequeued places
        count--;
        return frontItem;
    }
    void print()
    {
        while (frontIdx != rearIdx)
        {
            cout << frontIdx << " : frontIdx " << arr[frontIdx] << endl;
            frontIdx = (frontIdx + 1) % MAX_SIZE;
        }
        cout << frontIdx << " : frontIdx " << arr[frontIdx] << endl;
    }

    int frontElement()
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty." << std::endl;
            return -1;
        }
        return arr[frontIdx];
    }

    bool isEmpty()
    {
        return count == 0;
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

    q.dequeue();
    q.dequeue();
    q.dequeue();

    std::cout << "Front element: " << q.frontElement() << std::endl;
    std::cout << "Dequeued: " << q.dequeue() << std::endl;
    std::cout << "Front element after dequeue: " << q.frontElement() << std::endl;
    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);
    q.enqueue(104);
    q.print();

    std::cout << "Queue size: " << q.size() << std::endl;

    return 0;
}
