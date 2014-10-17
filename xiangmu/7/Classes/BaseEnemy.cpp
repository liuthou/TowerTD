#include "BaseEnemy.h"
#include "RoleAnimate.h"
#include "GameScene.h"

BaseEnemy *BaseEnemy::create(std::string fileName, int speed, int type, Vec2 posi,Size size, int AI){
	BaseEnemy *baseEnemy = new BaseEnemy();
	if (baseEnemy && baseEnemy->initWithSpriteFrameName(fileName,speed,type,posi,size,AI))
	{
		baseEnemy->autorelease();
		return baseEnemy;
	}

	CC_SAFE_DELETE(baseEnemy);
	return NULL;
}

bool BaseEnemy::initWithSpriteFrameName(std::string fileName, int speed, int type, Vec2 posi,Size size, int AI){

	if (!BaseRole::initWithSpriteFrameName(fileName)){
		return false;
	}
	m_AI = AI;
	m_isSkillReady = false;
	isDie = false;
	m_isMoving = false;
	m_size = size;
	m_isSkilled = false;
	m_isFired = false;
	m_isTaken = false;
	m_subscructStateTime = 5;
	m_posi = posi;
	m_speed = speed;
	m_type = type;
	countToJump = 0;
	isJump = false;
	m_state = 0;
	m_direction = 1;

	this->setPosition(m_posi);
	this->setScale(0.7);

	

	this->scheduleUpdate();
	this->schedule(schedule_selector(BaseEnemy::renewMove),0.99);

	//创建body
	this->setPhysicsBody(PhysicsBody::createBox(m_size));
	this->getPhysicsBody()->setRotationEnable(false);
	this->getPhysicsBody()->setCollisionBitmask(22);
	this->getPhysicsBody()->setCategoryBitmask(1);
	this->getPhysicsBody()->setContactTestBitmask(6);
	this->getPhysicsBody()->getShape(0)->setRestitution(0);//设置没有 弹性

	return true;
}


void BaseEnemy::mySkill1(){
	this->stopAllActions();
	if(m_direction == 3){
		auto cf2 = CCCallFunc::create([=](){
			enemybullet = EnemyBullet::create("LeftBullet1.png",Vec2(this->getPositionX() - this->getContentSize().width/2 + 30,this->getPositionY() + 10));
			enemybullet->setScale(0.2);
		});
		auto ani = RoleAnimate::getinstance()->getAttackAnimate(m_type,1);
		auto cf = CCCallFunc::create([=](){
			enemybullet->move(2);
		});
		auto cf1 = CCCallFunc::create([=](){
			this->m_isSkilled = false;
		});
		auto seq = Sequence::create(ani,cf2,cf,cf1,nullptr);
		seq->setTag(500);
		this->runAction(seq);
	}else{
		auto cf2 = CCCallFunc::create([=](){
			enemybullet = EnemyBullet::create("RightBullet1.png",Vec2(this->getPositionX() + this->getContentSize().width/2 - 30,this->getPositionY() + 10));
			enemybullet->setScale(0.2);
		});
		auto ani = RoleAnimate::getinstance()->getAttackAnimate(m_type,2);
		auto cf = CCCallFunc::create([=](){
			enemybullet->move(1);
		});
		auto cf1 = CCCallFunc::create([=](){
			this->m_isSkilled = false;
		});
		auto seq = Sequence::create(ani,cf2,cf,cf1,nullptr);
		seq->setTag(501);
		this->runAction(seq);	
	}
}

void BaseEnemy::mySkill2(){
	this->stopAllActions();
	if (m_direction == 3){
		std::vector<std::string>fireFileName;
		for (int i = 1; i < 5; i++){
			std::string fileName = StringUtils::format("enemy%dAttackLeft_0%d.png",m_type,i);
			fireFileName.push_back(fileName);
		}
		auto attackAni = RoleAnimate::getinstance()->createAnimate(fireFileName,0.25,1);
		auto cf = CCCallFunc::create([=](){
			this->m_isSkilled = false;
		});
		auto seq = Sequence::create(attackAni,cf,NULL);
		this->runAction(seq);
	}else if (m_direction == 4){
		std::vector<std::string>fireFileName;
		for (int i = 1; i < 5; i++){
			std::string fileName = StringUtils::format("enemy%dAttackRight_0%d.png",m_type,i);
			fireFileName.push_back(fileName);
		}
		auto attackAni = RoleAnimate::getinstance()->createAnimate(fireFileName,0.25,1); 
		auto cf = CCCallFunc::create([=](){
			this->m_isSkilled = false;
		});
		auto seq = Sequence::create(attackAni,cf,NULL);
		this->runAction(seq);
	}
}


void BaseEnemy::hurt(){

	Vec2 firePosition = Vec2(this->getContentSize().width / 2,(this->getContentSize().height - m_size.height) / 2);

	this->stopAllActions();
	this->getPhysicsBody()->setCategoryBitmask(8);
	this->getPhysicsBody()->setCollisionBitmask(18);
	this->getPhysicsBody()->setContactTestBitmask(2);


	std::vector<std::string>fileNames;
	for (int i=1;i<=2;i++){
		std::string fileName = StringUtils::format("enemy%dHurt_0%d.png",m_type,i);
		fileNames.push_back(fileName);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.3,-1);

	std::vector<std::string>fireFileName;
	for (int i = 1; i < 9; i++){
		std::string fileName = StringUtils::format("onFire_0%d.png",i);
		fireFileName.push_back(fileName);
	}
	auto fireAnimate = RoleAnimate::getinstance()->createAnimate(fireFileName,0.1,-1); 

	if(m_state == 1){
		this->removeAllChildrenWithCleanup(true);
		auto sp = Sprite::create();
		sp->setPosition(firePosition);
		sp->setScale(0.5);
		this->addChild(sp);
		sp->runAction(fireAnimate);
		this->runAction(ani);

	}
	if(m_state == 2){
		this->removeAllChildrenWithCleanup(true);
		auto sp = Sprite::create();
		sp->setPosition(firePosition);
		sp->setScale(0.7);
		this->addChild(sp);
		sp->runAction(fireAnimate);
		this->runAction(ani);
	}
	if(m_state == 3){
		this->removeAllChildrenWithCleanup(true);
		auto sp = Sprite::create();
		sp->setPosition(firePosition);
	
		this->addChild(sp);
		sp->runAction(fireAnimate);
		this->runAction(ani);
	}
	if(m_state == 4){
		this->removeAllChildrenWithCleanup(true);
		auto sp = Sprite::create();
		sp->setPosition(firePosition);
        sp->setScale(1.3);
		this->addChild(sp);
		sp->runAction(fireAnimate);
		this->runAction(ani);
	}
	if(m_state == 5){
		//this->m_isTaken = true;
		this->removeAllChildrenWithCleanup(true);
		Sprite *fireBall = Sprite::createWithSpriteFrameName("fireBall_01.png");
		fireBall->setScale(0.7);
		fireBall->setNormalizedPosition(Vec2(0.5,0.5));
		this->addChild(fireBall,100);
		std::vector<std::string>fireFileName;
		for (int i = 1; i < 4; i++){
			std::string fileName = StringUtils::format("fireBall_0%d.png",i);
			fireFileName.push_back(fileName);
		}
		auto fireAnimate = RoleAnimate::getinstance()->createAnimate(fireFileName,0.3,-1); 
		fireBall->runAction(fireAnimate);

	}
}

void BaseEnemy::bulletHit(){
	 GameScene * rScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	 HeroLayer * hLayer = dynamic_cast<HeroLayer *>(rScene->getHeroLayer());
	 auto hero = hLayer->getHero();
	if(m_state < 5){
		if (hero->getM_isFireUp() == true){
			m_state = m_state + 2;
			if (m_state > 5){
				m_state = 5;
			}
		}else{
			m_state++;
		}
		this->hurt();

		bulletHitTime = 0;
	}
}

void BaseEnemy::update(float t){

	if (m_state != 0 && m_state < 6){

		countToJump = 0;

		this->stopActionByTag(500);
		this->stopActionByTag(501);

		bulletHitTime += t;


		if(bulletHitTime > m_subscructStateTime){

			m_state--;
            this->m_isTaken = false;
			hurt();
			if (m_state == 0){
				this->getPhysicsBody()->setCollisionBitmask(22);
				this->getPhysicsBody()->setCategoryBitmask(1);
				this->getPhysicsBody()->setContactTestBitmask(6);
			}
			bulletHitTime = 0;
		}
	}else{
		this->removeAllChildrenWithCleanup(true);
		if (m_isMoving == false){
			m_isMoving = true;
			this->move();
		}
	}
}

void BaseEnemy::moveLeftAnimate(int imageMount){
	m_direction = 1;
	this->isJump = false;
	
	auto stm = RoleAnimate::getinstance()->getMoveLeftAnimate(m_type,imageMount,0.3,1);
	auto ml = MoveBy::create(1,Vec2(-m_speed,0));
	auto spa = Spawn::create(stm,ml,NULL);
	auto cf = CallFunc::create([=](){
		m_speed = 50;
		m_isSkilled = false;
	});
	auto seq = Sequence::create(spa,cf,NULL);
	seq->setTag(5001);
	this->runAction(seq);
}

void BaseEnemy::moveRightAnimate(int imageMount){
	m_direction = 2;
	this->isJump = false;
	
	auto stm = RoleAnimate::getinstance()->getMoveRightAnimate(m_type,imageMount,0.3,1);
	auto mr = MoveBy::create(1,Vec2(m_speed,0));
	auto spa = Spawn::create(stm,mr,NULL);
	auto cf = CallFunc::create([=](){	
		m_speed = 50;
		m_isSkilled = false;
	});
	auto seq = Sequence::create(spa,cf,NULL);
	seq->setTag(5002);
	this->runAction(seq);
}

void BaseEnemy::mySkill(){
	this->stopAllActions();
	if (m_direction == 3){
		this->getPhysicsBody()->setVelocity(Vec2(-220,300));
		std::vector<std::string>fireFileName;
		for (int i = 1; i < 5; i++){
			std::string fileName = StringUtils::format("enemy%dAttackLeft_0%d.png",m_type,i);
			fireFileName.push_back(fileName);
		}
		auto attackAni = RoleAnimate::getinstance()->createAnimate(fireFileName,0.25,1); 
		this->runAction(attackAni);
	}else if (m_direction == 4){
		this->getPhysicsBody()->setVelocity(Vec2(220,300));
		std::vector<std::string>fireFileName;
		for (int i = 1; i < 5; i++){
			std::string fileName = StringUtils::format("enemy%dAttackRight_0%d.png",m_type,i);
			fireFileName.push_back(fileName);
		}
		auto attackAni = RoleAnimate::getinstance()->createAnimate(fireFileName,0.25,1); 
		this->runAction(attackAni);
	}
}

void BaseEnemy::move(){
	
	countToJump++;
	if (countToJump == 5 + m_type % 10){
		m_isSkillReady = true;
		this->jump();
		countToJump = 0;
	}

	//左右边界的判断
	if (this->getBoundingBox().origin.x > 960-this->getBoundingBox().size.width -25){
		m_direction = 3;
	}else if (this->getBoundingBox().origin.x < 25){
		m_direction = 4;
	}
	if (m_direction == 3){
		this->moveLeftAnimate(4);
	}else if (m_direction == 4){
		this->moveRightAnimate(4);
	}else{
		m_direction = CCRANDOM_0_1() > 0.5 ? 1 : 2;
		if (m_direction == 1){
			this->moveLeftAnimate(4);
		}else if (m_direction == 2){
			this->moveRightAnimate(4);
		}
	}
}



void BaseEnemy::jump(){
	this->getPhysicsBody()->setVelocity(Vec2(0,530));
	this->getPhysicsBody()->setCategoryBitmask(0);
	this->scheduleOnce(schedule_selector(BaseEnemy::call),0.4);
	auto delay = DelayTime::create(2);
	auto cf = CallFunc::create([=](){isJump = false;});
	auto seq = Sequence::create(delay,cf,NULL);
	this->runAction(seq);
}

void BaseEnemy::call(float t){
	this->getPhysicsBody()->setCategoryBitmask(3);
}


void BaseEnemy::renewMove(float t){
	m_isMoving = false;
}

void BaseEnemy::die(){
	__NotificationCenter::getInstance()->postNotification("addscore",nullptr);
    auto dieani = RoleAnimate::getinstance()->createAmt("enemyExpoode_0%d.png", 6, 0.1, 1);
    auto cf = CCCallFunc::create([=](){
        this->removeFromParentAndCleanup(true);
    });
    this->runAction(Sequence::create(dieani,cf,NULL));
	this->setIsDie(true);
	AllVectors::getInstance()->deleteEnemy();
    
}
