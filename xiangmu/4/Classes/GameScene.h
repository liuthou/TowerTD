#pragma once
#include "Conf.h"
#include "HeroesLayer.h"
#include "EnemyLayer.h"
#include "ScoreLayer.h"
class GameScene :public Scene
{
protected:
	virtual void onEnter();
public:
	virtual bool init();
	CREATE_FUNC(GameScene);

	//获取主机层
	HeroesLayer* getHeroLayer();
	//获取敌机层
	EnemyLayer* getEnemyLayer();
	//获取碰撞层
	Layer* getColideLayer();
	//获取分数层
	ScoreLayer *getScoreLayer();

};