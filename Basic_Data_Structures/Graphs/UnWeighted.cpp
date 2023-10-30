#include <iostream>
using namespace std;

class Edge; // Forward declaration

class Vertex {
public:
    char data;
    Vertex* next;
    Edge* edgeList;

    Vertex(char data) : data(data), next(nullptr), edgeList(nullptr) {}
};

class Edge {
public:
    Vertex* toVertex;
    Edge* next;

    Edge(Vertex* toVertex) : toVertex(toVertex), next(nullptr) {}
};

class Graph {
private:
    Vertex* vStart;

public:
    Graph() : vStart(nullptr) {}

    void insertVertex() {
        char inputData;
        cout << "Enter Node Data" << endl;
        cin >> inputData;
        Vertex* tempV = new Vertex(inputData);

        if (vStart == nullptr) {
            vStart = tempV;
        } else {
            Vertex* tempV1 = vStart;
            while (tempV1->next != nullptr) {
                tempV1 = tempV1->next;
            }
            tempV1->next = tempV;
        }
    }

    Vertex* searchVertex(char data) {
        Vertex* tempV = vStart;
        while (tempV != nullptr) {
            if (tempV->data == data) {
                return tempV;
            }
            tempV = tempV->next;
        }
        return nullptr;
    }

    void insertEdge() {
        char fromData;
        char toData;
        cout << "From Where" << endl;
        cin >> fromData;
        cout << "To Where" << endl;
        cin >> toData;

        Vertex* to = searchVertex(toData);
        Vertex* from = searchVertex(fromData);

        if (to != nullptr && from != nullptr) {
            Edge* tempE = new Edge(to);

            if (from->edgeList == nullptr) {
                from->edgeList = tempE;
            } else {
                Edge* tempE1 = from->edgeList;
                while (tempE1->next != nullptr) {
                    tempE1 = tempE1->next;
                }
                tempE1->next = tempE;
            }
        }
    }

    void printVertex() {
        Vertex* tempV1 = vStart;
        while (tempV1 != nullptr) {
            cout << tempV1->data;
            tempV1 = tempV1->next;
        }
        cout << endl;
    }

    void printEdge() {
        char inputData;
        cout << "Which node's edges to be printed: " << endl;
        cin >> inputData;

        Vertex* tempV1 = searchVertex(inputData);
        Edge* tempE = tempV1->edgeList;
        cout << tempV1->data << " : ";
        while (tempE != nullptr) {
            cout << tempE->toVertex->data << ",";
            tempE = tempE->next;
        }
        cout << "null" << endl;
    }

    int degree(char data) {
        Vertex* tempV1 = searchVertex(data);
        Edge* tempE = tempV1->edgeList;
        int degree = 0;
        while (tempE != nullptr) {
            degree++;
            tempE = tempE->next;
        }
        return degree;
    }

    ~Graph() {
        // Clean up dynamically allocated memory
        Vertex* current = vStart;
        while (current != nullptr) {
            Vertex* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    Graph graph;

    graph.insertVertex();
    graph.insertVertex();
    graph.insertVertex();
    graph.insertVertex();
    graph.insertEdge();
    graph.insertEdge();
    graph.printEdge();
    cout << "Degree: " << graph.degree('A') << endl;

    return 0;
}
