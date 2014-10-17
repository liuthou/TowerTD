#include "Common_BlueGlost.h"
#include "GameScene.h"

bool Common_BlueGlost::initWithSpriteFrameName(int sb, int level)
{
	if (!BaseCommon::initWithSpriteFrameName(kCommon_BlueGlostFileName, sb, level))
	{
		return false;
	}

	return true;
}

void Common_BlueGlost::onEnter()
{
	BaseCommon::onEnter();
}

//ËÀÍö¶¯»­
ActionInterval * Common_BlueGlost::enemyDie(){
	auto dieAni = ShareFunc::getAct("EnemyCommon_oneDie1.png", 1, 4, 0.1, 1);
	return dieAni;
}

//·ÉÐÐ¶¯»­
void Common_BlueGlost::enemyFly(){
	auto dieAni = ShareFunc::getAct("EnemyCommon_one1.png", 1, 3, 0.25, 1);
	this->runAction(dieAni);
}



Common_BlueGlost *Common_BlueGlost::create(int sb, int level){
	Common_BlueGlost *pRet = new Common_BlueGlost();
	if (pRet && pRet->initWithSpriteFrameName(sb, level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
