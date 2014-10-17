#include "Bullet.h"
#include "EntityManager.h"
#include "MainScene.h"
bool Bullet:: init(std::string fileName, Vec2 target,Vec2 position,int speed,int attackValue,int scope,attackEffect atteffect){
	if (!Sprite::initWithFile(fileName)) 
		return false;
	this->speed = speed;
	this->buName = fileName;
	this->attackValue = attackValue;
	this->target = target;
	this->cposition = position;
	this->scope = scope;
	this->attackeffect = atteffect;
	this->setIsdie(false);
	this->setPosition(position);
	return true;
}
void Bullet::onEnter(){
	Sprite::onEnter();
	auto vec = target-cposition;
	float sl = sqrt(vec.x*vec.x+vec.y*vec.y);
	float t = scope/sl;
	this->runAction(Sequence::create(MoveBy::create((float)scope/speed, Vec2(t*vec.x,t*vec.y)),
		CallFuncN::create(CC_CALLBACK_0(Bullet::remove, this)),
		NULL));
}
Bullet* Bullet::create(std::string fileName,  Vec2 target,Vec2 position,int speed,int attackValue,int scope,attackEffect atteffect){
	Bullet *bu = new Bullet();
	if (bu&&bu->init(fileName,target,position,speed,attackValue,scope,atteffect)){
		bu->autorelease();
		return bu;
	}
	CC_SAFE_DELETE(bu);
	return nullptr;
}
 void Bullet::die(float t){
	 if (this->getPositionX()< 0 || this->getPositionX()>960 ||this->getPositionY()<0 ||this->getPositionY()>960){
		 this->setIsdie(true);
		 this->remove();
	 }
 }
 void Bullet::remove(){
	 this->setIsdie(true);
	 this->removeFromParent();
 }
