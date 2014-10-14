#include "TwoEnemyplan.h"
bool TwoEnemyplan::init(int Speed){
	if(!BaseEnemyplan::initWithSpriteFrameName("enemy3_fly_1.png",Speed,TWOHP)){
		return false;
	}
	return true;
}
TwoEnemyplan* TwoEnemyplan::create(int Speed){
	auto smll = new TwoEnemyplan();
	if(smll&&smll->init(Speed)){
		smll->autorelease();
		return smll;
	}
	CC_SAFE_DELETE(smll);
}