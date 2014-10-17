#include "Elite_Shadow.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool Elite_Shadow::initWithSpriteFrameName(int sb, int level)
{
	if (!BaseElite::initWithSpriteFrameName(kElite_ShadowFileName,sb,level))
	{
		return false;
	}
	enemyType = true;
	firstCollide = true;
	isProtect = false;
	return true;
}

void Elite_Shadow::onEnter()
{
	BaseElite::onEnter();
}

void Elite_Shadow::hurt(int attack)
{
	SimpleAudioEngine::getInstance()->playEffect("enemyHurtMusic.wav");
	if (firstCollide == true)
	{
		elude();
		return;
	}
	this->setHp(this->getHp() - (float)attack);
	//受伤动画
	enemyHurt();
	if (this->getHp() <= 0)
	{
		this->die();
	}
}

void Elite_Shadow::elude()
{
	firstCollide = false;
	isProtect = true;
	auto blink = CCBlink::create(1, 1);
	auto moveBy1 = MoveBy::create(1, Vec2(0, randomNumber));
	auto spawn = Spawn::create(blink, moveBy1, NULL);
	auto eliteCB1 = CallFunc::create(std::bind(&Elite_Shadow::eliteCB,this));
	auto moveby2 = MoveBy::create(1400 / this->getEnemySpeed(), Vec2(-960, 0));
	auto eliteCB2 = CallFunc::create(std::bind(&BaseElite::removeEnemyNode, this));
	this->runAction(Sequence::create(spawn,eliteCB1,moveby2,eliteCB2,NULL));
}

Rect Elite_Shadow::getBoundingBox(int t) const
{
	Rect rect = Rect(Sprite::getBoundingBox().origin.x - 200, Sprite::getBoundingBox().origin.y, 400, this->getContentSize().height);
	return rect;
}

Rect Elite_Shadow::getBoundingBox() const
{
	Rect rect = Rect(Sprite::getBoundingBox().origin.x,Sprite::getBoundingBox().origin.y,this->getContentSize().width,this->getContentSize().height);
	return rect;
}

//死亡动画
ActionInterval * Elite_Shadow::enemyDie(){
	auto dieAni = ShareFunc::getAct("SmartEnemyDie1.png", 1, 4, 0.1, 1);

	return dieAni;
	
}

//飞行动画
void Elite_Shadow::enemyFly(){
	auto dieAni = ShareFunc::getAct("EnemyCommon_two1.png", 1, 4, 0.25, -1);
	this->runAction(dieAni);
}


Elite_Shadow *Elite_Shadow::create(int sb, int level){
	Elite_Shadow *pRet = new Elite_Shadow();
	if (pRet && pRet->initWithSpriteFrameName(sb, level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void Elite_Shadow::eliteCB()
{
	isProtect = false;
}