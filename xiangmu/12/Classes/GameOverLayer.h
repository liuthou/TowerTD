#ifndef __GAMEOVERLAYER_H
#define __GAMEOVERLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class GameOverLayer:public Layer{
public:
	virtual bool init(int type);
	static GameOverLayer*create(int type);
};
#endif