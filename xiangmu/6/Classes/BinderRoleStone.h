#ifndef __BINDERROLESTONE_H_
#define __BINDERROLESTONE_H_
#include "cocos2d.h"
#include "ToolsBaseControlUserScript.h"
#include "ConfigUtil.h"
#define  STONE_SPEED 0;
using namespace cocos2d;
class BinderRoleStone:public ToolsBaseControlUserScript
{
public:
	virtual bool init();
	static BinderRoleStone * create();
	virtual Direction_ROLE collitionDirection();
	virtual void changeRoleState();
	virtual int controleRoleSpeed();
	virtual void collisionRole();
    virtual std::string sendCast();
    virtual int attack(){
        return ATTCK;
    }
    
private:
};
#endif