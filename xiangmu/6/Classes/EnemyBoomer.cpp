//
//  EnemyBoomer.cpp
//  heroJump
//
//  Created by mazhai on 14-10-8.
//
//

#include "EnemyBoomer.h"
bool EnemyBoomer::init(){
    
    if (!ToolsBaseControlUserScript::init()) {
        
        return false;
    }
    
    initWithSpriteFrameName("enmy4_pepole1.png");
    return true;
}
std::string EnemyBoomer::sendCast(){
    return "";
}
Direction_ROLE EnemyBoomer::collitionDirection(){
    return Direction_ROLE::UP;
}
void EnemyBoomer::changeRoleState(){
    
}
int EnemyBoomer::controleRoleSpeed(){
    return -1;
}
void EnemyBoomer::collisionRole(){
    
}
