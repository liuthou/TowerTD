#include "PetWolf.h"
#include "Hero_SwordPlay.h"
#include "GameScene.h"



bool PetWolf::initWithSpriteFrameName(Vec2 position)
{
	if (!BasePet::initWithSpriteFrameName("PetFly1.png", position))
	{
		return false;
	}
	isMay = true;

	bigenPoint = this->getPosition();

	return true;
}

PetWolf * PetWolf::create(Vec2 position)
{
	PetWolf * pet = new PetWolf();

	if (pet && pet->initWithSpriteFrameName(position))
	{
		pet->autorelease();
		return pet;
	}

	CC_SAFE_DELETE(pet);

	return nullptr;
}

void PetWolf::onEnter(){
	BasePet::onEnter();

	GameScene* scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	HeroesLayer* hl = scene->getHeroLayer();
	hero = (Hero_SwordPlay*)hl->getChildByName("hero");
	//hero->retain();

}

//蓄力完成动作
void PetWolf::powerOver(){

	auto petAnt = ShareFunc::getAct("PetReady1.png", 1, 16, 0.07, -1);

	petAnt->setTag(10086);

	this->stopAllActions();

	this->runAction(petAnt);

	heroPowerOver();

}

void PetWolf::heroPowerOver(){

	ActionInterval* heroAnt = ShareFunc::getAct("PetPowerOver1.png", 1, 16, 0.07, -1);

	auto sAnt = Sprite::create();

	sAnt->setName("heroAnt");

	sAnt->setPosition(hero->getContentSize().width / 2, hero->getContentSize().height / 2);

	sAnt->runAction(heroAnt);

	hero->addChild(sAnt);

}

//蓄力释放动作 
void PetWolf::powerRelease(){
	this->setIsMay(false);

	hero->removeChildByName("heroAnt");

	this->stopAllActions();
	//执行动作
	exePetPowerRelease();

	this->petFly();

}

void PetWolf::exePetPowerRelease(){

	this->runAction(serialAction());

}
//并行动作 闪烁 + 移动
Spawn* PetWolf::parallelAction(){

	auto petBlink = Blink::create(0.7, 1);

	Vec2 v = this->convertToNodeSpaceAR(hero->getPosition());

	auto petMoveBy = MoveBy::create(0.5, Vec2(v.x + hero->getContentSize().width, v.y));

	auto petBig = ScaleBy::create(0.5, 2);

	return Spawn::create(petBlink, petBig, petMoveBy, NULL);

}
//串行动作
Sequence* PetWolf::serialAction(){

	auto spawn = parallelAction();

	auto petRelease = ShareFunc::getAct("PetReleaseSkills1.png", 1, 7, 0.1, 1);

	auto petReleaseAttack = ShareFunc::getAct("PetReleaseSkills1.png", 8, 8, 3, 1);

	auto attackCF = CallFunc::create(std::bind(&PetWolf::addFire, this));

	auto petReleaseAttack_attackCF = Spawn::create(petReleaseAttack, attackCF, NULL);

	//返回动作
	auto backSeq = backBigen();

	auto cbChangeIsMay = CallFunc::create(std::bind(&PetWolf::changeIsMay, this));

	auto pf = this->petFly();

	return Sequence::create(spawn, petRelease, petReleaseAttack_attackCF, backSeq, cbChangeIsMay, pf, NULL);

}

Spawn* PetWolf::backBigen(){

	auto petSmall = ScaleBy::create(0.5, 0.5);

	auto backBlink = Blink::create(1, 0.2);

	auto petMoveTo = MoveTo::create(0.2, bigenPoint);

	auto cbChangeIsMove = CallFunc::create(std::bind(&PetWolf::changeIsMove, this));

	auto spawn = Spawn::create(petSmall, backBlink, petMoveTo, cbChangeIsMove, NULL);

	return spawn;
}

PetWolf::~PetWolf(){
	//hero->release();
}

void PetWolf::changeIsMove()
{
	this->setIsMove(true);
}

void PetWolf::changeIsMay()
{
	this->setIsMay(true);
}

void PetWolf::stopPowerOver()
{
	auto scene = (GameScene *)Director::getInstance()->getRunningScene();
	auto ani = (Animate *) this->getActionByTag(10086);
	auto ant = hero->getChildByName("heroAnt");
	hero->removeChild(ant, true);
	this->stopAction(ani);
	this->runAction(petFly());
}

void PetWolf::die()
{
	this->stopAllActions();
	//运行死亡动画
	auto dieAni = ShareFunc::getAct("PetDie1.png",1,10,0.2,1);
	auto cbRemovePet = CallFunc::create(std::bind(&PetWolf::removePet,this));
	this->runAction(Sequence::create(dieAni,cbRemovePet,NULL));
}

void PetWolf::removePet()
{
	this->removeFromParentAndCleanup(true);
}