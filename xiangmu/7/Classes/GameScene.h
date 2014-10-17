#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"
#include "HeroLayer.h"
#include "EnemyLayer.h"
#include "MapLayer.h"
#include "ScoreLayer.h"
#include "SkillLayer.h"
#include "ControlLayer.h"


using namespace cocos2d;
using namespace std;
class GameScene :public Scene{

public:
	
	virtual bool init();

	CREATE_FUNC(GameScene);

	virtual HeroLayer *getHeroLayer();
	virtual EnemyLayer * getEnemyLayer();
	virtual MapLayer *getMapLayer();

	virtual ScoreLayer *getScoreLayer();
	virtual SkillLayer *getSkillLayer();
	virtual ControlLayer *getControlLayer();


	void onEnter();
};


#endif