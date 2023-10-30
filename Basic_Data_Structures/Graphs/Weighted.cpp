#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Edge
{
    char toVertex;
    int weight;
    Edge(char to, int w) : toVertex(to), weight(w) {}
};

struct Vertex
{
    char data;
    vector<Edge> edgeList;
    Vertex(char d) : data(d) {}
};

class Graph
{
public:
    vector<Vertex> vertices;

    void addVertex(char data)
    {
        vertices.push_back(Vertex(data));
    }

    void addEdge(char fromData, char toData, int weight)
    {
        for (Vertex &vertex : vertices)
        {
            if (vertex.data == fromData)
            {
                vertex.edgeList.push_back(Edge(toData, weight));
            }
            if (vertex.data == toData)
            {
                vertex.edgeList.push_back(Edge(fromData, weight));
            }
        }
    }

    void primMST(char startNode)
    {
        vector<char> parent(vertices.size(), '\0');
        vector<int> key(vertices.size(), numeric_limits<int>::max());
        vector<bool> inMST(vertices.size(), false);

        int startIdx = startNode - 'A';
        key[startIdx] = 0;

        for (int count = 0; count < vertices.size() - 1; count++)
        {
            int u = minKey(key, inMST);
            inMST[u] = true;

            for (const Edge &edge : vertices[u].edgeList)
            {
                int v = edge.toVertex - 'A';

                if (!inMST[v] && edge.weight < key[v])
                {
                    parent[v] = vertices[u].data;
                    key[v] = edge.weight;
                }
            }
        }

        printMST(parent);
    }

private:
    int minKey(const vector<int> &key, const vector<bool> &inMST)
    {
        int min = numeric_limits<int>::max();
        int minIdx = -1;

        for (int i = 0; i < vertices.size(); i++)
        {
            if (!inMST[i] && key[i] < min)
            {
                min = key[i];
                minIdx = i;
            }
        }

        return minIdx;
    }

    void printMST(const vector<char> &parent)
    {
        cout << "Minimum Spanning Tree (MST):" << endl;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (parent[i] != '\0')
            {
                cout << parent[i] << " - " << vertices[i].data << endl;
            }
        }
    }
};

int main()
{
    Graph graph;

    // Add vertices
    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');
    graph.addVertex('D');
    graph.addVertex('E');

    // Add edges with weights
    graph.addEdge('A', 'B', 2);
    graph.addEdge('A', 'C', 3);
    graph.addEdge('B', 'C', 1);
    graph.addEdge('B', 'D', 1);
    graph.addEdge('C', 'D', 4);
    graph.addEdge('C', 'E', 5);
    graph.addEdge('D', 'E', 3);

    char startNode = 'A';
    cout << "Starting node for MST: " << startNode << endl;
    graph.primMST(startNode);

    return 0;
}
