//#include "NormalTower.h"
//#include "Bullet.h"
//#include "MainScene.h"
//#include "NormalTower.h"
//bool NormalTower::init(std::string fileName){
//	if(!Tower::init(fileName,HP,ATTACKVALUE,SCOPE))return false;
//
//	auto scene =dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
//	scene->getGameLayer()->addChild(this);
//	return true;
//}
//NormalTower* NormalTower::create(std::string fileName){
//	NormalTower * normal = new NormalTower();
//	if (normal && normal->init(fileName)){
//		normal->autorelease();
//		return normal;
//	}
//	CC_SAFE_DELETE(normal);
//	return nullptr;
//}
/*
void NormalTower:: fire(Vec2 target){
	Bullet::create("jiantou.png",target,this->getPosition());
}*/