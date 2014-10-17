#include "BaseBullet.h"
bool BaseBullet::init(std::string fileName,Vec2 positionBegin,int attack,int speed){
	if(!Sprite::initWithFile(fileName)){
		return false;
	}
	isDie = false;
	this->attack = attack;
	this->speed = speed;
	this->setPosition(positionBegin);
	move();
	return true;
}
int BaseBullet::getAttack(){
	return this->attack;
}
void BaseBullet::deleteMy(){
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}
void BaseBullet::setIsDie(){
	this->isDie = true;
}
bool BaseBullet::getIsDie(){
	return this->isDie;
}