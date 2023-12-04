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
    delete[] foodBucket;
    delete[] snakePos;
}

Food::Food()
{
    snakePos = new objPos();
    foodBucket = new objPos[5];

    for (int i = 0; i < 5; i++)
    {
        foodBucket[i].x = 0;
        foodBucket[i].y = 0;
        foodBucket[i].symbol = '*';
    }
}

void Food::generateFood(objPosArrayList *refinput)
{
    bool clear;
    int xCount = 0;
    int yCount = 0;
    int zCount = 0;
    int bitVy[28];
    int bitVx[13];

    for (int i = 0; i < 28; i++)
        bitVx[i] = 0;

    for (int i = 0; i < 13; i++)
        bitVy[i] = 0;

    while (xCount < 5)
    {
        int randX = rand() % 28 + 1;
        clear = false;
        for (int i = 0; i < refinput->getSize(); i++)
        {
            refinput->getElement(*snakePos, i);
            if (randX == snakePos->x)
            {
                clear = false;
                continue;
            }
            else
            {
                clear = true;
            }
        }

        if (clear && bitVx[randX] == 0)
        {
            bitVx[randX] = 1;
            foodBucket[xCount].x = randX;
            xCount++;
        }
    }

    while (yCount < 5)
    {
        int randY = rand() % 13 + 1;
        clear = false;
        for (int i = 0; i < refinput->getSize(); i++)
        {
            refinput->getElement(*snakePos, i);
            if (randY == snakePos->y)
            {
                clear = false;
                continue;
            }
            else
            {
                clear = true;
            }
        }

        if (clear && bitVy[randY] == 0)
        {
            bitVy[randY] = 1;
            foodBucket[yCount].y = randY;
            yCount++;
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
            foodBucket[zCount].symbol = symbol;
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

            foodBucket[zCount].symbol = symbol;
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
            bitVx[i] = 0;
        }
    }
}

int Food::getFoodPosX(int pos)
{
    return foodBucket[pos].x;
}
int Food::getFoodPosY(int pos)
{
    return foodBucket[pos].y;
}
char Food::getfoodSymbol(int pos)
{
    return foodBucket[pos].symbol;
}
