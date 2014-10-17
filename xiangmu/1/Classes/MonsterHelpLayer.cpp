//
//  MonsterHelpLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#include "MonsterHelpLayer.h"


bool MonsterHelpLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        bRet = true;
    }
    while (0);
	auto monsterHelpLayer = Sprite::createWithSpriteFrameName("help_monster.png");	
	monsterHelpLayer->setPosition(480,280);
	monsterHelpLayer->setScale(0.95f);
	addChild(monsterHelpLayer);
    return bRet;
}