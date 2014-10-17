#include "BaseHeroes.h"
#include "ShareFunc.h"
#include "GameScene.h"
#include "LinearBullet.h"
#include "HeroesBullets.h"
#include "GameOverLayer.h"
#include "GameScene.h"

bool BaseHeroes::initWithSpriteFrameName(std::string fileName)
{
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}
	this->setFileName(fileName);
	this->setBulletLevel(1);
	this->setPosition(200, 320);
	return true;
}

void BaseHeroes::addFire(float t)
{
	//通过参数创建对应的子弹
	if (_isAddFire == true)
	{
		auto scene = (GameScene *)Director::getInstance()->getRunningScene();
		auto herolayer =scene->getHeroLayer();
		position = this->getPosition();

		std::string fileName;

		switch ((int)this->getBulletLevel())
		{
			case 1: fileName = "HeroBullet1.png";
				break;
			case 2: fileName = "HeroBullet2.png";
				break;
			case 3: fileName = "HeroBullet3.png";
				break;
		}

 		auto bullet = LinearBullet ::create(100,position,10 * this->getBulletLevel(), fileName,1,0);
 	    HeroesBullets::getInstance()->addBullet(bullet);
 		herolayer->addChild(bullet);
	}
	return;
}

void BaseHeroes::hurt()
{
	//this->stopAllActions();
	//this->setIsProtect(true);
	//this->setBulletLevel(_bulletLevel-1.0);
	////判断子弹等级，如果>0，就运行受伤害动画，并且子弹等级-1，如果子弹等级=0，则执行die()方法
	//if ((int)this->getBulletLevel() <= 0 )
	//{
	//	die();
	//	return;
	//}
	//
	//auto heroHurt = this->hurtAnimate();

	//auto heroFly = this->flyAnimate();

	//auto cbProtect = CallFunc::create(std::bind(&BaseHeroes::protect, this));

	//auto seq = Sequence::create(heroHurt,cbProtect, heroFly, NULL);

	//this->runAction(seq);

	
	
}

void BaseHeroes::onEnter()
{
	Sprite::onEnter();
	_isAddFire = true;
	this->schedule(schedule_selector(BaseHeroes::addFire), 0.2);
}


void BaseHeroes::protect()
{
	this->setIsProtect(false);
//	this->fly();
}

Rect BaseHeroes::getBox() const{
	Rect rect = Rect(Sprite::getBoundingBox().origin.x+25,Sprite::getBoundingBox().origin.y+75,  this->getContentSize().width - 70, this->getContentSize().height-120);
	return rect;
}




