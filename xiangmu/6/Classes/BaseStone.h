//
//  可以控制主角速度的道具
//  heroJump
//
//  Created by liuly on 14-9-20.
//
//
#ifndef __BASESTONE_H_
#define __BASESTONE_H_
#include "cocos2d.h"
#include "ToolsBaseControlUserScript.h"
#include "SystemMarcoUtil.h"
#include "ConfigUtil.h"
#define STONE_SPEED 8
using namespace cocos2d;
class BaseStone:public ToolsBaseControlUserScript
{
public:
	virtual bool init();
	virtual void changeRoleState(int times);
	virtual void changeRoleState(){}
    virtual Direction_ROLE collitionDirection(){
        return Direction_ROLE::DOWN;
    };
    virtual int controleRoleSpeed(){
        return STONE_SPEED;
    }
protected:
	int value;

};
#endif
