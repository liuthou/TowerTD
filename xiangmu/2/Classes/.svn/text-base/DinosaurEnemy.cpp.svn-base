#include "DinosaurEnemy.h"
#include "GameAttackScene.h"
#include "DinosaurBullet.h"
#include "Bullets.h"
bool DinosaurEnemy::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,DINOSAURPROJECTNAME)){
		return false;
	}
	return true;
}
DinosaurEnemy *DinosaurEnemy::create(std::string fileNameXml){
	DinosaurEnemy *enemy = new DinosaurEnemy();
	if(enemy && enemy->init(fileNameXml)){
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
void DinosaurEnemy::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
}
void DinosaurEnemy::fair(){
	DinosaurBullet *bullet = DinosaurBullet::create(this->getPosition(),this->getAttackValue());
	GameAttackScene *scene = dynamic_cast<GameAttackScene *>(Director::getInstance()->getRunningScene());
	Bullets::getInstence()->addEnemyBullets(bullet);
	scene->getAttackLayer()->addChild(bullet);
}