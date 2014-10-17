#include "EnemyWalkOne.h"
#include "SelectRole.h"
#include "SimpleAudioEngine.h"

EnemyWalkOne *EnemyWalkOne::create(std::string fileNameXml){
	EnemyWalkOne *enemy = new EnemyWalkOne();
	if(enemy && enemy->init(fileNameXml)){
		enemy->autorelease();
		return	enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
bool EnemyWalkOne::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,ENEMYWALKONEPROJECT)){
		return false;
	}
	return true;
}
void EnemyWalkOne::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
}
void EnemyWalkOne::fair(){
	auto strFlie = FileUtils::getInstance()->fullPathForFilename("COCO_ ATK.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(strFlie.c_str());
	auto roles = SelectRole::getInstence()->getRoleArmatures();
	Person *role = roles.at(0);
	for(int i = 0; i < roles.size();i++){
		auto ro = roles.at(i);
		if(ro->getPositionX() > role->getPositionX()){
			role = ro;
		}
	}
	role->setHp(this->getAttackValue());
}

