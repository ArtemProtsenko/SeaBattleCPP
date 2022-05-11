#include "Game.h"
#include <iostream>
#include <vector>

using namespace variables;
using namespace constants;
using namespace functions;
using namespace std;

vars var;
consts constVar;

string playerOneType = var.playerOneType;
string playerTwoType = var.playerTwoType;

const int width = constVar.width;
const int height = constVar.height;

vector<vector<char>> playerOneField;
vector<vector<char>> playerTwoField;

int playerOneMode; // 1 means hide ships, 2 means show ships
int playerTwoMode;

int playerOneShipsLeft = 20;
int playerTwoShipsLeft = 20;

int playerOneShootX;
int playerOneShootY;
int playerTwoShootX;
int playerTwoShootY;

int carrierLength = constVar.carrierLength;
int cruiserLength = constVar.cruiserLength;
int battleShipLength = constVar.battleShipLength;
int miniShipLength = constVar.miniShipLength;

int axisForShips;

string cheatCode;

bool isPerson(string playerType)
{
    if (playerType == "human" || playerType == "Human")
    {
        return true;
    }
    return false;
}

bool enteredCorrectType(string playerType)
{
    if (playerType != "bot" && playerType != "Bot" && playerType != "human" && playerType != "Human")
    {
        return false;
    }
    return true;
}

bool cantPlaceBlock(vector<vector<char>> field, int x, int y)
{
    if (x < 0)
    {
        x++;
    }
    else if (x >= width)
    {
        x--;
    }
    if (y < 0)
    {
        y++;
    }
    else if (y >= height)
    {
        y--;
    }
    return field[x][y] != 'Y';
}

int wayToPlaceShip(int coordX, int coordY, vector<vector<char>> field, int length, int& axis)
{
    axis = rand() % 2;

    if (axis == 1)
    {
        for (int i = 0; i < length; i++)
        {
            if (cantPlaceBlock(field, coordX + i, coordY) || cantPlaceBlock(field, coordX + i, coordY + 1) ||
                cantPlaceBlock(field, coordX + i, coordY - 1))
            {
                return 0;
            }
        }

        return 1;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            if (cantPlaceBlock(field, coordX, coordY + i) || cantPlaceBlock(field, coordX + 1, coordY + i) ||
                cantPlaceBlock(field, coordX - 1, coordY + i))
            {
                return 0;
            }
        }

        return 2;
    }
}

bool isCheated()
{
    return cheatCode == "cheat";
}

void Instructions()
{
    cout << "This is Sea Battle. there are 2 axis: x & y." << endl;
    cout << "x - horizontal, y - vertical." << endl;
    cout << "Write first coordinate x from 1 to 9, then press enter and write y." << endl;
    cout << "# - you hit ship, ^ - miss." << endl;
    cout << "Good luck!" << endl;;
    system("pause");
    system("clr");
}

void inputPlayerTypes()
{
    cout << "Enter player one type: ";
    cin >> playerOneType;
    cout << "Enter player two type: ";
    cin >> playerTwoType;
}

void setPlayersFieldMode()
{
    if (isPerson(playerOneType) && isPerson(playerTwoType))
    {
        playerOneMode = 1;
        playerTwoMode = 1;
    }
    else if (isPerson(playerOneType) || isPerson(playerTwoType))
    {
        if (isPerson(playerOneType))
        {
            playerOneMode = 1;
            playerTwoMode = 2;
        }
        else
        {
            playerOneMode = 2;
            playerTwoMode = 1;
        }
    }
    else
    {
        playerOneMode = 2;
        playerTwoMode = 2;
    }
}

void SetField(vector<vector<char>> &field)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            field[j][i] = 'Y';
        }
    }
}

void placeShip(vector<vector<char>> &field, int length, int coordX, int coordY, int axis)
{
    for (int i = 0; i < length; i++)
    {
        if (axis == 1)
        {
            field[coordX + i][coordY] = '@';
        }
        else
        {
            field[coordX][coordY + i] = '@';
        }
    }
}

void SetPlayerShip(vector<vector<char>> &field, int length)
{
    while (true)
    {
        int x = rand() % width;
        int y = rand() % height;

        if (wayToPlaceShip(x, y, field, length, axisForShips) == 1 || wayToPlaceShip(x, y, field, length, axisForShips)
            == 2)
        {
            placeShip(field, length, x, y, axisForShips);
            break;
        }
    }
}

void SetPlayerShips(vector<vector<char>> &field)
{
    SetPlayerShip(field, carrierLength);
    SetPlayerShip(field, cruiserLength);
    SetPlayerShip(field, battleShipLength);
    SetPlayerShip(field, miniShipLength);
}

void DrawField(vector<vector<char>> field, int playerMode)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (playerMode == 1)
            {
                if(field[j][i] != '@')
                {
                    cout << field[j][i];
                }
                else
                {
                    cout << 'Y';
                }
            }
            else if (playerMode == 2)
            {
                cout << field[j][i];
            }
        }
        cout << endl;
    }
}

void PlayerInput(string playerCreature, int &playerShootX, int &playerShootY)
{
    if (isPerson(playerCreature))
    {
        cin >> playerShootX;
        cin >> playerShootY;
    }
    else
    {
        playerShootX = rand() % width;
        playerShootY = rand() % height;
    }
}

void Shoot(char &fieldTile, int &shipsLeft)
{
    if (fieldTile == '@')
    {
        fieldTile = '#';
        shipsLeft--;
        Shoot(fieldTile, shipsLeft);
    }
    else if (fieldTile == 'Y')
    {
        fieldTile = '^';
    }
}

void tryToShoot(string playerCreature, char &enemyFieldTile, int &playerShipsLeft)
{
    if (!isPerson(playerCreature))
    {
        do
        {
            Shoot(enemyFieldTile, playerShipsLeft);
        }
        while (enemyFieldTile == '#' || enemyFieldTile == '^');
    }
    else
    {
        Shoot(enemyFieldTile, playerShipsLeft);
    }
}

void SetPlayers()
{
    SetField(playerOneField);
    SetField(playerTwoField);
    SetPlayerShips(playerOneField);
    SetPlayerShips(playerTwoField);
}

void DrawGameTurn()
{
    setPlayersFieldMode();
    DrawField(playerOneField, playerOneMode);
    cout << endl;
    DrawField(playerTwoField, playerTwoMode);
}

void playerInputAsker()
{
    inputPlayerTypes();

    while (true)
    {
        if (!enteredCorrectType(playerOneType) && !enteredCorrectType(playerTwoType))
        {
            system("clr");
            inputPlayerTypes();
        }
        else
        {
            break;
        }
    }
}

void Turn(string playerCreature, int &playerShootX, int &playerShootY, vector<vector<char>> enemyField, int &playerShipsLeft)
{
    DrawGameTurn();
    PlayerInput(playerCreature, playerShootX, playerShootY);
    tryToShoot(playerCreature, enemyField[playerShootX][playerShootY], playerShipsLeft);
    cout << "Press enter to continue...";
    cin >> cheatCode;
    system("clr");
}

void gameLoop()
{
    playerInputAsker();

    SetPlayers();

    do
    {
        Turn(playerOneType, playerOneShootX, playerOneShootY, playerTwoField, playerTwoShipsLeft);
        if (isCheated())
        {
            playerTwoShipsLeft = 0;
            break;
        }
        Turn(playerTwoType, playerTwoShootX, playerTwoShootY, playerOneField, playerOneShipsLeft);
        if (isCheated())
        {
            playerOneShipsLeft = 0;
            break;
        }
    }
    while (playerTwoShipsLeft > 0 && playerOneShipsLeft > 0);
}

void GameEnd()
{
    system("clr");
    if (playerTwoShipsLeft <= 0)
    {
        cout << "Player 1 won that round!!!" << endl;
    }
    else if (playerOneShipsLeft <= 0)
    {
        cout << "Player 2 won that round!!!" << endl;
    }
}
