#ifndef  __ENTERLATER_H
#define  __ENTERLATER_H

#include "cocos2d.h"
USING_NS_CC;

class EnterLayer : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(EnterLayer);
};

#endif