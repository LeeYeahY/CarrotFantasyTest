#include "gameManager.h"

GameManager* GameManager::gInstance;


bool GameManager::Init()
{
    myIsPause = false;
    return true;
}
