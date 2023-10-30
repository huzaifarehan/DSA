#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Vertex
{
    char data;
    Vertex *next;
    struct Edge *edgeList;
} *vStart = nullptr;

struct Edge
{
    Vertex *toVertex;
    Edge *next;
};

Vertex *newVertex(char c)
{
    struct Vertex *current = new Vertex();
    current->data = c;
    current->next = nullptr;
    current->edgeList = nullptr;
    return current;
}

void insertVertex(char c)
{
    struct Vertex *current = newVertex(c);
    if (vStart == nullptr)
    {
        vStart = current;
    }
    else
    {
        struct Vertex *temp = vStart;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = current;
    }
}

Vertex *searchVertex(char data)
{
    struct Vertex *temp = vStart;
    while (temp != nullptr && temp->data != data)
    {
        temp = temp->next;
    }
    return temp;
}

void insertEdge(char fromData, char toData)
{
    struct Vertex *from = searchVertex(fromData);
    struct Vertex *to = searchVertex(toData);

    struct Edge *current = new Edge();
    current->toVertex = to;
    current->next = nullptr;

    if (to != nullptr && from != nullptr)
    {
        if (from->edgeList == nullptr)
        {
            from->edgeList = current;
        }
        else
        {
            struct Edge *temp = from->edgeList;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = current;
        }
    }
}

void printVertex()
{
    struct Vertex *tempV1 = vStart;
    while (tempV1 != nullptr)
    {
        cout << tempV1->data << " ";
        tempV1 = tempV1->next;
    }
    cout << endl;
}

void printEdge(char c)
{
    struct Edge *tempE = new Edge();
    struct Vertex *tempV = searchVertex(c);
    tempE = tempV->edgeList;
    cout << tempV->data << " : ";
    while (tempE != nullptr)
    {
        cout << tempE->toVertex->data << ", ";
        tempE = tempE->next;
    }
    cout << endl;
}

int degree(char data)
{
    struct Vertex *currentV = searchVertex(data);
    struct Edge *currentE = currentV->edgeList;
    int degree = 0;
    while (currentE != nullptr)
    {
        degree++;
        currentE = currentE->next;
    }
    return degree;
}

void bfsTraversal(char startNode)
{
    struct Vertex *start = searchVertex(startNode);
    if (start == nullptr)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    queue<Vertex *> q;
    bool visited[100] = {false};

    cout << "BFS Traversal starting from " << startNode << ": ";

    q.push(start);
    visited[startNode - 'A'] = true;

    while (!q.empty())
    {
        Vertex *current = q.front();
        cout << current->data << " ";
        q.pop();

        struct Edge *edge = current->edgeList;
        while (edge != nullptr)
        {
            if (!visited[edge->toVertex->data - 'A'])
            {
                q.push(edge->toVertex);
                visited[edge->toVertex->data - 'A'] = true;
            }
            edge = edge->next;
        }
    }

    cout << endl;
}

void dfsTraversal(char startNode)
{
    struct Vertex *start = searchVertex(startNode);
    if (start == nullptr)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    stack<Vertex *> q;
    bool visited[100] = {false};

    cout << "DFS Traversal starting from " << startNode << ": ";

    q.push(start);
    visited[startNode - 'A'] = true;

    while (!q.empty())
    {
        Vertex *current = q.top();
        cout << current->data << " ";
        q.pop();

        struct Edge *edge = current->edgeList;
        while (edge != nullptr)
        {
            if (!visited[edge->toVertex->data - 'A'])
            {
                q.push(edge->toVertex);
                visited[edge->toVertex->data - 'A'] = true;
            }
            edge = edge->next;
        }
    }

    cout << endl;
}

int main()
{
    insertVertex('A');
    insertVertex('B');
    insertVertex('C');
    insertVertex('D');
    insertVertex('E');
    insertVertex('F');
    insertEdge('A', 'C');
    insertEdge('A', 'D');
    insertEdge('A', 'B');
    insertEdge('B', 'C');
    insertEdge('B', 'E');
    insertEdge('B', 'F');
    // printVertex();
    bfsTraversal('A');
    dfsTraversal('A');
    printEdge('A');
    printEdge('A');
    cout << "Degree :" << degree('A') << endl;
    return 0;
}