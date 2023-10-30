#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int val)
    {
        data = val;
        next = NULL;
    }
};


void insert(Node *&head, int newData)
{
    Node *newNode = new Node(newData);
    Node *current = head;

    if (head == NULL)
    {
        newNode->next = newNode;
        head = newNode;
        return;
    }

    while (current->next != head)
    {
        current = current->next;
    }

    newNode->next = head;
    current->next = newNode;
}

void deleteAtHead(Node *&head)
{
    Node *current = head;
    Node *tail = head;
    while (tail->next != head)
    {
        tail = tail->next;
    }
    head = head->next;
    tail->next = head;
    delete current;
    return;
}

void deleteNodeByValue(Node *&head, int value)
{
    Node *current = head;
    if (current != NULL && current->data == value)
    {
        deleteAtHead(head);
        return;
    }
    while (current != NULL && current->next->data != value)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "NO Data Found";
        return;
    }
    Node *todelete = current->next;
    current->next = current->next->next;
    delete todelete;
}

void deleteNodeByIndex(Node *&head, int position)
{
    Node *current = head;

    if (head == NULL)
    {
        cout << "The List Is Empty";
        return;
    }
    if (current != NULL && position == 0)
    {
        deleteAtHead(head);
        return;
    }
    for (int i = 0; i < position - 1; i++)
    {
        current = current->next;
    }

    if (current == head || current->next == head)
    {
        cout << "Position is Greater than the size of the Linked List" << endl;
        return;
    }

    Node *todelete = current->next;
    current->next = current->next->next;
    delete todelete;
}

void traverse(Node *head)
{
    Node *current = head;
    if (head == NULL)
    {
        cout << "The List Is Empty";
        return;
    }
    for (int i = 0; i < 20; i++)
    {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << endl;
}

int main()
{
    Node *head = NULL;
    insert(head, 1);
    insert(head, 2);
    insert(head, 3);
    insert(head, 4);
    insert(head, 5);
    insert(head, 6);
    deleteNodeByValue(head, 1);
    deleteNodeByIndex(head, 0);
    traverse(head);
    return 0;
}
