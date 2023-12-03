#include "GameMechs.h"
#include "time.h"
#include "stdlib.h"

GameMechs::GameMechs()
{
    input = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = false;
    loseFlag = false;

    score = 0;
}

// do you need a destructor?

GameMechs::~GameMechs()
{
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = NULL;
}

void GameMechs::incrementScore(int increment)
{
    score = score + increment;
}

Food::~Food()
{
    delete[] bitVx;
    delete[] bitVy;
    delete[] bitVz;
    delete[] foodBucketX;
    delete[] foodBucketY;
}

Food::Food()
{
    foodSymbol = new char[5];
    foodBucketX = new int[5];
    foodBucketY = new int[5];

    bitVx = new int[13]();
    bitVy = new int[28]();
    bitVz = new int[5];

    //initialize bit vectors to 0

    for(int i = 0; i < 13; i++)
        bitVx[i] = 0;

    for(int i = 0; i < 28; i++) 
        bitVy[i] = 0;

    for (int i = 0; i < 5; i++)
    {
        foodBucketX[i] = 0;
        foodBucketY[i] = 0;
    }
}

void Food::generateFood(objPosArrayList* refinput)
{
    int xCount = 0;
    int yCount = 0;
    int zCount = 0;

    while (xCount < 5)
    {
        int randX = rand() % 13 + 1;

        if (bitVx[randX] == 0)
        {
            bitVx[randX] = 1;
            foodBucketX[xCount] = randX;
            xCount++;
        }
        else
        {
            continue;
        }
    }

    while (yCount < 5)
    {
        int randY = rand() % 28 + 1;
        if (bitVy[randY] == 0)
        {
            bitVy[randY] = 1;
            foodBucketY[yCount] = randY;
            yCount++;
        }
        else
        {
            continue;
        }
    }

    while (zCount < 5)
    {
        //* / $ / ! food
        char symbol;
        int randZ = rand() % 4;

        if (zCount < 3)
        {
            symbol = '*';
            foodSymbol[zCount] = symbol;
            zCount++;
        }
        else if (zCount >= 3)
        {
            if (randZ < 2)
            {
                symbol = '$';
            }
            else if (randZ >= 2)
            {
                symbol = '!';
            }

            foodSymbol[zCount] = symbol;
            zCount++;
        }
    }
    // reset the bit vector after each use

    for (int i = 0; i < 28; i++)
    {
        if (i < 13)
        {
            bitVx[i] = 0;
            bitVy[i] = 0;
        }
        else
        {
            bitVy[i] = 0;
        }
    }
}

int Food::getFoodPos(int xy, int pos)
{
    if (xy == 2)
    {
        return foodBucketX[pos];
    }
    else if (xy == 1)
    {
        return foodBucketY[pos];
    }

    return 0;
}

char Food::getfoodSymbol(int pos)
{
    return foodSymbol[pos];
}
