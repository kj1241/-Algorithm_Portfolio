#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring>
#include <memory>

using namespace std;

constexpr int MAX_WEIGHT = numeric_limits<int>::max();
using ElementType = char;
struct Edge;

struct Vertex {
    ElementType Data;
    Vertex* Next;
    Edge* AdjacencyList;
    bool Visited;
    int Index;
    Vertex(ElementType data) : Data(data), Next(nullptr), AdjacencyList(nullptr), Visited(false), Index(-1) {}
};


struct Edge {
    Vertex* From;
    Vertex* Target;
    Edge* Next;
    int Weight;
    Edge(Vertex* from, Vertex* target, int weight) : From(from), Target(target), Next(nullptr), Weight(weight) {}
};


struct Graph {
    Vertex* Vertices;
    int VertexCount;
    Graph() : Vertices(nullptr), VertexCount(0) {}
    ~Graph();
};

Graph::~Graph() {
    while (Vertices != nullptr) {
        Vertex* nextVertex = Vertices->Next;
        delete Vertices;
        Vertices = nextVertex;
    }
}

struct PQNode {
    int Priority;
    Vertex* Data;
    bool operator<(const PQNode& other) const {
        return Priority > other.Priority;
    }
};

class PriorityQueue {
public:
    PriorityQueue(int initialSize) : capacity(initialSize), usedSize(0) {
        nodes.resize(capacity);
    }

    void Enqueue(PQNode newNode) {
        if (usedSize == capacity) {
            capacity *= 2;
            nodes.resize(capacity);
        }
        nodes[usedSize++] = newNode;
        int currentPosition = usedSize - 1;
        int parentPosition = GetParent(currentPosition);
        while (currentPosition > 0 && nodes[currentPosition].Priority < nodes[parentPosition].Priority) {
            SwapNodes(currentPosition, parentPosition);
            currentPosition = parentPosition;
            parentPosition = GetParent(currentPosition);
        }
    }

    void Dequeue(PQNode& root) {
        root = nodes[0];
        nodes[0] = nodes[--usedSize];
        int parentPosition = 0;
        while (true) {
            int leftPosition = GetLeftChild(parentPosition);
            int rightPosition = leftPosition + 1;
            if (leftPosition >= usedSize) break;
            int selectedChild = (rightPosition >= usedSize || nodes[leftPosition].Priority < nodes[rightPosition].Priority) ? leftPosition : rightPosition;
            if (nodes[selectedChild].Priority < nodes[parentPosition].Priority) {
                SwapNodes(parentPosition, selectedChild);
                parentPosition = selectedChild;
            }
            else {
                break;
            }
        }
    }

    bool IsEmpty() const {
        return usedSize == 0;
    }

private:
    int GetParent(int index) const {
        return (index - 1) / 2;
    }

    int GetLeftChild(int index) const {
        return 2 * index + 1;
    }

    void SwapNodes(int index1, int index2) {
        swap(nodes[index1], nodes[index2]);
    }

    vector<PQNode> nodes;
    int capacity;
    int usedSize;
};

Graph* CreateGraph() {
    return new Graph();
}

void DestroyGraph(Graph* G) {
    delete G;
}

Vertex* CreateVertex(ElementType Data) {
    return new Vertex(Data);
}

void DestroyVertex(Vertex* V) {
    while (V->AdjacencyList != nullptr) {
        Edge* edge = V->AdjacencyList->Next;
        delete V->AdjacencyList;
        V->AdjacencyList = edge;
    }
    delete V;
}

Edge* CreateEdge(Vertex* From, Vertex* Target, int Weight) {
    return new Edge(From, Target, Weight);
}

void DestroyEdge(Edge* E) {
    delete E;
}

void AddVertex(Graph* G, Vertex* V) {
    Vertex* vertexList = G->Vertices;
    if (vertexList == nullptr) {
        G->Vertices = V;
    }
    else {
        while (vertexList->Next != nullptr)
            vertexList = vertexList->Next;
        vertexList->Next = V;
    }
    V->Index = G->VertexCount++;
}

void AddEdge(Vertex* V, Edge* E) {
    if (V->AdjacencyList == nullptr) {
        V->AdjacencyList = E;
    }
    else {
        Edge* adjacencyList = V->AdjacencyList;
        while (adjacencyList->Next != nullptr)
            adjacencyList = adjacencyList->Next;
        adjacencyList->Next = E;
    }
}

void PrintGraph(const Graph* G) {
    Vertex* V = G->Vertices;
    while (V != nullptr) {
        cout << V->Data << " : ";
        Edge* E = V->AdjacencyList;
        while (E != nullptr) {
            cout << E->Target->Data << "[" << E->Weight << "] ";
            E = E->Next;
        }
        cout << endl;
        V = V->Next;
    }
    cout << endl;
}

void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath) {
    int i = 0;
    PQNode startNode = { 0, StartVertex };
    PriorityQueue pq(10);
    pq.Enqueue(startNode);

    vector<int> weights(G->VertexCount, MAX_WEIGHT);
    vector<Vertex*> shortestPathVertices(G->VertexCount);
    vector<Vertex*> fringes(G->VertexCount, nullptr);
    vector<Vertex*> precedences(G->VertexCount, nullptr);

    Vertex* currentVertex = G->Vertices;
    while (currentVertex != nullptr) {
        Vertex* newVertex = CreateVertex(currentVertex->Data);
        AddVertex(ShortestPath, newVertex);
        shortestPathVertices[i++] = newVertex;
        currentVertex = currentVertex->Next;
    }

    weights[StartVertex->Index] = 0;

    while (!pq.IsEmpty()) {
        PQNode popped;
        pq.Dequeue(popped);
        currentVertex = popped.Data;
        fringes[currentVertex->Index] = currentVertex;

        Edge* currentEdge = currentVertex->AdjacencyList;
        while (currentEdge != nullptr) {
            Vertex* targetVertex = currentEdge->Target;
            if (!fringes[targetVertex->Index] && weights[currentVertex->Index] + currentEdge->Weight < weights[targetVertex->Index]) {
                PQNode newNode = { weights[currentVertex->Index] + currentEdge->Weight, targetVertex };
                pq.Enqueue(newNode);
                precedences[targetVertex->Index] = currentEdge->From;
                weights[targetVertex->Index] = weights[currentVertex->Index] + currentEdge->Weight;
            }
            currentEdge = currentEdge->Next;
        }
    }

    for (i = 0; i < G->VertexCount; ++i) {
        if (precedences[i] == nullptr) continue;
        int fromIndex = precedences[i]->Index;
        int toIndex = i;
        AddEdge(shortestPathVertices[fromIndex], CreateEdge(shortestPathVertices[fromIndex], shortestPathVertices[toIndex], weights[i]));
    }
}

int main() {
    auto graph = CreateGraph();
    auto primMST = CreateGraph();
    auto kruskalMST = CreateGraph();

    auto A = CreateVertex('A');
    auto B = CreateVertex('B');
    auto C = CreateVertex('C');
    auto D = CreateVertex('D');
    auto E = CreateVertex('E');
    auto F = CreateVertex('F');
    auto G = CreateVertex('G');
    auto H = CreateVertex('H');
    auto I = CreateVertex('I');

    AddVertex(graph, A);
    AddVertex(graph, B);
    AddVertex(graph, C);
    AddVertex(graph, D);
    AddVertex(graph, E);
    AddVertex(graph, F);
    AddVertex(graph, G);
    AddVertex(graph, H);
    AddVertex(graph, I);

    AddEdge(A, CreateEdge(A, E, 247));
    AddEdge(B, CreateEdge(B, A, 35));
    AddEdge(B, CreateEdge(B, C, 126));
    AddEdge(B, CreateEdge(B, F, 150));
    AddEdge(C, CreateEdge(C, D, 117));
    AddEdge(C, CreateEdge(C, F, 162));
    AddEdge(C, CreateEdge(C, G, 220));
    AddEdge(E, CreateEdge(E, H, 98));
    AddEdge(F, CreateEdge(F, E, 82));
    AddEdge(F, CreateEdge(F, G, 154));
    AddEdge(F, CreateEdge(F, H, 120));
    AddEdge(G, CreateEdge(G, I, 106));

    cout << "Dijkstra's Algorithm result:" << endl;
    Dijkstra(graph, B, primMST);
    PrintGraph(primMST);

    DestroyGraph(primMST);
    DestroyGraph(kruskalMST);
    DestroyGraph(graph);

    return 0;
}
