#include "ThreeTank.h"
#include "Basebullet.h"
#include "BulletManager.h"
ThreeTank* ThreeTank::create(Vec2 position){
	auto smll = new ThreeTank();
	if(smll&&smll->init(position)){
		smll->autorelease();
		return smll;
	}
	CC_SAFE_DELETE(smll);
}
bool ThreeTank::init(Vec2 position){
	if(!EnemyTank::initWithSpriteFrameName("en3.png",THREEHP,THREESPEED,position)){
		return false;
	}
	this->score = 300;
	return true;
}
void ThreeTank::runAnimate(){

}