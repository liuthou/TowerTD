//
//  ActionHelp.cpp
//  heroJump
//
//  Created by mazhai on 14-9-29.
//
//

#include "ActionHelper.h"

vector<int> ActionHelper::firest_jump;
vector<int> ActionHelper::hit_wood_jump;
vector<int> ActionHelper::getFirest_jump(){
    return firest_jump;
}
vector<int> ActionHelper::getHit_wood_jump(){
    return hit_wood_jump;
}
void ActionHelper::initJumpActions(){
    /**
     *  第一次跳跃的动作组
     */
    firest_jump.push_back(ROLE_PROPER_TO_JUMP);
    firest_jump.push_back(ROLE_JUMPING_FOR_MY_SCREEN);
    firest_jump.push_back(ROLE_JUMPING_BORN);
    firest_jump.push_back(ROLE_JUMPING_BORNNING);
    firest_jump.push_back(ROLE_BE_BORN_FOR_FIERST);
    
    
    /**
     *  碰见木头后的动作组
     */
    hit_wood_jump.push_back(ROLE_PROPER_TO_JUMP);
    hit_wood_jump.push_back(ROLE_JUMPING_FOR_MY_SCREEN);
    hit_wood_jump.push_back(ROLE_JUMPING_FOR_MY_SCREEN_END);
    hit_wood_jump.push_back(ROLE_JUMPING_FOR_BACKGROUND);
    hit_wood_jump.push_back(ROLE_JUMPING_UP_END);
    hit_wood_jump.push_back(ROLE_JUMPING_BORN);
    hit_wood_jump.push_back(ROLE_JUMPING_BORNNING);
    hit_wood_jump.push_back(ROLE_BE_BORN);
}