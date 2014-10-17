    //
//  GameManager.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-10-4.
//
//

#include "GameManager.h"

GameManager *GameManager::_gInstance;


bool GameManager::init()
{
    _bIsPause = false;
    return true;
}
