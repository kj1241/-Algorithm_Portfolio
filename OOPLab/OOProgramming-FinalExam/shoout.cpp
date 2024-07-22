#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <vector>

using namespace std;

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

struct GAMEINFO {
    COORD PlayerOnePosition;
    COORD PlayerTwoPosition;
    vector<COORD> PlayerOneBullets;
    vector<COORD> PlayerTwoBullets;
    COORD ZeroZero;
    bool PlayerOneShield;
    bool PlayerTwoShield;
    bool PlayerOneShieldUsed;
    bool PlayerTwoShieldUsed;
};

HANDLE hInput, hOutput;
GAMEINFO GameInfo;
int PlayerOneScore = 0;
int PlayerTwoScore = 0;

void InitializeGame(GAMEINFO& GameInfo);
void Movement(GAMEINFO& GameInfo);
void Draw(GAMEINFO);
void Erase(GAMEINFO);
void UpdateScore();
void LaunchBullet(GAMEINFO& GameInfo, int);
void GameLoop(GAMEINFO& GameInfo);

int main() {
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleMode(hOutput, ENABLE_PROCESSED_INPUT);

    InitializeGame(GameInfo);
    UpdateScore();
    Draw(GameInfo);

    while (1) {
        GameLoop(GameInfo);
    }

    return 0;
}

void InitializeGame(GAMEINFO& GameInfo) {
    GameInfo.PlayerOnePosition.X = 19;
    GameInfo.PlayerOnePosition.Y = 12;
    GameInfo.PlayerTwoPosition.X = 61;
    GameInfo.PlayerTwoPosition.Y = 12;
    GameInfo.PlayerOneBullets.clear();
    GameInfo.PlayerTwoBullets.clear();
    GameInfo.ZeroZero.X = 0;
    GameInfo.ZeroZero.Y = 0;
    GameInfo.PlayerOneShield = false;
    GameInfo.PlayerTwoShield = false;
    GameInfo.PlayerOneShieldUsed = false;
    GameInfo.PlayerTwoShieldUsed = false;

    system("cls");
}

void UpdateScore() {
    COORD ScorePos = { 0, 0 };
    SetConsoleCursorPosition(hOutput, ScorePos);
    cout << "Player 1 Score: " << PlayerOneScore << " | Player 2 Score: " << PlayerTwoScore << endl;
}

void Draw(GAMEINFO GameInfo) {
    COORD boundary = { 0, 1 };
    SetConsoleCursorPosition(hOutput, boundary);
    for (int i = 0; i < 80; i++) cout << "-";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOnePosition);
    cout << "|";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoPosition);
    cout << "|";

    for (const auto& bullet : GameInfo.PlayerOneBullets) {
        SetConsoleCursorPosition(hOutput, bullet);
        cout << ".";
    }

    for (const auto& bullet : GameInfo.PlayerTwoBullets) {
        SetConsoleCursorPosition(hOutput, bullet);
        cout << ".";
    }

    if (GameInfo.PlayerOneShield) {
        SetConsoleCursorPosition(hOutput, { (short)(GameInfo.PlayerOnePosition.X + 1), GameInfo.PlayerOnePosition.Y });
        cout << "O";
    }

    if (GameInfo.PlayerTwoShield) {
        SetConsoleCursorPosition(hOutput, { (short)(GameInfo.PlayerTwoPosition.X - 1), GameInfo.PlayerTwoPosition.Y });
        cout << "O";
    }

    boundary = { 0, 24 };
    SetConsoleCursorPosition(hOutput, boundary);
    for (int i = 0; i < 80; i++) cout << "-";
}

void Erase(GAMEINFO GameInfo) {
    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOnePosition);
    cout << " ";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoPosition);
    cout << " ";

    for (const auto& bullet : GameInfo.PlayerOneBullets) {
        SetConsoleCursorPosition(hOutput, bullet);
        cout << " ";
    }

    for (const auto& bullet : GameInfo.PlayerTwoBullets) {
        SetConsoleCursorPosition(hOutput, bullet);
        cout << " ";
    }

    if (GameInfo.PlayerOneShield) {
        SetConsoleCursorPosition(hOutput, { (short)(GameInfo.PlayerOnePosition.X + 1), GameInfo.PlayerOnePosition.Y });
        cout << " ";
    }

    if (GameInfo.PlayerTwoShield) {
        SetConsoleCursorPosition(hOutput, { (short)(GameInfo.PlayerTwoPosition.X - 1), GameInfo.PlayerTwoPosition.Y });
        cout << " ";
    }
}

void Movement(GAMEINFO& GameInfo) {
    if (_kbhit()) {
        switch (_getch()) {
        case 'q':
            Erase(GameInfo);
            GameInfo.PlayerOnePosition.Y--;
            if (GameInfo.PlayerOnePosition.Y < 2)
                GameInfo.PlayerOnePosition.Y++;
            Draw(GameInfo);
            break;
        case 'a':
            Erase(GameInfo);
            GameInfo.PlayerOnePosition.Y++;
            if (GameInfo.PlayerOnePosition.Y > 23)
                GameInfo.PlayerOnePosition.Y--;
            Draw(GameInfo);
            break;
        case 'd':
            if (!GameInfo.PlayerOneShieldUsed) {
                GameInfo.PlayerOneShield = true;
                GameInfo.PlayerOneShieldUsed = true;
                Draw(GameInfo);
            }
            break;
        case 's':
            LaunchBullet(GameInfo, 1);
            break;
        case 'o':
            Erase(GameInfo);
            GameInfo.PlayerTwoPosition.Y--;
            if (GameInfo.PlayerTwoPosition.Y < 2)
                GameInfo.PlayerTwoPosition.Y++;
            Draw(GameInfo);
            break;
        case 'l':
            Erase(GameInfo);
            GameInfo.PlayerTwoPosition.Y++;
            if (GameInfo.PlayerTwoPosition.Y > 23)
                GameInfo.PlayerTwoPosition.Y--;
            Draw(GameInfo);
            break;
        case 'j':
            if (!GameInfo.PlayerTwoShieldUsed) {
                GameInfo.PlayerTwoShield = true;
                GameInfo.PlayerTwoShieldUsed = true;
                Draw(GameInfo);
            }
            break;
        case 'k':
            LaunchBullet(GameInfo, 2);
            break;
        case 27: 
            exit(0);
        }
    }
}

void GameLoop(GAMEINFO& GameInfo) {
    Movement(GameInfo);

    if (!GameInfo.PlayerOneBullets.empty()) {
        Erase(GameInfo);
        for (auto& bullet : GameInfo.PlayerOneBullets) {
            bullet.X++;
            if (bullet.X == GameInfo.PlayerTwoPosition.X && bullet.Y == GameInfo.PlayerTwoPosition.Y) {
                if (GameInfo.PlayerTwoShield) {
                    GameInfo.PlayerTwoShield = false;
                }
                else {
                    PlayerOneScore++;
                    InitializeGame(GameInfo);
                    UpdateScore();
                }
            }
            else if (bullet.X >= 79) {
                bullet.X = 0;
                bullet.Y = 0;
            }
        }

        GameInfo.PlayerOneBullets.erase(remove_if(GameInfo.PlayerOneBullets.begin(), GameInfo.PlayerOneBullets.end(),
            [](COORD bullet) { return bullet.X == 0 && bullet.Y == 0; }), GameInfo.PlayerOneBullets.end());
        Draw(GameInfo);
    }

    if (!GameInfo.PlayerTwoBullets.empty()) {
        Erase(GameInfo);
        for (auto& bullet : GameInfo.PlayerTwoBullets) {
            bullet.X--;
            if (bullet.X == GameInfo.PlayerOnePosition.X && bullet.Y == GameInfo.PlayerOnePosition.Y) {
                if (GameInfo.PlayerOneShield) {
                    GameInfo.PlayerOneShield = false;
                }
                else {
                    PlayerTwoScore++;
                    InitializeGame(GameInfo);
                    UpdateScore();
                }
            }
            else if (bullet.X <= 0) {
                bullet.X = 79;
                bullet.Y = 0;
            }
        }
 
        GameInfo.PlayerTwoBullets.erase(remove_if(GameInfo.PlayerTwoBullets.begin(), GameInfo.PlayerTwoBullets.end(),
            [](COORD bullet) { return bullet.X == 79 && bullet.Y == 0; }), GameInfo.PlayerTwoBullets.end());
        Draw(GameInfo);
    }

    Sleep(50); 
}

void LaunchBullet(GAMEINFO& GameInfo, int PlayerNumber) {
    COORD bullet;
    if (PlayerNumber == 1) {
        bullet.Y = GameInfo.PlayerOnePosition.Y;
        bullet.X = GameInfo.PlayerOnePosition.X + 1;
        GameInfo.PlayerOneBullets.push_back(bullet);
    }
    if (PlayerNumber == 2) {
        bullet.Y = GameInfo.PlayerTwoPosition.Y;
        bullet.X = GameInfo.PlayerTwoPosition.X - 1;
        GameInfo.PlayerTwoBullets.push_back(bullet);
    }
}
