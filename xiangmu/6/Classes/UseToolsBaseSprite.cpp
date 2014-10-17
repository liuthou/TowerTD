//
//  UseToolsBaseSprite.cpp
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#include "UseToolsBaseSprite.h"
#include "HitBodys.h"
bool UseToolsBaseSprite::init(){
    if (!BodyAbstract::init()) {
        return false;
    }
    
    isDie = false;
    return true;
}

void UseToolsBaseSprite::collisionRole(){
   
    
}
std::string UseToolsBaseSprite::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_TYPE;
}

void UseToolsBaseSprite::die(){
    isDie = true;
    this -> removeFromParentAndCleanup(true);
    HitBodys::getInstance() -> deleteToolsBaseSprite(this);
}
