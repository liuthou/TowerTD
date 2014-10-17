#include "SkillBullet.h"
#include "ShareFunc.h"
#include "GameScene.h"
#include "LinearBullet.h"
#include "HeroesBullets.h"

SkillBullet *SkillBullet::create(Vec2 fromPosition, float attack, std::string fileName, int skillstyle, int level){
	SkillBullet *pRet = new SkillBullet();
	if (pRet && pRet->init(fromPosition, attack, fileName,skillstyle,level))
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

bool SkillBullet::init(Vec2 fromPosition, float attack, std::string fileName, int skillstyle, int level){
	
	if (!Sprite::init()){
		return false;
	}

	this->setFileName(fileName);
	this->setPoint_Skill(fromPosition);
	this->setBulletLevel(skillstyle);
	this->setAttack(attack);

	
	this->setPosition(fromPosition);

	return true;
}

void SkillBullet::onEnter(){
	BaseBullet::onEnter();

	if (this->getBulletLevel() == ray)
	{
		this->schedule(schedule_selector(SkillBullet::create_Sprite), 0.18, 3, 0);
	}
	else
	{
		this->scheduleOnce(schedule_selector(SkillBullet::create_Storage), 0.5);
	}

	this->setPosition(this->getPoint_Skill().x + 100, this->getPoint_Skill().y);
}

void SkillBullet::create_Sprite(float t){
	GameScene *scene = (GameScene *)Director::getInstance()->getRunningScene();
	HeroesLayer * hero = (HeroesLayer *)scene->getHeroLayer();
	ActionInterval * func = ShareFunc::getAct(this->getFileName(), 1, 7, 0.1, 1);
	ActionInterval * fun = ShareFunc::getAct(this->getFileName(), 8, 8, 0.1, 1);
	LinearBullet *sp = LinearBullet::create(0.5,this->getPosition(), 1000, getFileName(), 1,1);
	HeroesBullets::getInstance()->addBullet(sp);
	Spawn * sq = Spawn::create(fun, MoveBy::create(0.7, Vec2(960 - this->getPoint_Skill().x, 0)), ScaleBy::create(0.5, 2, 2, 2), NULL);
	auto cf = CallFunc::create([=]{
		sp->removeFromParentAndCleanup(true);
		sp->setDie(true);
	});
	//this->setPosition(this->getPoint_Skill().x + 150, this->getPoint_Skill().y);
	hero->addChild(sp);
	sp->runAction(Sequence::create(func,sq,cf,NULL));
}
void SkillBullet::create_Storage(float t){
	ActionInterval * func = ShareFunc::getAct(this->getFileName(), 1, 3, 0.005, 1);
	ActionInterval * fun = ShareFunc::getAct(this->getFileName(), 4, 7, 0.1, TIME * this->getBulletLevel());
	ActionInterval * funa = ShareFunc::getAct(this->getFileName(), 7, 10, 0.1, 1);
	auto cf = CallFunc::create([=]{
		this->removeFromParentAndCleanup(true);
		this->setDie(true);
	});
	this->setScale(1.7);
	this->setPosition(this->getPoint_Skill().x + 310, this->getPoint_Skill().y);
	this->runAction(Sequence::create(func,fun,funa,cf,NULL));
	this->getBoundingBox().setRect(0,0,100,40);
}

void SkillBullet::die(){
	
}