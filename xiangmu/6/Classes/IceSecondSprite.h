#ifndef __ICESECONDSPRITE_H_
#define __ICESECONDSPRITE_H_
#include "IceSecondSprite.h"
#include "ToolsBaseControlUserScript.h"
using namespace cocos2d;
class IceSecondSprite:public ToolsBaseControlUserScript{
public:
	 virtual void changeRoleState();
	virtual bool init(std::string fileName);
	static IceSecondSprite * create(std::string fileName);
	virtual Direction_ROLE collitionDirection();
	virtual int controleRoleSpeed();
	virtual void collisionRole();
    void removeIce(float ft);
}; 
#endif 