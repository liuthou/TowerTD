//
//  Enemy1.h
//  heroJump
//
//  Created by mazhai on 14-10-7.
//
//

#ifndef __heroJump__Enemy1__
#define __heroJump__Enemy1__

#include <iostream>
#include <cocos2d.h>
#include "ToolsBaseControlUserScript.h"
USING_NS_CC;
class Enemy1:public ToolsBaseControlUserScript{
public:
    virtual bool init();
    CREATE_FUNC(Enemy1);
    virtual std::string sendCast();
    virtual Direction_ROLE collitionDirection();
    virtual void changeRoleState();
    virtual int controleRoleSpeed();
    virtual void collisionRole();
};
#endif /* defined(__heroJump__Enemy1__) */
