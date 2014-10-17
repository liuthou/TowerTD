#ifndef __ENEMYLAYER_H
#define __ENEMYLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
#include "EnemyOne.h"
#include "EnemyWalkOne.h"
class EnemyLayer:public Layer
{
protected:
	EnemyWalkOne *enemyWalk;
	EnemyOne *enemyFly;
	virtual bool init();
	std::string enemyXml;
public:
	CREATE_FUNC(EnemyLayer);
	std::string ReadEnemyXml();
};
#endif