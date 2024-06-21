#include <iostream>
#include <stack>
using namespace std;

#define MAPSIZE 8

class Node {
public:
    int posX, posY;
    Node* parent;
    bool IsBlock;
    bool visited;

    Node() : posX(0), posY(0), parent(nullptr), IsBlock(false), visited(false) {}
};

Node mapData[MAPSIZE][MAPSIZE];
stack<Node*> dfsStack;
Node* Start;
Node* End;

void InitializeNodes() {
    for (int i = 0; i < MAPSIZE; ++i) {
        for (int j = 0; j < MAPSIZE; ++j) {
            mapData[i][j].posX = j;
            mapData[i][j].posY = i;
            mapData[i][j].IsBlock = false;
            mapData[i][j].parent = nullptr;
            mapData[i][j].visited = false;
        }
    }
}

void DFSInsertStack(Node* node, Node* parent) {
    if (node->posX < 0 || node->posY < 0 || node->posX >= MAPSIZE || node->posY >= MAPSIZE || node->IsBlock || node->visited)
        return;

    node->parent = parent;
    dfsStack.push(node);
}

void DFSSetObstacleBlock(int x, int y) {
    mapData[y][x].IsBlock = true;
}

void DFSSetStartEndPoints(Node* S, Node* E) {
    Start = S;
    End = E;
    dfsStack.push(Start);
}

void DFSFindRoute() {
    Node* node;
    while (!dfsStack.empty()) {
        node = dfsStack.top();
        dfsStack.pop();

        if (node->visited) continue;
        node->visited = true;

        if (node == End) break;

        int directions[4][2] = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        for (auto& dir : directions) {
            int newY = node->posY + dir[0];
            int newX = node->posX + dir[1];
            if (newX >= 0 && newY >= 0 && newX < MAPSIZE && newY < MAPSIZE) {
                DFSInsertStack(&mapData[newY][newX], node);
            }
        }
    }
}

void TestPrint() {
    for (int i = 0; i < MAPSIZE; ++i) {
        for (int j = 0; j < MAPSIZE; ++j) {
            cout << "[" << j << "," << i << "]";
            cout.width(3);
            if (mapData[i][j].visited)
                cout << "V";
            else
                cout<< " ";
        }
        cout << endl;
    }
}

void DFSMakePath() {
    cout << "Result : ";
    Node* node = End;
    while (node != Start) {
        cout << "[" << node->posX << "," << node->posY << "] ";
        node = node->parent;
    }
    cout << "[" << node->posX << "," << node->posY << "] ";
}

int main() {
    cout << "DFS 알고리즘" << endl << endl;

    InitializeNodes();

    DFSSetObstacleBlock(4, 2);
    DFSSetObstacleBlock(4, 3);
    DFSSetObstacleBlock(4, 4);
    DFSSetObstacleBlock(3, 2);
    DFSSetObstacleBlock(2, 4);
    DFSSetObstacleBlock(3, 4);

    DFSSetStartEndPoints(&mapData[3][2], &mapData[3][6]);

    cout << endl << "-----------------초기 세팅----------------" << endl << endl;
    TestPrint();
    DFSFindRoute();
    cout << endl << "-----------------전체 결과----------------" << endl << endl;
    TestPrint();
    cout << endl << "-----------------경로----------------" << endl << endl;
    DFSMakePath();

    return 0;
}
