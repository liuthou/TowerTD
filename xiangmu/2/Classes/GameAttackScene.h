#ifndef __GAMEATTACKSCENE_H
#define __GAMEATTACKSCENE_H
#include "cocos2d.h"
using namespace cocos2d;
class GameAttackScene:public Scene
{
protected:
	void onEnter();
	virtual bool init();
public:
	Layer *getAttackLayer();
	CREATE_FUNC(GameAttackScene);
	Layer *getEnemyLayer();
};
#endif