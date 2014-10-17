//
//  WoodSprite.cpp
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#include "WoodSprite.h"
#include "HitBodys.h"
#include "AudioUtil.h"
bool WoodSprite::init(){
    if (!UseToolsBaseSprite::initWithFile(TOOLS_WOOD_PNG)) {
        return false;
    }
    return true;
}
void WoodSprite::onEnter(){
    UseToolsBaseSprite::onEnter();
    HitBodys::getInstance() -> addUseToolsBaseSprite(this);
}
void WoodSprite::collisionRole(){
    UseToolsBaseSprite::collisionRole();
    AudioUtil::getInstance() -> playEffect("wood.wav");
    
}
std::string WoodSprite::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_TYPE;
}
void WoodSprite::changeRoleState(){
    
}
float WoodSprite::getRoleSpeedTime(){
    return WOOD_SPEED;
}

float WoodSprite::getRedians(){
    
    return WOOD_REDINS;
}
std::vector<Rect> WoodSprite::getRects(){
    rects.push_back(this -> getBoundingBox());
    return rects;
}