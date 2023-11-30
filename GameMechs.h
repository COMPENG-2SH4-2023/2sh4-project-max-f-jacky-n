#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

private:
    char input;
    bool exitFlag;
    bool loseFlag;
    int score;

    int boardSizeX;
    int boardSizeY;

public:
    GameMechs();
    ~GameMechs();
    GameMechs(int boardX, int boardY);

    bool getExitFlagStatus();
    bool getLoseFlagStatus();
    void setLoseTrue();
    void setExitTrue();

    char getInput();
    void setInput(char this_input);
    void clearInput();

    int getBoardSizeX();
    int getBoardSizeY();
    int getScore();

    void incrementScore(int increment);
};

class Food
{

private:
    int *foodBucketY;
    int *foodBucketX;

    char *foodSymbol; // reg = *, super = $/!;

    int *bitVx;
    int *bitVy;
    int *bitVz;

public:
    Food();
    ~Food();

    void generateFood();
    int getFoodPos(int xy, int pos);
    char getfoodSymbol(int pos);
};

#endif