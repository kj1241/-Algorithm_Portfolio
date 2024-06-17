#include <iostream>
#include <string>

enum VisitStatus {
    NotVisited,
    Visited
};

struct Edge;

struct Vertex {
    char Data;
    Vertex* Next;
    Edge* AdjacencyList;
    VisitStatus Visited;
    int Index;

    Vertex(char data) : Data(data), Next(nullptr), AdjacencyList(nullptr), Visited(NotVisited), Index(-1) {}
};

struct Edge {
    Vertex* From;
    Vertex* Target;
    Edge* Next;
    int Weight;

    Edge(Vertex* from, Vertex* target, int weight) : From(from), Target(target), Next(nullptr), Weight(weight) {}
};

class Graph {
public:
    Graph();
    ~Graph();

    void AddVertex(Vertex* V);
    void AddEdge(Vertex* V, Edge* E);
    void PrintGraph() const;

private:
    Vertex* Vertices;
    int VertexCount;

    void DestroyVertex(Vertex* V);
    void DestroyEdge(Edge* E);
};

Graph::Graph() : Vertices(nullptr), VertexCount(0) {}

Graph::~Graph() {
    while (Vertices != nullptr) {
        Vertex* vertices = Vertices->Next;
        DestroyVertex(Vertices);
        Vertices = vertices;
    }
}

void Graph::AddVertex(Vertex* V) {
    if (Vertices == nullptr) {
        Vertices = V;
    }
    else {
        Vertex* vertexList = Vertices;
        while (vertexList->Next != nullptr) {
            vertexList = vertexList->Next;
        }
        vertexList->Next = V;
    }
    V->Index = VertexCount++;
}

void Graph::AddEdge(Vertex* V, Edge* E) {
    if (V->AdjacencyList == nullptr) {
        V->AdjacencyList = E;
    }
    else {
        Edge* adjacencyList = V->AdjacencyList;
        while (adjacencyList->Next != nullptr) {
            adjacencyList = adjacencyList->Next;
        }
        adjacencyList->Next = E;
    }
}

void Graph::PrintGraph() const {
    Vertex* V = Vertices;
    while (V != nullptr) {
        std::cout << V->Data << " : ";
        Edge* E = V->AdjacencyList;
        while (E != nullptr) {
            std::cout << E->Target->Data << "[" << E->Weight << "] ";
            E = E->Next;
        }
        std::cout << std::endl;
        V = V->Next;
    }
    std::cout << std::endl;
}

void Graph::DestroyVertex(Vertex* V) {
    while (V->AdjacencyList != nullptr) {
        Edge* edge = V->AdjacencyList->Next;
        DestroyEdge(V->AdjacencyList);
        V->AdjacencyList = edge;
    }
    delete V;
}

void Graph::DestroyEdge(Edge* E) {
    delete E;
}

int main() {
    // 그래프 생성
    Graph G;

    // 정점 생성
    Vertex* V1 = new Vertex('1');
    Vertex* V2 = new Vertex('2');
    Vertex* V3 = new Vertex('3');
    Vertex* V4 = new Vertex('4');
    Vertex* V5 = new Vertex('5');

    // 그래프에 정점을 추가
    G.AddVertex(V1);
    G.AddVertex(V2);
    G.AddVertex(V3);
    G.AddVertex(V4);
    G.AddVertex(V5);

    // 정점과 정점을 간선으로 잇기
    G.AddEdge(V1, new Edge(V1, V2, 0));
    G.AddEdge(V1, new Edge(V1, V3, 0));
    G.AddEdge(V1, new Edge(V1, V4, 0));
    G.AddEdge(V1, new Edge(V1, V5, 0));

    G.AddEdge(V2, new Edge(V2, V1, 0));
    G.AddEdge(V2, new Edge(V2, V3, 0));
    G.AddEdge(V2, new Edge(V2, V5, 0));

    G.AddEdge(V3, new Edge(V3, V1, 0));
    G.AddEdge(V3, new Edge(V3, V2, 0));

    G.AddEdge(V4, new Edge(V4, V1, 0));
    G.AddEdge(V4, new Edge(V4, V5, 0));

    G.AddEdge(V5, new Edge(V5, V1, 0));
    G.AddEdge(V5, new Edge(V5, V2, 0));
    G.AddEdge(V5, new Edge(V5, V4, 0));

    G.PrintGraph();

    // 그래프 소멸 - Graph 소멸자는 자동으로 호출됨

    return 0;
}
