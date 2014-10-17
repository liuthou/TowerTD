#include "OneOxEnemy.h"
#include "SelectRole.h"
bool OneOxEnemy::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,ONEOXPROJECT)){
		return false;
	}
	return true;
}
OneOxEnemy *OneOxEnemy::create(std::string fileNameXml){
	OneOxEnemy *enemy = new OneOxEnemy();
	if(enemy && enemy->init(fileNameXml)){
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
void OneOxEnemy::fair(){
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
void OneOxEnemy::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
}