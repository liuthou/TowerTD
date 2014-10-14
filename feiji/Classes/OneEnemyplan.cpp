#include "OneEnemyplan.h"
bool OneEnemyplan::init(int Speed){
	if(!BaseEnemyplan::initWithSpriteFrameName("enemy1_fly_1.png",Speed,ONEHP)){
		return false;
	}
	return true;
}
OneEnemyplan* OneEnemyplan::create(int Speed){
	auto smll = new OneEnemyplan();
	if(smll&&smll->init(Speed)){
		smll->autorelease();
		return smll;
	}
	CC_SAFE_DELETE(smll);
}