#include "HeroLayer.h"
#include "AllVectors.h"
#include "GameScene.h"

bool HeroLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//可视区大小
	visSize = Director::getInstance()->getVisibleSize();


	//创建一个英雄，贴在层上
	Size vis = Size(55,85);

	sp = Hero::create(Vec2(100,78));
	sp->setName("hero");
	sp->setTag(2000);
	//创建body
	sp->setPhysicsBody(PhysicsBody::createBox(vis));
	//碰撞之后会否旋转
	sp->getPhysicsBody()->setRotationEnable(false);

	sp->getPhysicsBody()->setCollisionBitmask(17);
	//时候可穿越
	sp->getPhysicsBody()->setCategoryBitmask(4);
	//是否可碰撞
	sp->getPhysicsBody()->setContactTestBitmask(1);
	sp->getPhysicsBody()->getShape(0)->setRestitution(0);//设置没有 弹性

	this->addChild(sp);

	this->schedule(schedule_selector(HeroLayer::getFieBall));

	return true;

}

Hero *HeroLayer::getHero(){
	return sp;
}


void HeroLayer::getFieBall(float t){
	auto ev = AllVectors::getInstance()->getEnemiesVector();
	for (auto it = ev.begin(); it != ev.end(); it++){
		if ((*it)->getBoundingBox().intersectsRect(sp->getBoundingBox()) && (*it)->getM_state() >4 && (*it)->getM_state() <= 5 && (*it)->m_isFired == false){
			(*it)->setPosition(sp->getPosition());
            (*it)->m_isTaken = true;
			sp->isTaking = true;
		}
	}
}
