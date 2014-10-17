#include "PowerfulTower.h"
#include "MainScene.h"
#include "EntityManager.h"
PowerfulTower* PowerfulTower::create(int id){
	auto tow = new PowerfulTower();
	if (tow &&tow->init(id)){
		tow->autorelease();
		return tow;
	}
	CC_SAFE_DELETE(tow);
	return nullptr;
}
void PowerfulTower::fire(Sprite* monster){
	for(int i = 0; i <=11 ;i++){
	float a = M_PI*((float)(i-6)/6);
	Vec2 m  = monster->getPosition()-this->getPosition();
	float l = sqrt(m.x*m.x+m.y*m.y);
	Vec2 p = Vec2(l*cos(a),l*sin(a));
	p = this->getPosition()+p;
	auto bu = Bullet::create(buName,p,this->getPosition(),buspeed,buattackValue,scope,atteffect);
	log("Tower fire!!(%f,%f)",monster->getPosition().x,monster->getPosition().y);
	bu->setPosition(this->getPosition());
	auto scene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	scene->getGameLayer()->addChild(bu);
	EntityManager::getInstance()->TowerBullet.pushBack(bu);
	}
}