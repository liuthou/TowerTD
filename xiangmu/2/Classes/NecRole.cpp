#include "NecRole.h"
#include "RoleOneBullet.h"
#include "GameAttackScene.h"
#include "Bullets.h"
#include "SimpleAudioEngine.h"

NECRole * NECRole::create(std::string fileName){
	NECRole * sf = new NECRole();
	if (sf && sf->init(fileName)){
		sf->autorelease();
		sf->retain();
		return sf;
	}
	CC_SAFE_DELETE(sf);
	return nullptr;
}
bool NECRole::init(std::string fileName){
	if (!Person::init(fileName, PROJECTNAME)){
		return false;
	}
	mp = 0;
	return true;
}
void NECRole::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((960 - this->getPositionX()) / speedValue, Vec2(960 - this->getPositionX(), 0)));
}
void NECRole::fair(){
	if (this == nullptr){
		return;
	}
	auto strFlie = FileUtils::getInstance()->fullPathForFilename("SF_ATK.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(strFlie.c_str());
	RoleOneBullet *bullet = RoleOneBullet::create(Vec2(this->getPositionX(), this->getPositionY()), this->getAttackValue());
	Bullets::getInstence()->addRoleBullets(bullet);
	GameAttackScene *scene = dynamic_cast<GameAttackScene *>(Director::getInstance()->getRunningScene());
	scene->getAttackLayer()->addChild(bullet);
}