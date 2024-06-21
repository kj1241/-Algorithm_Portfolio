#include <iostream>
#include <list>
#include <cmath>
using namespace std;

#define UNIT_DISTANCE 1
#define MAPSIZE 8

class Node {
public:
    int posX, posY;
    int F, G, H;  // F(Fitness), G(Goal), H(Heuristic)
    Node* parent;
    bool IsBlock;
};

Node mapData[MAPSIZE][MAPSIZE];

list<Node*> openList;
Node* Start;
Node* End;

void InitializeNodes() {
    for (int i = 0; i < MAPSIZE; ++i) {
        for (int j = 0; j < MAPSIZE; ++j) {
            mapData[i][j].posX = j;
            mapData[i][j].posY = i;
            mapData[i][j].F = mapData[i][j].G = mapData[i][j].H = 0;
            mapData[i][j].IsBlock = false;
            mapData[i][j].parent = nullptr;
        }
    }
}

void AstarInsertOpenList(Node* node, Node* parent, int Gdist = 0) {
    if (node->posX < 0 || node->posY < 0 || node->posX >= MAPSIZE || node->posY >= MAPSIZE || node->IsBlock)
        return;

    for (auto iter = openList.begin(); iter != openList.end(); ++iter) {
        if (node == *iter) {
            if (Gdist < node->G) {
                openList.erase(iter);
            }
            else {
                return;
            }
            break;
        }
    }

    node->parent = parent;
    node->G = Gdist;
    node->H = UNIT_DISTANCE * (abs(End->posX - node->posX) + abs(End->posY - node->posY));
    node->F = node->G + node->H;

    for (auto iter = openList.begin(); iter != openList.end(); ++iter) {
        if (node->F <= (*iter)->F) {
            openList.insert(iter, node);
            return;
        }
    }
    openList.push_back(node);
}

void AstarSetObstacleBlock(int x, int y) {
    mapData[y][x].IsBlock = true;
}

void AstarSetStartEndPoints(Node* S, Node* E) {
    Start = S;
    End = E;
    AstarInsertOpenList(Start, nullptr, 0);
}

void AstarFindRoute() {
    Node* node;
    while (!openList.empty()) {
        auto iter = openList.begin();
        node = *iter;
        openList.erase(iter);
        node->IsBlock = true;

        if (node == End) break;

        int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},         { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        for (auto& dir : directions) {
            int newY = node->posY + dir[0];
            int newX = node->posX + dir[1];
            if (newX >= 0 && newY >= 0 && newX < MAPSIZE && newY < MAPSIZE) {
                double distance=0;
                if (dir[0] != 0 && dir[1] != 0)
                    distance = 1.4 * UNIT_DISTANCE;
                else
                    distance = UNIT_DISTANCE;
                AstarInsertOpenList(&mapData[newY][newX], node, node->G + distance);
            }
        }
    }
}

void TestPrint() {
    for (int i = 0; i < MAPSIZE; ++i) {
        for (int j = 0; j < MAPSIZE; ++j) {
            cout << "[" << j << "," << i << "]";
            cout.width(3);
            cout << mapData[i][j].F << " ";
        }
        cout << endl;
    }
}

void AstarMakePath() {
    cout << "Result : ";
    Node* node = End;
    while (node != Start) {
        cout << "[" << node->posX << "," << node->posY << "] ";
        node = node->parent;
    }
    cout << "[" << node->posX << "," << node->posY << "] ";
}

int main() {
    cout << "A* 알고리즘" << endl << endl;

    InitializeNodes();

    AstarSetObstacleBlock(4, 2);
    AstarSetObstacleBlock(4, 3);
    AstarSetObstacleBlock(4, 4);
    AstarSetObstacleBlock(3, 2);
    AstarSetObstacleBlock(2, 4);
    AstarSetObstacleBlock(3, 4);

    AstarSetStartEndPoints(&mapData[3][2], &mapData[3][6]);

    cout << endl << "-----------------초기 세팅----------------" << endl << endl;
    TestPrint();
    AstarFindRoute();
    cout << endl << "-----------------전체 결과----------------" << endl << endl;
    TestPrint();
    cout << endl << "-----------------최단 경로----------------" << endl << endl;
    AstarMakePath();

    return 0;
}
