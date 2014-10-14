#ifndef __GAMEOVERLAYER_H
#define __GAMEOVERLAYER_H
#include "cocos2d.h"
USING_NS_CC;
class GameOverLayer :public Layer{
public:
	virtual bool init();

	CREATE_FUNC(GameOverLayer);

	
};
#endif