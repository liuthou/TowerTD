#include "EnemyOne.h"
#include "EnemyOneBullet.h"
#include "GameAttackScene.h"
#include "Bullets.h"
#include "SimpleAudioEngine.h"

bool EnemyOne::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,FLYPROJECTNAME)){
		return false;
	}
	return true;
}
EnemyOne *EnemyOne::create(std::string fileNameXml){
	EnemyOne *enemy = new EnemyOne();
	if(enemy && enemy->init(fileNameXml)){
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
void EnemyOne::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
	
}
void EnemyOne::fair(){
	auto strFlie = FileUtils::getInstance()->fullPathForFilename("COCO_ ATK.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(strFlie.c_str());
	EnemyOneBullet *bullet = EnemyOneBullet::create(this->getPosition(),this->getAttackValue());
	GameAttackScene *scene = dynamic_cast<GameAttackScene *>(Director::getInstance()->getRunningScene());
	Bullets::getInstence()->addEnemyBullets(bullet);
	scene->getAttackLayer()->addChild(bullet);
}