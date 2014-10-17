#include "CowEnemy.h"
#include "SelectRole.h"
bool CowEnemy::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,COWPROJECTNAME)){
		return false;
	}
	return true;
}
CowEnemy *CowEnemy::create(std::string fileNameXml){
	CowEnemy *enemy = new CowEnemy();
	if(enemy && enemy->init(fileNameXml)){
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
void CowEnemy::fair(){
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
void CowEnemy::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
}