//
//  ColoudSprite.h
//  herojump
//
//  Created by lanou3g on 14-10-8.
//
//

#ifndef __herojump__ColoudSprite__
#define __herojump__ColoudSprite__
#include "cocos2d.h"
#include "ToolsBaseControlUserScript.h"
using namespace cocos2d;
class ColoudSprite:public ToolsBaseControlUserScript{
protected:
	Size vSize;
	Size pSize;
	int m_speed;
	int m_number;
    Sprite * cloud;
public:
	CC_SYNTHESIZE(bool,isSpeedLow,IsSpeedLow);
	virtual void changeRoleState();
	virtual bool init(std::string fileName,int m_id);
	static ColoudSprite * create(std::string fileName,int m_id);
	virtual Direction_ROLE collitionDirection();
	virtual int controleRoleSpeed();
	virtual void collisionRole();
    virtual std::string sendCast();
    virtual int attack(){
        return -ATTCK;
    }
};
#endif /* defined(__herojump__ColoudSprite__) */
