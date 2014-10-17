#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene;
class Hero_SwordPlay;
class ShareFunc
{
public:
	static ActionInterval * getAct(std::string fileName, int begin, int count, float time, int loop);
	static bool isFileName(std::string fileName);
	static GameScene* getGameScene();
};



