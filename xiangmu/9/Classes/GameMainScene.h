#ifndef __GAMEMAINSCENE_R_
#define __GAMEMAINSCENE_R_

#include "cocos2d.h"
#include <iostream>
using namespace std;
using namespace cocos2d;

class GameMainScene : public Scene
{
public:	
	virtual bool init(std::string filename);
	static GameMainScene *create(std::string filename);
	virtual Layer *getMonsterLayer();
	virtual Layer *getHeroLayer();
	virtual Layer *getSundriesLayer();
	void addWinLayer(Ref * obj);
	GameMainScene(){}
	~GameMainScene();
};

#endif