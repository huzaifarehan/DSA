#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *prev;
    Node(int val)
    {
        data = val;
        next = NULL;
        prev = NULL;
    }
};

void insertAtHead(Node *&head, int newData)
{
    Node *current = new Node(newData);
    head->prev = current;
    current->next = head;
    head = current;
}

void insert(Node *&head, int newData)
{
    Node *current = head;
    Node *newNode = new Node(newData);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
    newNode->prev = current;
}

void deleteHead(Node *&head)
{
    Node *current = head;
    head = current->next;
    head->prev = current->prev;
    delete current;
}
void deleteNodeByValue(Node *&head, int value)
{
    Node *current = head;
    if (current != NULL && current->data == value)
    {
        deleteHead(head);
        return;
    }
    while (current != NULL && current->data != value)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "NO Data Found";
        return;
    }
    Node *todelete = current;
    current->prev->next = current->next;
    if (current->next)
    {
        current->next->prev = current->prev;
    }
    delete todelete;
}

void deleteNodeByIndex(Node *&head, int position)
{
    Node *current = head;
    if (current != NULL && position == 0)
    {
        deleteHead(head);
        return;
    }
    for (int i = 0; current != NULL && i < position; i++)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "Position is Greater than the size of the Linked List" << endl;
        return;
    }
    Node *todelete = current;
    current->prev->next = current->next;
    if (current->next)
    {
        current->next->prev = current->prev;
    }
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
    while (current != NULL)
    {
        cout << "Data : " << current->data;
        if (current->next)
        {
            cout << " Next : " << current->next->data;
        }
        if (current->prev)
        {
            cout << " Prev : " << current->prev->data;
        }
        cout << endl;
        current = current->next;
    }
    cout << endl;
}
int length(Node *head)
{
    int count = 0;
    while (head != NULL)
    {
        head = head->next;
        count++;
    }
    return count;
}
Node *appendK(Node *&head, int k)
{
    Node *tail = head;
    Node *newHead;
    Node *newTail;
    int l = length(head);
    for (int i = 0; tail->next != NULL; i++)
    {
        if (i == l - k)
            newHead = tail;
        if (i == l - k - 1)
            newTail = tail;
        tail = tail->next;
    }
    newTail->next = NULL;
    tail->next = head;
    return newHead;
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
    insertAtHead(head, 7);
    deleteNodeByValue(head,1);
    deleteNodeByIndex(head, 0);
    traverse(head);
    Node *newHead = appendK(head, 3);
    traverse(newHead);
    return 0;
}
