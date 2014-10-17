#ifndef __GAMEOVERSCENE_H
#define __GAMEOVERSCENE_H
#include "cocos2d.h"

using namespace cocos2d;

class GameOverScene :public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(GameOverScene);
	void Reborn(Ref * sender);
	void Pass(Ref * sender);
	void Die(Ref * sender);
};

#endif
