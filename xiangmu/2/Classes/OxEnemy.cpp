#include "OxEnemy.h"
#include "SelectRole.h"
bool OxEnemy::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,OXPROJECT)){
		return false;
	}
	return true;
}
OxEnemy *OxEnemy::create(std::string fileNameXml){
	OxEnemy *enemy = new OxEnemy();
	if(enemy && enemy->init(fileNameXml)){
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
void OxEnemy::fair(){
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
void OxEnemy::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
}