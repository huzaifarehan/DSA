#include <iostream>
#include <queue>
#include <stack>
#include <climits>
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
    int weight;
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

void insertEdge(char fromData, char toData, int weight)
{
    struct Vertex *from = searchVertex(fromData);
    struct Vertex *to = searchVertex(toData);

    struct Edge *current = new Edge();
    current->toVertex = to;
    current->next = nullptr;
    current->weight = weight;

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


struct Edge *findMinWeightEdge(vector<bool> &inMST) {
    int minWeight = INT_MAX;
    struct Edge *minEdge = nullptr;

    for (struct Vertex *vertex = vStart; vertex != nullptr; vertex = vertex->next) {
        if (inMST[vertex->data - 'A'] == false) {
            struct Edge *edge = vertex->edgeList;
            while (edge != nullptr) {
                if (inMST[edge->toVertex->data - 'A'] == false && edge->weight < minWeight) {
                    minWeight = edge->weight;
                    minEdge = edge;
                }
                edge = edge->next;
            }
        }
    }
    return minEdge;
}

void primMST(char startNode) {
    vector<bool> inMST(100, false);
    vector<int> key(100, INT_MAX);

    struct Edge *parent[100];
    parent[startNode - 'A'] = nullptr;
    key[startNode - 'A'] = 0;

    for (int i = 0; i < 100; ++i) {
        struct Edge *minEdge = findMinWeightEdge(inMST);
        if (!minEdge) {
            break;
        }

        char u = minEdge->toVertex->data;
        inMST[u - 'A'] = true;

        struct Edge *edge = searchVertex(u)->edgeList;
        while (edge != nullptr) {
            char v = edge->toVertex->data;
            int weight = edge->weight;

            if (!inMST[v - 'A'] && weight < key[v - 'A']) {
                parent[v - 'A'] = edge;
                key[v - 'A'] = weight;
            }
            edge = edge->next;
        }
    }

    cout << "Minimum Spanning Tree (MST) starting from " << startNode << ":" << endl;
    for (int i = 0; i < 100; ++i) {
        if (parent[i]) {
            cout << char(i + 'A') << " - " << parent[i]->toVertex->data << " (Weight: " << parent[i]->weight << ")" << endl;
        }
    }
}


int main()
{
    insertVertex('A');
    insertVertex('B');
    insertVertex('C');
    insertVertex('D');
    insertVertex('E');
    insertVertex('F');
    insertEdge('A', 'C', 2);
    insertEdge('A', 'D', 3);
    insertEdge('A', 'B', 4);
    insertEdge('B', 'C', 5);
    insertEdge('B', 'E', 6);
    insertEdge('B', 'F', 7);
    // printVertex();
    // bfsTraversal('A');
    // dfsTraversal('A');
    primMST('A');
    printEdge('A');
    printEdge('A');
    cout << "Degree :" << degree('A') << endl;
    return 0;
}