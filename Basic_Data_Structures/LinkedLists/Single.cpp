
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
        head = newNode;
        return;
    }

    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
}

void deleteNodeByValue(Node *&head, int value)
{
    Node *current = head;
    if (current != NULL && current->data == value)
    {
        head = current->next;
        delete current;
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
    if (current != NULL && position == 0)
    {
        head = current->next;
        delete current;
        return;
    }
    for (int i = 0; current != NULL && i < position - 1; i++)
    {
        current = current->next;
    }
    if (current == NULL || current->next == NULL)
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
    while (current != NULL)
    {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << endl;
}

Node *iterativeReverse(Node *&head)
{
    if (head == NULL)
    {
        cout << "The List Is Empty";
        return NULL;
    }
    Node *current = head;
    Node *prevPtr = NULL;
    Node *nextPtr;
    while (current != NULL)
    {
        nextPtr = current->next;
        current->next = prevPtr;

        prevPtr = current;
        current = nextPtr;
    }
    return prevPtr;
}
Node *recursiveReverse(Node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *newHead = recursiveReverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

Node *reverseK(Node *head, int k)
{
    Node *current = head;
    Node *prevPtr = NULL;
    Node *nextPtr;
    for (int i = 0; current != NULL && i < k; i++)
    {
        nextPtr = current->next;
        current->next = prevPtr;

        prevPtr = current;
        current = nextPtr;
    }
    if (nextPtr != NULL)
    {
        head->next = reverseK(nextPtr, k);
    }
    return prevPtr;
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
    deleteNodeByValue(head,4);
    deleteNodeByIndex(head, 7);
    traverse(head);
    Node *reverseHead = recursiveReverse(head);
    Node *reverseHead = iterativeReverse(head);
    traverse(reverseHead);
    Node *reverseHead = reverseK(head, 2);
    traverse(reverseHead);
    return 0;
}
