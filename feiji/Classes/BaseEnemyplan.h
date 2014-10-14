#ifndef __BASEENEMYPLAN_H
#define __BASEENEMYPLAN_H
#include "cocos2d.h"
using namespace cocos2d;
class BaseEnemyplan:public Sprite{
protected:
	int Hp;
	int Speed;
	virtual void die(std::vector<std::string>fileNames);
public:
	virtual bool initWithSpriteFrameName(std::string filename,int Speed,int Hp);
	virtual void remove();
};
#endif