#include "ThreeEnemylayer.h"
bool ThreeEnemyplan::init(int Speed){
	if(!BaseEnemyplan::initWithSpriteFrameName("enemy2_fly_2.png",Speed,THREEHP)){
		return false;
	}
	return true;
}
ThreeEnemyplan* ThreeEnemyplan::create(int Speed){
	auto smll = new ThreeEnemyplan();
	if(smll&&smll->init(Speed)){
		smll->autorelease();
		return smll;
	}
	CC_SAFE_DELETE(smll);
}