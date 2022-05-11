#pragma once

#include <iostream>

using namespace std;

#ifndef GAME_H
#define GAME_H

namespace functions
{
    class Game
    {
    public:
        void Instructions();
        void gameLoop();
        void GameEnd();
    };
}

namespace constants
{
    class consts
    {
    public:
        const int width = 9;
        const int height = 9;

        const int carrierLength = 4;
        const int cruiserLength = 3;
        const int battleShipLength = 2;
        const int miniShipLength = 1;
    };
}

namespace variables
{
    class vars
    {
    public:
        string playerOneType; // human or bot
        string playerTwoType;
    };
}

#endif