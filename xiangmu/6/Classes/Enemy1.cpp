//
//  Enemy1.cpp
//  heroJump
//
//  Created by mazhai on 14-10-7.
//
//

#include "Enemy1.h"
bool Enemy1::init(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enmy/enmy.plist");
    if (!ToolsBaseControlUserScript::init()) {
        
        return false;
    }
    
    initWithFile("enmy1_pepole_01.png");
    return true;
}
std::string Enemy1::sendCast(){
    return "";
}
Direction_ROLE Enemy1::collitionDirection(){
    return Direction_ROLE::UP;
}
void Enemy1::changeRoleState(){
    
}
int Enemy1::controleRoleSpeed(){
    return -1;
}
void Enemy1::collisionRole(){
    
}
