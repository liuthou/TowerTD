#include "Role.h"
#include "ActionsFactory.h"
#include "GameData.h"
#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
#include "DataXML.h"

bool Role::init() {
	
	if (!BaseSprite::initWithSpriteFrameName(StringUtils::format("%s_01.png", ROLE_RUN_FILENAME)))
	{
		return false;
	}
	bostZoneFlag = false;
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	this->m_type = "ROLE";
	this->m_name = "Role";
	this->m_hp = ROLE_ALL_HP;
	this->m_state = 0;

	isJumpingDown = false;
	isFastRun = false;
	isNormalRun = true;
	isSlowRnu = false;
	isRunning = false;
 
	normalRunAction = ActionsFactory::createAction(ROLE_RUN_FILENAME, 20, 0.0375, -1);
	slowRunAction = ActionsFactory::createAction(ROLE_RUN_FILENAME, 20, 0.065, -1);
	fastRunAction = ActionsFactory::createAction(ROLE_RUN_FILENAME, 20, 0.0175, -1);
	jumpUpAction = ActionsFactory::createAction(ROLE_JUMP_UP_FILENAME, 11, 0.04, 1);
	hurtAction = ActionsFactory::createAction(ROLE_HURT_FILENAME, 10, 0.04, 1);
	electricAction = ActionsFactory::createAction(ROLE_ELECTRIC_FILENAME, 9, 0.04, 1);

	normalRunAction->retain();
	slowRunAction->retain();
	fastRunAction->retain();
	jumpUpAction->retain();
	hurtAction->retain();
	electricAction->retain();

	addPhysicsBody();
	addSprite();
	addParticle();
	this->schedule(schedule_selector(Role::moveY));

	this->scheduleUpdate();

	this->schedule(schedule_selector(Role::dropHpByTime), DORP_HP_TIME);

	//边界检测
	this->schedule(schedule_selector(Role::boundaryDetection));

	return true;
}

void Role::addParticle(){
	quickBlood = ParticleSystemQuad::create("quickparticle.plist");
	quickBlood->setNormalizedPosition(Vec2(0.9,0.95));
	this->addChild(quickBlood);
	slowBlood = ParticleSystemQuad::create("slowparticle.plist");
	slowBlood->setNormalizedPosition(Vec2(0.9,0.95));
	slowBlood->setVisible(false);
	this->addChild(slowBlood);
}

void Role::addSprite(){
	protect = Sprite::createWithSpriteFrameName(ROLE_STATE_PROTECT);
	protect->setNormalizedPosition(Vec2(0.5, 0.5));
	this->addChild(protect);
	protect->setVisible(false);

	bucket = Sprite::createWithSpriteFrameName(StringUtils::format("%s_01.png",ROLE_STATE_BUCKET));
	bucket->setNormalizedPosition(Vec2(0.9, 0.95));
	bucket->setScale(0.8);
	bucket->runAction(ActionsFactory::createAction(ROLE_STATE_BUCKET, 11, 0.05, -1));
	this->addChild(bucket);
	bucket->setVisible(false);

	band = Sprite::createWithSpriteFrameName(ROLE_STATE_BAND);
	band->setNormalizedPosition(Vec2(0.95, 0.95));
	band->setScale(0.7);
	this->addChild(band);
	band->setVisible(false);
}

void Role::addPhysicsBody(){
	m_body = PhysicsBody::createCircle(this->getContentSize().width / 2 - 15, PHYSICSBODY_MATERIAL_DEFAULT);
	m_body->setDynamic(true);
	m_body->setGravityEnable(false);
	m_body->setCategoryBitmask(1);
	m_body->setCollisionBitmask(1);
	m_body->setContactTestBitmask(1);
	this->setPhysicsBody(m_body);
}

void Role::changeState(int state) {
	
	this->m_state |= state;
	EFFECT_MUSIC("pickup.mp3",audioFlag);
}

void Role::normalRun() {

	this->stopAllActions();
	this->runAction(normalRunAction);
}

void Role::slowRun() {

	this->isSlowRnu = true;
	this->isRunning = false;
	this->isNormalRun = false;
	this->isFastRun = false;
}

void Role::stopSlowRun() {

	this->isRunning = false;
	this->isFastRun = false;
	this->isSlowRnu = false;
	this->isNormalRun = true;
}

void Role::jumpUp() {
	EFFECT_MUSIC("arm whoosh 03.mp3", audioFlag);
	isJumpingDown = false;
	isRunning = true;
 	this->stopAllActions();
 	auto jumpUp = MoveBy::create(0.25, Vec2(0,130));
	auto jumpDownCall = CallFunc::create([=](){

		isJumpingDown = true;
		isRunning = false;
		this->setTexture(ROLE_JUMPING_0_FILENAME); 
	});

	auto spawn = Spawn::create(jumpUp, jumpUpAction, NULL);
	auto seq = Sequence::create(spawn, jumpDownCall, NULL);

 	this->runAction(seq);
}

void Role::hurt(int attack, bool isEfence){
	isJumpingDown = false;
	isRunning = true;
	this->stopAllActions();
	if (isEfence)
	{
		this->runAction(electricAction);
		EFFECT_MUSIC("electric.mp3",audioFlag);
	}else{
		this->runAction(hurtAction);
		EFFECT_MUSIC("hard hit.mp3",audioFlag);
	}
	auto hurtJump = MoveBy::create(0.4,Vec2(0,100));
	CallFunc * hurtJumpCall = CallFunc::create([=](){
		isJumpingDown = true;
		isRunning = false;
		this->setTexture(ROLE_JUMPING_1_FILENAME);
	});
	this->runAction(Sequence::create(hurtJump, hurtJumpCall, NULL));
	//判断保护罩 水桶 创可贴的状态
	if (protect->isVisible())
	{
		CallFunc * protectDisappear = CallFunc::create([=](){
			protect->setVisible(false);
		});
		protect->runAction(Sequence::create(Blink::create(1, 5), protectDisappear, NULL));
		return;
	}
	else if (bucket->isVisible())
	{
		bucket->setVisible(false);
		quickBlood->setVisible(true);
		slowBlood->setVisible(false);
	}
	else if (band->isVisible())
	{
		band->setVisible(false);
		quickBlood->setVisible(true);
		slowBlood->setVisible(false);
	}
	this->m_hp -= attack;
}

void Role::fastRun() {

	this->isRunning = false;
	this->isFastRun = true;
	this->isSlowRnu = false;
	this->isNormalRun = false;
}

void Role::stopFastRun() {

	this->isRunning = false;
	this->isFastRun = false;
	this->isSlowRnu = false;
	this->isNormalRun = true;
}

void Role::moveY(float t) {

	if (isJumpingDown)
	{
		if (this->getPositionY() > ROLE_POSITION_Y)
		{
			this->setPositionY(this->getPositionY() - 350 * t);
		}
	}
}

void Role::die(){
	m_body->setCategoryBitmask(0);
	m_body->setCollisionBitmask(0);
	m_body->setContactTestBitmask(0);
	this->stopAllActions();
	this->unschedule(schedule_selector(Role::moveY));
	this->setTexture(ROLE_DIEPING_FILENAME);
	auto moveDie = JumpTo::create(1.5, Vec2(this->getPositionX(), -20), 200, 1);
	auto postNot = CallFunc::create([=](){
		__NotificationCenter::getInstance()->postNotification("GAME_OVER", this);
	});
	this->runAction(Sequence::create(moveDie, postNot, NULL));
}

void Role::update(float t) {

	if (this->getPositionY() <= ROLE_POSITION_Y && !isRunning)
	{
		this->stopAllActions();
		if (isNormalRun)
		{
			this->runAction(normalRunAction);
			isRunning = true;
		}

		else if (isSlowRnu)
		{
			this->runAction(slowRunAction);
			isRunning = true;
		}

		else if (isFastRun)
		{
			this->runAction(fastRunAction);
			isRunning = true;
		}
	}

	if (m_state & Role_protected)
	{
		protect->setVisible(true);
		m_state ^= Role_protected;
	}

	if (m_state & Role_doubleScore)
	{
		__NotificationCenter::getInstance()->postNotification("DOUBLE_SCORE", this);
		this->m_state ^= Role_doubleScore;
	}

	if (m_state & Role_goldDoubleScore)
	{
		__NotificationCenter::getInstance()->postNotification("GLOD_DOUBLE_SCORE", this);
		this->m_state ^= Role_goldDoubleScore;
	}

	if (m_state & Role_bucket)
	{
		bucket->setVisible(true);
		band->setVisible(false);
		m_state ^= Role_bucket;
		quickBlood->setVisible(false);
		slowBlood->setVisible(false);
	}

	if (m_state & Role_band)
	{
		if (!bucket->isVisible())
		{
			band->setVisible(true);
			quickBlood->setVisible(false);
			slowBlood->setVisible(true);
		}
		m_state ^= Role_band;
	}
	
	if (m_state & Role_addBlood)
	{
		this->m_hp += BLOOD_ADD_HP;
		if (m_hp > ROLE_ALL_HP)
		{
			m_hp = ROLE_ALL_HP;
		}
		this->m_state ^=  Role_addBlood;
	}

	if (m_state  & Role_addBloodMost)
	{
		this->m_hp += 0.5 * BLOOD_ADD_HP;
		if (m_hp > ROLE_ALL_HP)
		{
			m_hp = ROLE_ALL_HP;
		}
		this->m_state ^= Role_addBloodMost;
	}

	if (m_state & Role_addScore)
	{
		__NotificationCenter::getInstance()->postNotification("ADD_50_SCORE", this);
		this->m_state ^= Role_addScore;
	}

	if (m_state & Role_addScoreMost)
	{
		__NotificationCenter::getInstance()->postNotification("ADD_100_SCORE", this);
		this->m_state ^= Role_addScoreMost;
	}
}

void Role::dropHpByTime(float t){
	if(bucket->isVisible())
	{
		this->m_hp -= ROLE_SCEOND_HP * 0;
		return;
	}else if (band->isVisible())
	{
		this->m_hp -= ROLE_SCEOND_HP * BOND_DROP_HP;
		return;
	}else
	{
		this->m_hp -= ROLE_SCEOND_HP;
	}
	if (m_hp <= 0)
	{
		this->unschedule(schedule_selector(Role::dropHpByTime));
		this->unscheduleUpdate();
		die();
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
		EFFECT_MUSIC("end.mp3",audioFlag);
		EFFECT_MUSIC("die_no_blood.mp3",audioFlag);
	}
}

void Role::boundaryDetection(float t){
	if (this->getPositionY() >= 500)
	{
		this->setPositionY(500);
	}
	if (this->getPositionX() <= 25)
	{
		this->setPositionX(25);
	}
	if (this->getPositionX() >= 935)
	{
		this->setPositionX(935);
	}
	if (this->getPositionX() >= 585 && !bostZoneFlag)
	{
		__NotificationCenter::getInstance()->postNotification("BOST_SCORE", this);
		bostZoneFlag = true;
	}
	if (this->getPositionX() <= 585 && bostZoneFlag)
	{
		__NotificationCenter::getInstance()->postNotification("DELETE_BOST_SCORE", this);
		bostZoneFlag = false;
	}
}

Role::~Role()
{
	normalRunAction->release();
	slowRunAction->release();
	fastRunAction->release();
	jumpUpAction->release();
	hurtAction->release();
	electricAction->release();
}
