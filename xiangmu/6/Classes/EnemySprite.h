#ifndef __ENEMYSPRITE_H_
#define __ENEMYSPRITE_H_
#include "cocos2d.h"
using namespace cocos2d;
#include "ToolsBaseControlUserScript.h"
class EnemySprite:public ToolsBaseControlUserScript{
protected:
	Size vSize;
	Size pSize;
	int m_speed;
public:
	virtual void changeRoleState();
    virtual bool init();
	static EnemySprite * create(std::string fileName);
	virtual Direction_ROLE collitionDirection();
	virtual int controleRoleSpeed();
	virtual void collisionRole();
    virtual std::string sendCast();
    virtual int attack(){
        return ATTCK;
    }
};
#endif