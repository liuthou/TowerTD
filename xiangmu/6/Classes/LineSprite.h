#ifndef __LINESPRITE_H_
#define __LINESPRITE_H_
#include "cocos2d.h"
#include "ToolsBaseControlUserScript.h"
using namespace cocos2d;
class LineSprite:public ToolsBaseControlUserScript{
public:
	virtual bool init(std::string fileName);
	static LineSprite * create(std::string fileName);
	virtual Direction_ROLE collitionDirection();
	virtual int controleRoleSpeed();
	virtual void collisionRole();
	virtual void changeRoleState();
    virtual std::string sendCast();
    virtual int attack(){
        return ATTCK;
    }
};
#endif