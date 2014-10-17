#include "SnakeEnemy.h"
#include "SelectRole.h"
bool SnakeEnemy::init(std::string fileNameXml){
	if(!Person::init(fileNameXml,SNAKEPROJECTNAME)){
		return false;
	}
	return true;
}
SnakeEnemy *SnakeEnemy::create(std::string fileName){
	SnakeEnemy *enemy = new SnakeEnemy();
	if(enemy && enemy->init(fileName)){
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}
void SnakeEnemy::fair(){
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
void SnakeEnemy::move(){
	this->getAnimation()->play(animationMove);
	this->runAction(MoveBy::create((this->getPositionX()/speedValue),Vec2(-this->getPositionX(),0)));
}