#ifndef __ACTIONSFACTORY__H
#define __ACTIONSFACTORY__H
#include "cocos2d.h"
USING_NS_CC;

class ActionsFactory
{
public:
	static  Animate * createAction(std::string fileNameStr, int pictureNum, float delayPerUnit, int loops);

};

#endif