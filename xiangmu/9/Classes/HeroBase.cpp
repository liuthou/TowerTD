#include "HeroBase.h"
#include "HeroMacro.h"
#include "MonsterBase.h"
#include "MonsterLayer.h"
#include "AnimateClass.h"
#include "GameMainScene.h"
#include "AnimateClass.h"
#include "SwordAnger.h"
#include "Lightning.h"
#include "BigSkill.h"
#include "SkillShowLayer.h"
#include "Skilles.h"
#include "GameOverLayer.h"
#include "SundriesLayer.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool HeroBase::initWithSpriteFrameName(std::string filename)
{
	if (!Sprite::initWithSpriteFrameName(filename))
	{
		return false;
	}
	this->setScale(2);	
	this->setHeroDie(false);
	_attackState = false;
	_skillReleaseContainer = SkillReleaseContainer::getInstance();
	//可见尺寸
	Vec2 vSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(vSize.x/9, vSize.y/6 + 50));
	_animate = AnimateClass::create();
	_touch = MoTouch::create();
	this->addChild(_touch);
	_touch->actionDriection = std::bind(&HeroBase::judgeActionType, this, std::placeholders::_1);
	//建立观察者，观察技能cd
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->addObserver(this,callfuncO_selector(HeroBase::endSkill1Cd), "Skill1Cd",nullptr);
	auto centerSkill1 = __NotificationCenter::getInstance();
	centerSkill1->addObserver(this,callfuncO_selector(HeroBase::endSkill2Cd), "Skill2Cd",nullptr);
	//建立观察者，观察大招的cd结束
	auto bigSkillCd = __NotificationCenter::getInstance();
	bigSkillCd->addObserver(this,callfuncO_selector(HeroBase::endBigSkillCd), "bigSkillCd",nullptr);
	//建立观察者，观察移动的方向
	auto centerMoveLeft = __NotificationCenter::getInstance();
	centerMoveLeft->addObserver(this,callfuncO_selector(HeroBase::endMoveLeft), "centerMoveLeft",nullptr);
	auto centerMoveRight = __NotificationCenter::getInstance();
	centerMoveRight->addObserver(this,callfuncO_selector(HeroBase::endMoveRight), "centerMoveRight",nullptr);
	//建立观察者，观察怪物是否受伤
	auto isMonsterHurt = __NotificationCenter::getInstance();
	isMonsterHurt->addObserver(this,callfuncO_selector(HeroBase::attackKnocking), "isMonsterHurt",nullptr);
	//建立观察者，观察怪物是否死亡并获得经验值
	auto addExp = __NotificationCenter::getInstance();
	addExp->addObserver(this,callfuncO_selector(HeroBase::addExp), "getMonsterExp",nullptr);
	//建立观察者，自动回血回蓝
	schedule(schedule_selector(HeroBase::heroAddHpMp),3);
	return true;
}

void HeroBase::heroAddHpMp(float t)
{
	if(_hpValue < _allHp )
	{
		_hpValue += _allHp * 0.01;
		auto censerhp = __NotificationCenter::getInstance();
		censerhp->postNotification("heroHurtHp", this);
	}
	if(_mpValue < _allMp)
	{
		_mpValue += _allMp * 0.01;
		auto centerSkill = __NotificationCenter::getInstance();
	    centerSkill->postNotification("heroCostlan", this);
	}
}

void HeroBase::addExp(Ref * obj)
{
	MonsterBase * monsterBase = dynamic_cast<MonsterBase *>(obj);
	_nowExpValue += monsterBase->getExpValue();
	_takeExpValue += monsterBase->getExpValue();
	while (1)
	{
		if(_nowExpValue - _expValue >= 0)
		{
				_levelValue += 1;
				_needExp = 400 + (_levelValue) * 200;
				_expValue = ((400 + (400 + (_levelValue) * 200)) * (_levelValue + 1)) / 2;
				addHeroAttribute();
		}
		else
		{
			break;
		}
	}
	auto addHeroExp = __NotificationCenter::getInstance();
	addHeroExp->postNotification("heroAddExp",this);
}

void HeroBase::addHeroAttribute()
{
	_hpValue = _allHp + _allHp * 0.3;
	_allHp = _hpValue;
	_mpValue = _allMp + _allMp * 0.01;
	_allMp = _mpValue;
	_attackBaseValue = _attackBaseValue + _attackBaseValue * 0.4;
	_defenseValue = _defenseValue + _defenseValue * 0.4;
	_agilityValue = _agilityValue + _agilityValue * 0.2;
	_spValue += 2;
}

void HeroBase::judgeActionType(Driection type)
{
	if(_heroDie || _isOneDownSkill || _isBigSkill)
	{
	   return;
	}
	Skilles * skilles = Skilles::getInstance();
	auto skill = skilles->getSkilles().begin();
	_directionType = type;
	if (type != STOP){
	   _directionTypeWrite = type;
	}
	if (_directionType == LEFT || _directionType == RIGHT)
	{   if(!_isOneAttack && !_isOneJump && !_isOneJumpSkill && !_isOneDownSkill && !_isOneLeftSkill && !_isOneRightSkill)
	    {
			if(_directionType == LEFT)
			{
				_directionRunTypeWrite = LEFT;
			   this->setRotationY(180);
			   
			}
			else
			{
				_directionRunTypeWrite = RIGHT;
			   this->setRotationY(0);
			}
			if(!_isRun)
			{
				_isRun = true;	
				Vec2 vSize = Director::getInstance()->getVisibleSize();
				schedule(schedule_selector(HeroBase::heroAddRun),0);
				heroRun();
			}
	    }
	}
	else if (_directionType == JUMP)
	{
		if(!_isOneAttack && !_isReleaseSkill && !_isOneJump)
	    {
			_isOneJump = true;
	    	heroJump();
		}
	}
	else if (_directionType == NEARSKILL)
	{	
		if(!_isOneDownSkill && !_isOneJump && !_isOneAttack  && !_downSkill && _mpValue >= (*(skill + 1))->getConsumeMp())
		{
			_isReleaseSkill = true;
			_downSkill = true;
			_isOneDownSkill = true;
			_dir = NEARSKILL;
			heroLightningSkillAttick();
			this->runAction(Sequence::create(DelayTime::create(2),CallFunc::create(CC_CALLBACK_0(HeroBase::createLighning,this)),NULL));
		}
	}
	else if (_directionType == LEFTFARSKILL)
	{
		if(!_isOneLeftSkill && !_isOneJump && !_isOneAttack && !_leftRightSkill && _mpValue >= (*skill)->getConsumeMp())
		{
			_isReleaseSkill = true;
			_leftRightSkill = true;
			this->setRotationY(180);
			_dir = LEFTFARSKILL;
			_isOneLeftSkill = true;
			heroSwordSkillAttack();
			this->runAction(Sequence::create(DelayTime::create(0.3),CallFunc::create(CC_CALLBACK_0(HeroBase::createSwordAnger,this)),NULL));
		}
	}
	else if (_directionType == RIGHTFARSKILL)
	{
		if(!_isOneRightSkill && !_isOneJump && !_isOneAttack && !_leftRightSkill && _mpValue >= (*skill)->getConsumeMp())
		{
			_isReleaseSkill = true;
			_leftRightSkill = true;
			this->setRotationY(0);
			_dir = RIGHTFARSKILL;
			_isOneRightSkill = true;
			heroSwordSkillAttack();
			this->runAction(Sequence::create(DelayTime::create(0.3),CallFunc::create(CC_CALLBACK_0(HeroBase::createSwordAnger,this)),NULL));
		}
	}
	else if (_directionType == ATTACK)
	{
		if(!_isOneJump && !_isReleaseSkill && !_isOneAttack)
		{
			_isOneAttack = true;
			heroCommonAttack();
		}
	}
	else if (_directionType == STOP)
	{
		auto centerBackgroundMove = __NotificationCenter::getInstance();
	    centerBackgroundMove->postNotification("stopBackgroundMove");
		heroStop();
	}
}

void HeroBase::heroAddRun(float t)
{
	Vec2 vSize = Director::getInstance()->getVisibleSize();
	if(this->getPositionX() > vSize.x/2 && !_isRightBoundary)
	{
		if(_directionType == RIGHT)
		 {
			 _isLeftBoundary = false;
			 auto centerBackgroundMoveRight = __NotificationCenter::getInstance();
			 centerBackgroundMoveRight->postNotification("backgroundMoveRight");
		 }
		else if(_directionType == LEFT)
		{
		     auto centerBackgroundMoveLeft = __NotificationCenter::getInstance();
			 centerBackgroundMoveLeft->postNotification("backgroundMoveLeft");
		}
	}
	else
	{
		if(this->getPositionX() < vSize.x/2 + 2 * MOVE_SPEED)
		{
		    _isRightBoundary = false;
		}
		 if(_directionType == LEFT)
		{
			if(this->getPositionX() <= this->getContentSize().width/2)
			{
				this->setPositionX(this->getContentSize().width/2);
			}
			else
			{
			    this->setPositionX(this->getPositionX() - MOVE_SPEED);
				if(_isMenu)
				{
					_men->setPositionX(this->getPositionX() - MOVE_SPEED);
				}
			}
			
		}
		if(_directionType == RIGHT)
		{
			if(this->getPositionX() >= vSize.x - this->getContentSize().width/2)
			{
				this->setPositionX(vSize.x - this->getContentSize().width/2);
			}
			else
		 	{
			    this->setPositionX(this->getPositionX() + MOVE_SPEED);
				if(_isMenu)
				{
					_men->setPositionX(this->getPositionX() + MOVE_SPEED);
				}
			}
		}	
	}
}

void HeroBase::endMoveLeft(Ref * obj)
{
	if(!_isLeftBoundary)
	{
	    _isLeftBoundary = true;
		this->setPositionX(this->getPositionX() - MOVE_SPEED);
	}
}

void HeroBase::endMoveRight(Ref * obj)
{
	if(!_isRightBoundary)
	{
	   _isRightBoundary = true;
	}
	
}

void HeroBase::heroRun()
{  
	auto runAnimate = _animate->heroRun();
    runAnimate->setTag(RUNANIMATE);
	this->runAction(runAnimate);
}

void HeroBase::heroJump()
{
    SimpleAudioEngine::getInstance()->playEffect("ground.wav");
	_jumpAttackState = true;
	auto jumpAnimate = _animate->heroJumpAttack();
	jumpAnimate->setTag(JUMPANIMATE);
	this->runAction(Sequence::create(Spawn::create(JumpBy::create(JUMPBY_TIME,Vec2(0,0),JUMPBY_HIGHT,JUMPBY_NUMBER),jumpAnimate,NULL),CallFunc::create(CC_CALLBACK_0(HeroBase::restoreOneJump,this)),NULL));
    if (_isMenu){
		_men->runAction(JumpBy::create(JUMPBY_TIME, Vec2(0, 0), JUMPBY_HIGHT, JUMPBY_NUMBER));
	}
}

void HeroBase::heroCommonAttack()
{
	_attackState = true;
	auto attackAnimate = _animate->heroAttack();
	attackAnimate->setTag(ATTACKANIMATE);
	this->runAction(Sequence::create(attackAnimate,CallFunc::create(CC_CALLBACK_0(HeroBase::restoreOneAttack,this)),CallFunc::create(CC_CALLBACK_0(HeroBase::endAttackAnimation, this)), CallFunc::create([=](){
		_practicalAttackValue = _attackValue + _attackGearValue;
		_isAttackKnocking = false;
	}), NULL));
	 float criticalProbability = CCRANDOM_0_1();
	 if(criticalProbability < 0.1)
	 {
		  _practicalAttackValue *= 2;
		  _isAttackKnocking = true;
	 }
}

void HeroBase::attackKnocking(Ref * obj)
{
	 if(_isAttackKnocking)
	 {
		  auto scene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
		  Sprite * practicaPicture = Sprite::create("battle_baoji.png");
		  practicaPicture->setScale(2.5);
		  practicaPicture ->setPosition(Vec2(this->getPositionX(),this->getPositionY() + this->getContentSize().height/2 + 50));
		  practicaPicture->runAction(Sequence::create( DelayTime::create(0.2), MoveBy::create(0.3,Vec2(0,100)), CallFunc::create([=](){
		  practicaPicture->removeFromParent();
		  }), NULL));
		  scene->getSundriesLayer()->addChild(practicaPicture, 4);
	 }
}

void HeroBase::heroSwordSkillAttack()
{   
	//向技能显示层发送消息
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("SkillType", this);
	auto skiiAttickAnimate = _animate->heroSwordAnger();
	skiiAttickAnimate->setTag(SKILLATTACKANIMATE);
	this->runAction(Sequence::create(skiiAttickAnimate,CallFunc::create(CC_CALLBACK_0(HeroBase::restoreOneSkill,this)),NULL));
}

void  HeroBase::heroLightningSkillAttick()
{
	//向技能显示层发送消息
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("SkillType", this);
	auto skiiAttickAnimate = _animate->heroLightningAnger();
	skiiAttickAnimate->setTag(SKILLATTACKANIMATE);
	this->runAction(Sequence::create(skiiAttickAnimate, DelayTime::create(2.4), CallFunc::create(CC_CALLBACK_0(HeroBase::restoreOneSkill,this)),NULL));
}

void HeroBase::heroStop()
{
	_isRun = false;
	this->stopActionByTag(RUNANIMATE);
	unschedule(schedule_selector(HeroBase::heroAddRun));
}

void HeroBase::heroHurt(int attack)
{
	if(_heroDie || _isOneDownSkill)
	{
	   return;
	}
	if(CCRANDOM_0_1() < (_agilityValue + _agilityGearValue))
	{
		this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=](){
		  auto scene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
		  Sprite * practicaPicture = Sprite::create("battle_shanbi.png");
		  practicaPicture->setScale(2.5);
		  practicaPicture ->setPosition(Vec2(this->getPositionX(),this->getPositionY() + this->getContentSize().height/2 + 50));
		  practicaPicture->runAction(Sequence::create( DelayTime::create(0.2), MoveBy::create(0.3,Vec2(0,100)), CallFunc::create([=](){
		  practicaPicture->removeFromParent();
		  }), NULL));
		  scene->getSundriesLayer()->addChild(practicaPicture, 3);
		}), NULL));
		  
	}
	else
	{
		this->_hpValue -= attack - (attack * (_defenseValue + _defenseGearValue));
		if (_hpValue<=0)
		{
			heroDie();
			heroStop();
			_heroDie = true;
			unschedule(schedule_selector(HeroBase::heroAddHpMp));
			auto centerBackgroundMove = __NotificationCenter::getInstance();
	        centerBackgroundMove->postNotification("stopBackgroundMove");
		}
		else
		{
		  this->runAction(Sequence::create(DelayTime::create(0.5), _animate->heroHurt(), nullptr));
		}
		auto censerhp = __NotificationCenter::getInstance();
		censerhp->postNotification("heroHurtHp", this);
	}
	
}

void HeroBase::heroDie()
{   
	this->runAction(Sequence::create(CallFunc::create([=](){
		auto gameMainScene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
		auto monsterLayer = dynamic_cast<MonsterLayer *>(gameMainScene->getMonsterLayer());
		monsterLayer->stopUnschedu();
	}), _animate->heroDie(), DelayTime::create(1), CallFunc::create([=](){
		auto scene =Director::getInstance()->getRunningScene();
		scene->addChild(GameOverLayer::create());
	}), nullptr) );
}

void HeroBase::restoreOneAttack()
{
	_isOneAttack = false;
}

void HeroBase::restoreOneJump()
{
	_isOneJump = false;
}

void HeroBase::restoreOneSkill()
{
	_isReleaseSkill = false;
	_isOneDownSkill = false;
	_isOneLeftSkill = false;
	_isOneRightSkill = false;		
	_isOneJumpSkill = false;
}

void HeroBase::createSwordAnger(){
	 SwordAnger * swordAnger;
	if(_dir == RIGHTFARSKILL)
	{
	    swordAnger = SwordAnger::create(Vec2(this->getPositionX() + this->getContentSize().width/2,this->getPositionY()),_dir);
	}
	else if(_dir == LEFTFARSKILL)
	{
	    swordAnger = SwordAnger::create(Vec2(this->getPositionX() - this->getContentSize().width/2,this->getPositionY()),_dir);
	}
   _skillReleaseContainer->addSkillRelease(swordAnger);
   _mpValue -= swordAnger->getConsumeMp();
   	//向蓝条发送信息
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("heroCostlan", this);
}

void HeroBase::createLighning()
{
	AnimateClass * animateClass = AnimateClass::create();
	Lightning * lightning;
   for(int i = 0;i < 3;i++)
   {
		   lightning = Lightning::create(Vec2(this->getPositionX() + this->getContentSize().width/1.1 + this->getContentSize().width * i,this->getPositionY() + 180));
		   _skillReleaseContainer->addSkillRelease(lightning);
   }
    for(int i = 0;i < 3;i++)
   {
		   lightning = Lightning::create(Vec2(this->getPositionX() - this->getContentSize().width/1.1 - this->getContentSize().width * i,this->getPositionY() + 180));
		   _skillReleaseContainer->addSkillRelease(lightning); 
   }
    _mpValue -= lightning->getConsumeMp();
	//恢复禁止状态
	this->runAction(Sequence::create(DelayTime::create(8),animateClass->heroStop(),NULL));
   	//向蓝条发送信息
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("heroCostlan", this);
}

void HeroBase::createBigSkill()
{
	Size vSize = Director::getInstance()->getVisibleSize();
	BigSkill * bigSkill = BigSkill::create(Vec2(this->getPositionX(), vSize.height / 2.2));
    _skillReleaseContainer->addSkillRelease(bigSkill);
    _mpValue -= bigSkill->getConsumeMp();
   	//向蓝条发送信息
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("heroCostlan", this);
}

void HeroBase::endSkill1Cd(Ref * obj)
{	
	_leftRightSkill = false;
}

void HeroBase::endSkill2Cd(Ref * obj)
{	
	_downSkill = false;
}

void HeroBase::endBigSkillCd(Ref * obj)
{		
	//创建按钮精灵
	Sprite * spriteButton = Sprite::createWithSpriteFrameName("bbu0.png");
	//按钮精灵的动画
	Animation * buttonAnimation = Animation::create();
	for(int i = 0; i < 12; i++)
	{
	    std::string filename = StringUtils::format("bbu%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		buttonAnimation->addSpriteFrame(frame);
	}
	buttonAnimation->setDelayPerUnit(0.1);
	buttonAnimation->setLoops(-1);
	spriteButton->runAction(Animate::create(buttonAnimation));
	AnimateClass * animateClass = AnimateClass::create();
	Skilles * skilles = Skilles::getInstance();
    auto skill = skilles->getSkilles().begin();
	GameMainScene * gameMainScene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	SundriesLayer * sundriesLayer = dynamic_cast<SundriesLayer *>(gameMainScene->getSundriesLayer());
	MenuItemSprite * menuItem = MenuItemSprite::create(spriteButton,spriteButton,[=](Ref * obj){
		if(_mpValue >= (*(skill + 2))->getConsumeMp() && !_heroDie)
	    { 
			this->runAction(Sequence::create(animateClass->heroLightningAnger(), CallFunc::create([=](){
				_isBigSkill = false;
			}), NULL));
			_isBigSkill = true;
			_isMenu = false;
			createBigSkill();
			auto bigSkillEnd = __NotificationCenter::getInstance();
			bigSkillEnd->postNotification("BigSkillEnd");
			_men->removeFromParent();
		}
	});
	_men = Menu::create(menuItem, nullptr);
	_men->setPosition(this->getPositionX(),this->getPositionY() + this->getContentSize().height/2);
	sundriesLayer->addChild(_men);	
	_isMenu = true;
	
}

void HeroBase::endAttackAnimation()
{
	//_attackState = false;
}

HeroBase::~HeroBase()
{
	auto centerSkillDown = __NotificationCenter::getInstance();
	centerSkillDown->removeObserver(this, "Skill1Cd");
	auto centerSkill1 = __NotificationCenter::getInstance();
	centerSkill1->removeObserver(this, "Skill2Cd");
	auto centerMoveLeft = __NotificationCenter::getInstance();
	centerMoveLeft->removeObserver(this, "centerMoveLeft");
	auto centerMoveRight = __NotificationCenter::getInstance();
	centerMoveRight->removeObserver(this, "centerMoveRight");
	auto isMonsterHurt = __NotificationCenter::getInstance();
	isMonsterHurt->removeObserver( this, "isMonsterHurt");
	auto addExp = __NotificationCenter::getInstance();
	addExp->removeObserver(this, "getMonsterExp");
	auto bigSkillCd = __NotificationCenter::getInstance();
	bigSkillCd->removeObserver(this, "bigSkillCd");
}