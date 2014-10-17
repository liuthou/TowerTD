//
//  JumpParameter.h
//  heroJump
//
//  Created by mazhai on 14-9-22.
//
//

#ifndef __heroJump__JumpParameter__
#define __heroJump__JumpParameter__

#include <iostream>
#include <cocos2d.h>
#include "ConfigUtil.h"

USING_NS_CC;
class JumpParameter :public Ref{
    
    
public:
    virtual bool init();
    CREATE_FUNC(JumpParameter);
    //role move direction for screen
    CC_SYNTHESIZE(Direction_ROLE, screen_direction, Screen_direction);
    //role move direction for role
    CC_SYNTHESIZE(Direction_ROLE, user_role_direction, User_role_direction);
    CC_SYNTHESIZE(bool, isMove, Move);
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(float, moveTime, MoveTime);
    CC_SYNTHESIZE(bool, screenIsStop, ScreenIsStop);
};
#endif /* defined(__heroJump__JumpParameter__) */
