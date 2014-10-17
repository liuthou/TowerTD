#ifndef __ICESPRITE_H_
#define __ICESPRITE_H_
#include "cocos2d.h"
#include "ToolsBaseControlUserScript.h"

using namespace cocos2d;
class IceSprite:public ToolsBaseControlUserScript{
protected:
	Size vSize;
	Size pSize;
	int m_speed;
	int m_number;
public:
	CC_SYNTHESIZE(bool,isSpeedLow,IsSpeedLow);
	virtual void changeRoleState();
	virtual bool init(std::string fileName,int m_id);
	static IceSprite * create(std::string fileName,int m_id);
	virtual Direction_ROLE collitionDirection();
	virtual int controleRoleSpeed();
	virtual void collisionRole();
    virtual int attack(){
        return ATTCK;
    }
    virtual std::string sendCast();
};
#endif