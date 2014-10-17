//
//  炸弹人
//  heroJump
//
//  Created by mazhai on 14-10-8.
//
//

#ifndef __heroJump__EnemyBoomer__
#define __heroJump__EnemyBoomer__

#include <iostream>
#include <cocos2d.h>
#include "ToolsBaseControlUserScript.h"
USING_NS_CC;
class EnemyBoomer:public ToolsBaseControlUserScript{
public:
    
    
    virtual bool init();
    CREATE_FUNC(EnemyBoomer);
    virtual std::string sendCast();
    virtual Direction_ROLE collitionDirection();
    virtual void changeRoleState();
    virtual int controleRoleSpeed();
    virtual void collisionRole();
};
#endif /* defined(__heroJump__EnemyBoomer__) */
