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

bool isCheated()
{
    return cheatCode == "cheat";
}

void Instructions()
{
    system("clr");
    cout << "This is Sea Battle. there are 2 axis: x & y." << endl;
    cout << "x - horizontal, y - vertical." << endl;
    cout << "Write first coordinate x from 1 to 9, then press enter and write y." << endl;
    cout << "# - you hit ship, ^ - miss." << endl;
    cout << "Good luck!" << endl;;
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
            if (field[j][i] != '@')
            {
                field[j][i] = 'Y';
            }
        }
    }
}

void SetPlayerCarrier(char (&field)[width][height])
{

}

void SetPlayerCruiser(char (&field)[width][height])
{

}

void SetPlayerBattleShip(char (&field)[width][height])
{

}

void SetPlayerDestroyer(char (&field)[width][height])
{

}

void SetPlayerShips(char (&field)[width][height])
{
    SetPlayerCarrier(field);
    SetPlayerCruiser(field);
    SetPlayerBattleShip(field);
    SetPlayerDestroyer(field);
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
                field[j][i];
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
    }
    else if (field[x][y] == 'Y')
    {
        field[x][y] = '^';
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
    DrawField(playerOneField, playerOneMode);
    cout << endl;
    DrawField(playerTwoField, playerTwoMode);
}

void playerInputAsker()
{
    while (true)
    {
        if (enteredCorrectType(playerOneType) && enteredCorrectType(playerTwoType))
        {
            system(("clr"));
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
    Shoot(playerShootX, playerShootY, enemyField, playerShipsLeft);
    cout << "Press enter to continue...";
    cin >> cheatCode;
    system("clr");
}

void gameLoop()
{
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