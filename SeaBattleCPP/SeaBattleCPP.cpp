#include <iostream>
#include <iomanip>
using namespace std;

string playerOneType; // human or bot
string playerTwoType;

const int width = 9;
const int height = 9;

char playerOneField[width][height];
char playerTwoField[width][height];

int playerOneMode; // 1 means hide ships, 2 means show ships
int playerTwoMode;

int playerOneShipsLeft = 20;
int playerTwoShipsLeft = 20;

int playerOneShootX;
int playerOneShootY;
int playerTwoShootX;
int playerTwoShootY;

int carrierLength = 4;
int cruiserLength = 3;
int battleShipLength = 2;
int miniShipLength = 1;

int axisForShips;

string cheatCode;

bool isPerson(string playerType)
{
    if(playerType == "human" || playerType == "Human")
    {
        return true;
    }
    return false;
}

bool enteredCorrectType(string playerType)
{
    if(playerType != "bot" && playerType != "Bot" && playerType != "human" && playerType != "Human")
    {
        return false;
    }
    return  true;
}

int wayToPlaceShip(int coordX, int coordY, char field[width][height], int length, int &axis)
{
    axis = rand() % 2;
    
    if(axis == 1)
    {
        for(int i = 0; i < length; i++)
        {
            if(field[coordX + i][coordY] != 'Y')
            {
                return 0;
            }
        }
        
        return 1;
    }
    else
    {
        for(int i = 0; i < length; i++)
        {
            if(field[coordX][coordY + i] != 'Y')
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
    if(isPerson(playerOneType) && isPerson(playerTwoType))
    {
        playerOneMode = 1;
        playerTwoMode = 1;
    }
    else if(isPerson(playerOneType) || isPerson(playerTwoType))
    {
        if(isPerson(playerOneType))
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

void SetField(char (&field)[width][height])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            field[j][i] = 'Y';
        }
    }
}

void placeShip(char (&field)[width][height], int length, int coordX, int coordY, int axis)
{
    for(int i = 0; i < length; i++)
    {
        if(axis == 1)
        {
            field[coordX + i][coordY] = '@';
        }
        else
        {
            field[coordX][coordY + i] = '@';
        }
    }
}

void SetPlayerShip(char (&field)[width][height], int length)
{
    while(true)
    {
        int x = rand() % width;
        int y = rand() % height;
    
        if(wayToPlaceShip(x, y, field, length, axisForShips) == 1 || wayToPlaceShip(x, y, field, length, axisForShips) == 2)
        {
            placeShip(field, length, x, y, axisForShips);
            break;
        }
    }
}

void SetPlayerShips(char (&field)[width][height])
{
    SetPlayerShip(field, carrierLength);
    SetPlayerShip(field, cruiserLength);
    SetPlayerShip(field, battleShipLength);
    SetPlayerShip(field, miniShipLength);
}

void DrawField(char field[width][height], int playerMode)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (playerMode == 1)
            {
                cout << 'Y';
            }
            else if(playerMode == 2)
            {
                cout << field[j][i];
            }
        }
        cout << endl;
    }
}

void PlayerInput(string playerCreature, int &playerShootX, int &playerShootY)
{
    if (playerCreature == "human" || playerCreature == "Human")
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

void Shoot(int x, int y, char (&field)[width][height], int &shipsLeft)
{
    if (field[x][y] == '@')
    {
        field[x][y] = '#';
        shipsLeft--;
        Shoot(x, y, field, shipsLeft);
    }
    else if (field[x][y] == 'Y')
    {
        field[x][y] = '^';
    }
}

void tryToShoot(string playerCreature, int playerShootX, int playerShootY, char (&enemyField)[width][height], int &playerShipsLeft)
{
    
    if(!isPerson(playerCreature))
    {
        do
        {
            Shoot(playerShootX, playerShootY, enemyField, playerShipsLeft);
        } while(enemyField[playerShootX][playerShootY] == '#' || enemyField[playerShootX][playerShootY] == '^');
    }
    else
    {
        Shoot(playerShootX, playerShootY, enemyField, playerShipsLeft);
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

void Turn(string playerCreature, int &playerShootX, int &playerShootY, char (&enemyField)[width][height], int &playerShipsLeft)
{
    DrawGameTurn();
    PlayerInput(playerCreature, playerShootX, playerShootY);
    tryToShoot(playerCreature, playerShootX, playerShootY, enemyField, playerShipsLeft);
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
        if(isCheated())
        {
            playerTwoShipsLeft = 0;
            break;
        }
        Turn(playerTwoType, playerTwoShootX, playerTwoShootY, playerOneField, playerOneShipsLeft);
        if(isCheated())
        {
            playerOneShipsLeft = 0;
            break;
        }
    } while(playerTwoShipsLeft > 0 && playerOneShipsLeft > 0);
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

int main()
{
    Instructions();
    gameLoop();
    GameEnd();
    
    return 0;
}