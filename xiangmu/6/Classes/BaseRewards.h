//
//BaseReward.cpp
//
//
//create by lius 9ÔÂ24ÈÕ
//
//
#ifndef __BASEREWARDS_H_
#define __BASEREWARDS_H_
#include "cocos2d.h"
#include "ToolsBaseScript.h"
#include "ConfigUtil.h"
#include "ToolsBaseControlUserScript.h"
using namespace cocos2d;
class BaseRewards:public ToolsBaseControlUserScript{
protected:
	Size vSize;
	Size pSize;
	int m_id_x;
	int m_id_y;
	float x;
	float y;
public:
	CC_SYNTHESIZE_READONLY(bool,isMove,IsMove);
	void addMagnetAnimation();
	virtual void changeRoleState();
	CC_SYNTHESIZE_READONLY(int, score, Score);
	CC_SYNTHESIZE_READONLY(int, coin, Coin);
	virtual bool initWithFile(std::string fileName);
	virtual void removeDieSprite();
    virtual Direction_ROLE collitionDirection();
    virtual int controleRoleSpeed();
    virtual void collisionRole();
	virtual void onEnter();
    virtual std::string sendCast();
};
#endif