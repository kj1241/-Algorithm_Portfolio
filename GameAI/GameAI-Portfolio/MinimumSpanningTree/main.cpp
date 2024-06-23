#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <limits>
#include <memory>

using namespace std;

constexpr int MAX_WEIGHT = numeric_limits<int>::max();

struct Edge;
struct Vertex {
    char Data;
    vector<Edge*> AdjacencyList;
    bool Visited;
    int Index;
    Vertex(char data) : Data(data), Visited(false), Index(-1) {}
};

struct Edge {
    Vertex* From;
    Vertex* Target;
    int Weight;
    Edge(Vertex* from, Vertex* target, int weight) : From(from), Target(target), Weight(weight) {}
};

struct Graph {
    vector<unique_ptr<Vertex>> Vertices;
};

unique_ptr<Graph> CreateGraph() {
    return make_unique<Graph>();
}

void DestroyGraph(Graph* G) {
    for (auto& vertex : G->Vertices) {
        for (auto& edge : vertex->AdjacencyList) {
            delete edge;
        }
    }
}

unique_ptr<Vertex> CreateVertex(char Data) {
    return make_unique<Vertex>(Data);
}

void AddVertex(Graph* G, unique_ptr<Vertex> V) {
    V->Index = G->Vertices.size();
    G->Vertices.push_back(move(V));
}

void AddEdge(Vertex* V, Edge* E) {
    V->AdjacencyList.push_back(E);
}

void PrintGraph(const Graph* G) {
    for (const auto& V : G->Vertices) {
        cout << V->Data << " : ";
        for (const auto& E : V->AdjacencyList) {
            cout << E->Target->Data << "[" << E->Weight << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

struct PQNode {
    int Priority;
    Vertex* Data;
    PQNode(int priority, Vertex* data) : Priority(priority), Data(data) {}
    bool operator<(const PQNode& other) const {
        return Priority > other.Priority;
    }
};

void Prim(Graph* G, Vertex* StartVertex, Graph* MST) {
    priority_queue<PQNode> PQ;
    vector<int> Weights(G->Vertices.size(), MAX_WEIGHT);
    vector<Vertex*> MSTVertices(G->Vertices.size(), nullptr);
    vector<Vertex*> Fringes(G->Vertices.size(), nullptr);
    vector<Vertex*> Precedences(G->Vertices.size(), nullptr);

    for (size_t i = 0; i < G->Vertices.size(); ++i) {
        MSTVertices[i] = new Vertex(G->Vertices[i]->Data);
        AddVertex(MST, unique_ptr<Vertex>(MSTVertices[i]));
    }

    Weights[StartVertex->Index] = 0;
    PQ.push(PQNode(0, StartVertex));

    while (!PQ.empty()) {
        PQNode Popped = PQ.top();
        PQ.pop();
        Vertex* CurrentVertex = Popped.Data;
        Fringes[CurrentVertex->Index] = CurrentVertex;

        for (auto& CurrentEdge : CurrentVertex->AdjacencyList) {
            Vertex* TargetVertex = CurrentEdge->Target;
            if (!Fringes[TargetVertex->Index] && CurrentEdge->Weight < Weights[TargetVertex->Index]) {
                PQ.push(PQNode(CurrentEdge->Weight, TargetVertex));
                Precedences[TargetVertex->Index] = CurrentEdge->From;
                Weights[TargetVertex->Index] = CurrentEdge->Weight;
            }
        }
    }

    for (size_t i = 0; i < G->Vertices.size(); ++i) {
        if (Precedences[i] != nullptr) {
            int FromIndex = Precedences[i]->Index;
            int ToIndex = i;
            AddEdge(MSTVertices[FromIndex], new Edge(MSTVertices[FromIndex], MSTVertices[ToIndex], Weights[i]));
            AddEdge(MSTVertices[ToIndex], new Edge(MSTVertices[ToIndex], MSTVertices[FromIndex], Weights[i]));
        }
    }
}

struct DisjointSet {
    DisjointSet* Parent;
    void* Data;
    DisjointSet(void* data) : Parent(nullptr), Data(data) {}
};

DisjointSet* DS_FindSet(DisjointSet* Set) {
    if (Set->Parent != nullptr) {
        Set->Parent = DS_FindSet(Set->Parent);
        return Set->Parent;
    }
    return Set;
}

void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2) {
    Set2 = DS_FindSet(Set2);
    Set2->Parent = Set1;
}

unique_ptr<DisjointSet> DS_MakeSet(void* NewData) {
    return make_unique<DisjointSet>(NewData);
}

void Kruskal(Graph* G, Graph* MST) {
    vector<unique_ptr<DisjointSet>> VertexSet(G->Vertices.size());
    vector<Vertex*> MSTVertices(G->Vertices.size());

    priority_queue<PQNode> PQ;

    for (size_t i = 0; i < G->Vertices.size(); ++i) {
        VertexSet[i] = DS_MakeSet(G->Vertices[i].get());
        MSTVertices[i] = new Vertex(G->Vertices[i]->Data);
        AddVertex(MST, unique_ptr<Vertex>(MSTVertices[i]));

        for (auto& CurrentEdge : G->Vertices[i]->AdjacencyList) {
            PQ.push(PQNode(CurrentEdge->Weight, reinterpret_cast<Vertex*>(CurrentEdge)));
        }
    }

    while (!PQ.empty()) {
        PQNode Popped = PQ.top();
        PQ.pop();

        Edge* CurrentEdge = reinterpret_cast<Edge*>(Popped.Data);
        int FromIndex = CurrentEdge->From->Index;
        int ToIndex = CurrentEdge->Target->Index;

        if (DS_FindSet(VertexSet[FromIndex].get()) != DS_FindSet(VertexSet[ToIndex].get())) {
            AddEdge(MSTVertices[FromIndex], new Edge(MSTVertices[FromIndex], MSTVertices[ToIndex], CurrentEdge->Weight));
            AddEdge(MSTVertices[ToIndex], new Edge(MSTVertices[ToIndex], MSTVertices[FromIndex], CurrentEdge->Weight));
            DS_UnionSet(VertexSet[FromIndex].get(), VertexSet[ToIndex].get());
        }
    }
}

int main() {
    unique_ptr<Graph> graph = CreateGraph();
    unique_ptr<Graph> PrimMST = CreateGraph();
    unique_ptr<Graph> KruskalMST = CreateGraph();

    auto A = CreateVertex('A');
    auto B = CreateVertex('B');
    auto C = CreateVertex('C');
    auto D = CreateVertex('D');
    auto E = CreateVertex('E');
    auto F = CreateVertex('F');
    auto G = CreateVertex('G');
    auto H = CreateVertex('H');
    auto I = CreateVertex('I');

    AddVertex(graph.get(), move(A));
    AddVertex(graph.get(), move(B));
    AddVertex(graph.get(), move(C));
    AddVertex(graph.get(), move(D));
    AddVertex(graph.get(), move(E));
    AddVertex(graph.get(), move(F));
    AddVertex(graph.get(), move(G));
    AddVertex(graph.get(), move(H));
    AddVertex(graph.get(), move(I));

    AddEdge(graph->Vertices[0].get(), new Edge(graph->Vertices[0].get(), graph->Vertices[1].get(), 35));
    AddEdge(graph->Vertices[0].get(), new Edge(graph->Vertices[0].get(), graph->Vertices[4].get(), 247));
    AddEdge(graph->Vertices[1].get(), new Edge(graph->Vertices[1].get(), graph->Vertices[0].get(), 35));
    AddEdge(graph->Vertices[1].get(), new Edge(graph->Vertices[1].get(), graph->Vertices[2].get(), 126));
    AddEdge(graph->Vertices[1].get(), new Edge(graph->Vertices[1].get(), graph->Vertices[5].get(), 150));
    AddEdge(graph->Vertices[2].get(), new Edge(graph->Vertices[2].get(), graph->Vertices[1].get(), 126));
    AddEdge(graph->Vertices[2].get(), new Edge(graph->Vertices[2].get(), graph->Vertices[3].get(), 117));
    AddEdge(graph->Vertices[2].get(), new Edge(graph->Vertices[2].get(), graph->Vertices[5].get(), 162));
    AddEdge(graph->Vertices[2].get(), new Edge(graph->Vertices[2].get(), graph->Vertices[6].get(), 220));
    AddEdge(graph->Vertices[3].get(), new Edge(graph->Vertices[3].get(), graph->Vertices[2].get(), 117));
    AddEdge(graph->Vertices[3].get(), new Edge(graph->Vertices[3].get(), graph->Vertices[8].get(), 125));
    AddEdge(graph->Vertices[4].get(), new Edge(graph->Vertices[4].get(), graph->Vertices[0].get(), 247));
    AddEdge(graph->Vertices[4].get(), new Edge(graph->Vertices[4].get(), graph->Vertices[5].get(), 82));
    AddEdge(graph->Vertices[4].get(), new Edge(graph->Vertices[4].get(), graph->Vertices[7].get(), 98));
    AddEdge(graph->Vertices[5].get(), new Edge(graph->Vertices[5].get(), graph->Vertices[1].get(), 150));
    AddEdge(graph->Vertices[5].get(), new Edge(graph->Vertices[5].get(), graph->Vertices[2].get(), 162));
    AddEdge(graph->Vertices[5].get(), new Edge(graph->Vertices[5].get(), graph->Vertices[4].get(), 82));
    AddEdge(graph->Vertices[5].get(), new Edge(graph->Vertices[5].get(), graph->Vertices[6].get(), 154));
    AddEdge(graph->Vertices[5].get(), new Edge(graph->Vertices[5].get(), graph->Vertices[7].get(), 120));
    AddEdge(graph->Vertices[6].get(), new Edge(graph->Vertices[6].get(), graph->Vertices[2].get(), 220));
    AddEdge(graph->Vertices[6].get(), new Edge(graph->Vertices[6].get(), graph->Vertices[5].get(), 154));
    AddEdge(graph->Vertices[6].get(), new Edge(graph->Vertices[6].get(), graph->Vertices[8].get(), 106));
    AddEdge(graph->Vertices[7].get(), new Edge(graph->Vertices[7].get(), graph->Vertices[4].get(), 98));
    AddEdge(graph->Vertices[7].get(), new Edge(graph->Vertices[7].get(), graph->Vertices[5].get(), 120));
    AddEdge(graph->Vertices[8].get(), new Edge(graph->Vertices[8].get(), graph->Vertices[6].get(), 106));

    cout << "Prim's Algorithm result:" << endl;
    Prim(graph.get(), graph->Vertices[0].get(), PrimMST.get());
    PrintGraph(PrimMST.get());

    cout << "Kruskal's Algorithm result:" << endl;
    Kruskal(graph.get(), KruskalMST.get());
    PrintGraph(KruskalMST.get());

    DestroyGraph(graph.get());
    DestroyGraph(PrimMST.get());
    DestroyGraph(KruskalMST.get());

    return 0;
}
