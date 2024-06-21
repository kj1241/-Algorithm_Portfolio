#include <iostream>
#include <queue>
#include <list>
using namespace std;

#define MAPSIZE 8

class Node {
public:
    int posX, posY;
    int distance;  // distance from the start node
    Node* parent;
    bool IsBlock;

    Node() : posX(0), posY(0), distance(0), parent(nullptr), IsBlock(false) {}
};

Node mapData[MAPSIZE][MAPSIZE];
queue<Node*> bfsQueue;
Node* Start;
Node* End;

void InitializeNodes() {
    for (int i = 0; i < MAPSIZE; ++i) {
        for (int j = 0; j < MAPSIZE; ++j) {
            mapData[i][j].posX = j;
            mapData[i][j].posY = i;
            mapData[i][j].distance = 0;
            mapData[i][j].IsBlock = false;
            mapData[i][j].parent = nullptr;
        }
    }
}

void BFSInsertQueue(Node* node, Node* parent) {
    if (node->posX < 0 || node->posY < 0 || node->posX >= MAPSIZE || node->posY >= MAPSIZE || node->IsBlock)
        return;

    if (node->parent != nullptr)
        return;

    node->parent = parent;
    node->distance = parent->distance + 1;
    bfsQueue.push(node);
}

void BFSSetObstacleBlock(int x, int y) {
    mapData[y][x].IsBlock = true;
}

void BFSSetStartEndPoints(Node* S, Node* E) {
    Start = S;
    End = E;
    bfsQueue.push(Start);
}

void BFSFindRoute() {
    Node* node;
    while (!bfsQueue.empty()) {
        node = bfsQueue.front();
        bfsQueue.pop();

        if (node == End) break;

        int directions[4][2] = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        for (auto& dir : directions) {
            int newY = node->posY + dir[0];
            int newX = node->posX + dir[1];
            if (newX >= 0 && newY >= 0 && newX < MAPSIZE && newY < MAPSIZE) {
                BFSInsertQueue(&mapData[newY][newX], node);
            }
        }
    }
}

void TestPrint() {
    for (int i = 0; i < MAPSIZE; ++i) {
        for (int j = 0; j < MAPSIZE; ++j) {
            cout << "[" << j << "," << i << "]";
            cout.width(3);
            cout << mapData[i][j].distance << " ";
        }
        cout << endl;
    }
}

void BFSMakePath() {
    cout << "Result : ";
    Node* node = End;
    while (node != Start) {
        cout << "[" << node->posX << "," << node->posY << "] ";
        node = node->parent;
    }
    cout << "[" << node->posX << "," << node->posY << "] ";
}

int main() {
    cout << "BFS 알고리즘" << endl << endl;

    InitializeNodes();

    BFSSetObstacleBlock(4, 2);
    BFSSetObstacleBlock(4, 3);
    BFSSetObstacleBlock(4, 4);
    BFSSetObstacleBlock(3, 2);
    BFSSetObstacleBlock(2, 4);
    BFSSetObstacleBlock(3, 4);

    BFSSetStartEndPoints(&mapData[3][2], &mapData[3][6]);

    cout << endl << "-----------------초기 세팅----------------" << endl << endl;
    TestPrint();
    BFSFindRoute();
    cout << endl << "-----------------전체 결과----------------" << endl << endl;
    TestPrint();
    cout << endl << "-----------------최단 경로----------------" << endl << endl;
    BFSMakePath();

    return 0;
}
