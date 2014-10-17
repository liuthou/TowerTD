#ifndef _ENEMYAILAYER_H
#define _ENEMYAILAYER_H
#include "cocos2d.h"
using namespace cocos2d;

class EnemyAILayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(EnemyAILayer);
	void AIOne(float t);
	void AITwo(float t);
	void AIThree(float t);
	void AIFour(float t);
	void AIFive(float t);
	void AISix(float t);
	void AISeven(float t);
	void AIEight(float t);
	void onEnter();

};
#endif