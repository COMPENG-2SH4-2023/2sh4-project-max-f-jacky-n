#include "Player.h"

Player::Player(GameMechs *thisGMRe, Food *thisFoodRe)
{
    mainGameMechsRef = thisGMRe;
    foodRef = thisFoodRe;

    myDir = STOP;

    objPos tempPos((mainGameMechsRef->getBoardSizeX()) / 2, (mainGameMechsRef->getBoardSizeY()) / 2, '@');

    /* objPos tempPos;
    tempPos.setObjPos((mainGameMechsRef -> getBoardSizeX()) / 2, (mainGameMechsRef -> getBoardSizeY()) / 2, '@');
 */

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    switch ((char)mainGameMechsRef->getInput())
    {

    case 'w':
        if (myDir != UP && myDir != DOWN)
            myDir = UP;
        break;

    case 'a':
        if (myDir != LEFT && myDir != RIGHT)
            myDir = LEFT;
        break;

    case 's':
        if (myDir != UP && myDir != DOWN)
            myDir = DOWN;
        break;

    case 'd':
        if (myDir != LEFT && myDir != RIGHT)
            myDir = RIGHT;
        break;

    default:
        break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos tempPos;

    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    switch (myDir)
    {

    case UP:
        currentHead.y--;
        break;

    case LEFT:
        currentHead.x--;
        break;

    case DOWN:
        currentHead.y %= (mainGameMechsRef->getBoardSizeY() - 2);
        currentHead.y++;

        break;

    case RIGHT:
        currentHead.x %= (mainGameMechsRef->getBoardSizeX() - 2);
        currentHead.x++;
        break;

    case STOP:
    default:
        break;
    }

    if (currentHead.y == 0)
        currentHead.y = ((mainGameMechsRef->getBoardSizeY())) - 1;

    if (currentHead.x == 0)
        currentHead.x = ((mainGameMechsRef->getBoardSizeX())) - 1;

    for (int i = 1; i < playerPosList -> getSize(); i++) {
            playerPosList -> getElement(tempPos, i);
            if(currentHead.x == tempPos.x && currentHead.y == tempPos.y) {
                mainGameMechsRef -> setLoseTrue();
            }

        }

    for (int i = 0; i < 5; i++)
    {
        if (currentHead.x == foodRef->getFoodPosX(i) && currentHead.y == foodRef->getFoodPosY(i))
        {
            playerPosList->insertTail(currentHead);
            mainGameMechsRef->incrementScore(1);
            foodRef->generateFood(getPlayerPos());
            break;
        }
    }

    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}
