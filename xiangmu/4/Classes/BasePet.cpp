#include "BasePet.h"
#include "ShareFunc.h"
#include "GameScene.h"
#include "SkillBullet.h"
#include "HeroesBullets.h"

bool BasePet::initWithSpriteFrameName(std::string fileName, Vec2 position)
{
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}
	isMove = true;
	offSet = Vec2(-50,80);
	this->setPosition(position+offSet);
	this->setPetAttack(1);
	this->setFileName(fileName);

	this->scheduleUpdate();
	return true;
}

void BasePet::onEnter(){
	Sprite::onEnter();
	this->runAction(petFly());
}

ActionInterval* BasePet::petFly(){
	auto ant = ShareFunc::getAct(this->getFileName(), 1, 4, .5, -1);
	return ant;
}

void BasePet::addFire(){
	//´´½¨×Óµ¯
	auto skillFire = SkillBullet::create(this->getPosition(), this->getPetAttack() * 25,"Skill4.png",2,5);
	HeroesBullets::getInstance()->addBullet(skillFire);
	auto scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	scene->getHeroLayer()->addChild(skillFire);
}

BasePet::~BasePet(){

}

void BasePet::update(float t)
{
	auto scene = (GameScene *)Director::getInstance()->getRunningScene();
	auto layer = scene->getHeroLayer();
	auto sp = layer->getChildByName("hero");
	auto position = sp->getPosition();
	petMove(position);
}
void BasePet::petMove(Vec2 position)
{
	if (isMove == true)
	{
		this->setPosition(position + offSet);
	}
}


