//
//  HelpLayer.h
//  heroJump
//
//  Created by liuly on 14-9-20.
//
//
#ifndef __STONELAYER_H_
#define __STONELAYER_H_
#include "cocos2d.h"
#include "SystemMarcoUtil.h"
using namespace cocos2d;
class StoneLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(StoneLayer);
protected:
	virtual void onEnter();
	int times;
	
};
#endif