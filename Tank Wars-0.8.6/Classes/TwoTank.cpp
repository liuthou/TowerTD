#include "TwoTank.h"
#include "Basebullet.h"
#include "BulletManager.h"
TwoTank* TwoTank::create(Vec2 position){
	auto smll = new TwoTank();
	if(smll&&smll->init(position)){
		smll->autorelease();
		return smll;
	}
	CC_SAFE_DELETE(smll);
}
bool TwoTank::init(Vec2 position){
	if(!EnemyTank::initWithSpriteFrameName("en1r.png",TWOHP,TWOSPEED,position)){
		return false;
	}
	this->score = 200;
	return true;
}
void TwoTank::runAnimate(){

}