#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 850000

// Class Pointer //

GameMechs *gameM = new GameMechs(30, 15);
Food *food = new Food();

//

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (gameM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    srand(time(NULL));
}

void GetInput(void)
{
    MacUILib_hasChar();

    if (MacUILib_hasChar() != 0)
    {
        gameM->setInput(MacUILib_getChar());
    }
    else
    {
        gameM->clearInput();
    }
}

void RunLogic(void)
{

    food->generateFood();
    if (gameM->getInput() == 32)
    {
        gameM->setExitTrue();
    }

    if (gameM->getScore() == 30)
    {
        gameM->setLoseTrue();
        gameM->setExitTrue();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    // Game Board x = 30, y = 15;

    for (int row = 0; row < gameM->getBoardSizeY(); row++)
    {

        for (int col = 0; col < gameM->getBoardSizeX(); col++)
        {
            if (col == 29)
            {
                MacUILib_printf("#\n");
            }
            else if (row == 0 || row == 14)
            {
                MacUILib_printf("#");
            }
            else if (col == 0)
            {
                MacUILib_printf("#");
            }
            else if (row == food->getFoodPos(1, 0) && col == food->getFoodPos(2, 0))
            {
                MacUILib_printf("%c", food->getfoodSymbol(0));
            }
            else if (row == food->getFoodPos(1, 1) && col == food->getFoodPos(2, 1))
            {
                MacUILib_printf("%c", food->getfoodSymbol(1));
            }
            else if (row == food->getFoodPos(1, 2) && col == food->getFoodPos(2, 2))
            {
                MacUILib_printf("%c", food->getfoodSymbol(2));
            }
            else if (row == food->getFoodPos(1, 3) && col == food->getFoodPos(2, 3))
            {
                MacUILib_printf("%c", food->getfoodSymbol(3));
            }
            else if (row == food->getFoodPos(1, 4) && col == food->getFoodPos(2, 4))
            {
                MacUILib_printf("%c", food->getfoodSymbol(4));
            }
            else if (col > 0 && col < 29)
            {
                MacUILib_printf(" ");
            }
        }
    }

    // Score
    MacUILib_printf("Score: %d\n", gameM->getScore());

    MacUILib_printf("Input: %c", gameM->getInput());
    // End Messages

    if (gameM->getLoseFlagStatus() == true)
    {
        MacUILib_printf(
            "\n\nYou ran into yourself.\nYou lose!");
    }
    else
    {
        if (gameM->getExitFlagStatus() == true)
        {
            MacUILib_printf("\nGame Stopped.");
        }
    }

    // debugging
    for (int i = 0; i < 5; i++)
    {
        MacUILib_printf("\nFood Item %d: [%d,%d]", i + 1, food->getFoodPos(1, i), food->getFoodPos(2, i));
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{

    MacUILib_uninit();
    delete food;
    delete gameM;
}
