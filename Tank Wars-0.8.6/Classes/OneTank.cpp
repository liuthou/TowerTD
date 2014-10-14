#include "OneTank.h"
#include "Basebullet.h"
#include "BulletManager.h"
OneTank* OneTank::create(Vec2 position){
	auto smll = new OneTank();
	if(smll&&smll->init(position)){
		smll->autorelease();
		return smll;
	}
	
	CC_SAFE_DELETE(smll);
	return nullptr;
}
bool OneTank::init(Vec2 position){
	if(!EnemyTank::initWithSpriteFrameName("en1.png",ONEHP,ONESPEED,position)){
		return false;
	}
	this->score = 100;
	return true;
}
void OneTank::runAnimate(){

}