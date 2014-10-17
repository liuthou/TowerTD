#include "MonsterBase.h"
#include "Monsters.h"
#include "GameMainScene.h"
#include "MonsterLayer.h"
#include "HeroLayer.h"
#include "MonsterFSM.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool MonsterBase::initWithSpriteFrameName(std::string monsterName, int hp, int attack, int id, float speed, int exp)
{
	if (!Sprite::initWithSpriteFrameName(monsterName))
	{
	     return false;
	}
	_id = id;	
	_hpValue =hp;
	_attackValue = attack;
	_expValue = exp;
	_speedValue = speed;
	_isOnePartol = true;
	allHp = hp;
	counts = 0;
	curState = NULLPTR;
	beforeSendState = NULLPTR;
	//初始化动画类
	_animateClass = AnimateClass::create();
	//可见尺寸
	Vec2 vSize = Director::getInstance()->getVisibleSize();

	_monsterAttackState = false;
	_isRun = true;
	this->setMonsterDie(false);
	auto scene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = scene->getHeroLayer();
	hero = (Sprite *)(heroLayer->getChildByTag(100));
	auto layer = scene->getMonsterLayer();
    layer->addChild(this);
	monsterHpSprite();
	schedule(schedule_selector(MonsterBase::update),0);
	monsterRunAnimation();
	return true;
}

void MonsterBase::update(float t)
{
	Vec2 monsterWordPoint = this->getParent()->convertToWorldSpace(this->getPosition());
	Vec2 heroWordPoint = hero->getParent()->convertToWorldSpace(hero->getPosition());
	auto censer = __NotificationCenter::getInstance();
	if (fabsf(monsterWordPoint.x - heroWordPoint.x) >= 400)
	{
		curState = Partol;
		if (curState != beforeSendState)
		{
			censer->postNotification("partol", this);
			beforeSendState = Partol;
		}
	}else if(fabsf(monsterWordPoint.x - heroWordPoint.x) > 100 && fabsf(monsterWordPoint.x - heroWordPoint.x) < 600)
	{
		if (!_isRun)
		{
			this->monsterRunAnimation();
			_isRun = true;
		}
		censer->postNotification("pursuit", this);
		beforeSendState = Pursuit;
	}else if(fabsf(monsterWordPoint.x - heroWordPoint.x) <= 100)
	{
		if(heroWordPoint.x > monsterWordPoint.x)
		{
			this->setRotationY(180);
			progress->setRotationY(180);
		}
		else
		{
			this->setRotationY(0);
			progress->setRotationY(0);
		}
		if (counts == 0)
		{
			counts = 120;
			censer->postNotification("attack", this);
			beforeSendState = Attack;
			
		}
	}
	if (counts > 0)
	{
		counts--;
	}
}

void MonsterBase::monsterHurt(int attack)
{
	int attackPercentage = (CCRANDOM_0_1() - 0.5) * (attack / 10);
	_isHurt = true;
	this->_hpValue -= attack + attackPercentage;
	_hurtAttackValue = attack + attackPercentage;
	hurtHpAnimation();
	float p = float(this->_hpValue) / float(this->allHp) * 100;
	progress->setPercentage(p);
	if (_hpValue <= 0)
	{
		auto addExp = __NotificationCenter::getInstance();
		addExp->postNotification("getMonsterExp", this);
		monsterDieAnimation();
		if(_id == 3)
		{
			auto endOnHook = __NotificationCenter::getInstance();
	        endOnHook->postNotification("endOnHook");
			auto boosDie = __NotificationCenter::getInstance();
			boosDie->postNotification("BoosDie");
			auto scene =dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
			MonsterLayer *monsterLayer = dynamic_cast<MonsterLayer *>(scene->getMonsterLayer());
			this->runAction(Sequence::create(CallFunc::create([=](){
				monsterLayer->stopUnschedu();
			}),CallFunc::create(CC_CALLBACK_0(MonsterBase::cleanAllMonster,this)),nullptr));
		}
		
	}else
	{
		auto isMonsterHurt = __NotificationCenter::getInstance();
		isMonsterHurt->postNotification("isMonsterHurt",this);
	    monsterHurtAnimation();
	}
}

void MonsterBase::cleanAllMonster()
{
	Monsters * monsters = Monsters::getInstance();
	for(auto x = monsters->getMonsterVector().begin(); x != monsters->getMonsterVector().end(); x++)
	{
		(*x)->monsterDie();
	}
}

void MonsterBase::hurtHpAnimation()
{
    SimpleAudioEngine::getInstance()->playEffect("monsterHurt.mp3");
	auto scene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	string attackHpValue = StringUtils::format("-%d", _hurtAttackValue); 
	Label * attackHpValueLabel = Label::create(attackHpValue,"",100);
	Vec2 monsterWordPoint = this->getParent()->convertToWorldSpace(this->getPosition());
	attackHpValueLabel->setPosition(monsterWordPoint.x, monsterWordPoint.y + this->getContentSize().height / 2);
	attackHpValueLabel->setColor(Color3B::YELLOW);
	scene->getSundriesLayer()->addChild(attackHpValueLabel,1,20);
	attackHpValueLabel->runAction(Sequence::create( MoveBy::create(1,Vec2(0,400)), CallFunc::create([=](){
		attackHpValueLabel->removeFromParent();
	}),NULL));
}

void MonsterBase::monsterDie()
{
	this->setMonsterDie(true);
	monsterRemove();
}

void MonsterBase::monsterRemove()
{
	this->removeFromParentAndCleanup(true);
}

void MonsterBase::monsterPartol()
{
	Size vSize = Director::getInstance()->getVisibleSize();
	if(_isHurt)
	{
	   return;
	}
	float dis = CCRANDOM_0_1() * 960 - 400;
	if(dis > 0)
	{
		this->setRotationY(180);
		if((dis + this->getPositionX()) >= (vSize.width * 2))
		{
		    this->setRotationY(0);
			dis = - dis;
		}
	}else
	{
		this->setRotationY(0);
		if((dis + this->getPositionX()) <= 0)
		{
		    this->setRotationY(180);
			dis = - dis;
		}
	}
	auto move1 = MoveBy::create(fabsf(dis / 50), Vec2(dis, 0));	
	auto cf = CallFunc::create([=](){
		monsterPartol();
	});
	auto monstermove =Sequence::create(move1, cf, NULL);
	monstermove->setTag(8011);
	this->runAction(monstermove);
}

void MonsterBase::monsterPursuit()
{
	if(_isHurt)
	{
	   return;
	}
	float addSpeed = CCRANDOM_0_1() - 0.5;
	Vec2 monsterWordPoint = this->getParent()->convertToWorldSpace(this->getPosition());
	Vec2 heroWordPoint = hero->getParent()->convertToWorldSpace(hero->getPosition());
	this->stopActionByTag(8011);
	if (monsterWordPoint.x > heroWordPoint.x){
		this->setRotationY(0);
		this->setPositionX(this->getPositionX() - _speedValue - addSpeed);
	}else if (monsterWordPoint.x < heroWordPoint.x){
		this->setRotationY(180);
		this->setPositionX(this->getPositionX() + _speedValue + addSpeed);
	}
}

void MonsterBase::monsterAttack()
{
	if (CCRANDOM_0_1() > 0.01)
	{
		_monsterAttackState = true;
		this->stopActionByTag(8012);
		_isRun = false;
		if (this->getPositionX() > hero->getPositionX()){
			this->setRotationY(0);
		}else if (this->getPositionX() - 70 < hero->getPositionX()){
			this->setRotationY(180);
		}
		monsterAttackAnimation();
	}else
	{
		_monsterAttackState = false;
	}
}

void MonsterBase::monsterRunAnimation()
{
	auto move = _animateClass->monsterRun(_id);
	move->setTag(8012); // 走的动画
	this->stopActionByTag(8013); // 打的动画
	this->runAction(move);
}

void MonsterBase::monsterAttackAnimation(){
	auto att = _animateClass->monsterAttack(_id);
	att->setTag(8013);
	this->stopActionByTag(8012);
	_isRun = false;
	this->runAction(att);
}

void MonsterBase::monsterHurtAnimation()
{
	this->runAction(Sequence::create( _animateClass->monsterHurt(_id), CallFunc::create([=](){
		_isHurt = false;
	}), NULL));
}

void MonsterBase::monsterDieAnimation()
{
	
	this->runAction(Sequence::create(Blink::create(0.1,2), CallFunc::create(CC_CALLBACK_0(MonsterBase::monsterDie, this)), nullptr));
}

void MonsterBase::monsterHpSprite(){
	auto hps = Sprite::create("monsterhp1.png");
	hps->setPosition(this->getPosition().x + this->getContentSize().width/2,this->getPositionY() + this->getContentSize().height);
	this->addChild(hps);
	progress = ProgressTimer::create(Sprite::create("monsterHp.png"));
	progress->setType(ProgressTimerType::BAR);
	progress->setBarChangeRate(Vec2(1,0));
	progress->setMidpoint(Vec2(0,0));
	progress->setPercentage(100.0f);
	progress->setPosition(hps->getPosition());
	this->addChild(progress);
}

MonsterBase::~MonsterBase()
{
}