#include "BaseBullet.h"

bool BaseBullet::init(float speed, Vec2 fromPosition, float attack, std::string fileName,int bulletSpecies,int pro){
	
	if (!Sprite::initWithSpriteFrameName(fileName)){
		return false;
	}
	this->setPosition(fromPosition);
	this->setSpeed(speed);
	this->setAttack(attack);
	this->propert = pro;

	return true;
}

void BaseBullet::die(){
	if (propert != 1)
	{
		this->setDie(true);
		this->removeFromParentAndCleanup(true);
	}
}

void BaseBullet::onEnter(){
	Sprite::onEnter();
}
