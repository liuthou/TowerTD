//
//  HelpLayer.h
//  heroJump
//
//  Created by liuly on 14-9-20.
//
//
#ifndef __BULESTONE_H_
#define __BULESTONE_H_
#include "cocos2d.h"
#include "BaseStone.h"
using namespace cocos2d;
class BuleStone:public BaseStone
{
public:
	virtual bool init();
	static BuleStone* create(std::string fileName) ;
    virtual std::string sendCast();
protected:
};
#endif