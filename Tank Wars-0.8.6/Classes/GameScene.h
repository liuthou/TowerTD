#ifndef __GAMESCENE_H
#define __GAMESCENE_H
#include "cocos2d.h"
using namespace cocos2d;
class GameScene:public Scene{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
	Layer* getTanklayer();
	Layer* getMaplayer();
	Layer* getenemlayer();
};
#endif