#include "BossThree.h"
#include "RoleAnimate.h"
#include "GameScene.h"
#include "GetEnemyInfoFromXML.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool BossThree::init(){
	if (!Sprite::initWithSpriteFrameName("boss3MoveLeft_01.png")){
		return false;
	}
	m_countToSkill = 0;
	m_direction = 0;
	m_skillType = 0;
	m_hp = 3;

	m_rollPosition = Vec2(0,0);
	/*isDie = false;*/
	this->setPosition(700,200);

	this->schedule(schedule_selector(BossThree::move),1.01);
	this->schedule(schedule_selector(BossThree::prepareForSkills),1);
	this->schedule(schedule_selector(BossThree::heroPKBoss));
	auto e = AllVectors::getInstance()->getEfmusic();
	if (!e)
	{
		SimpleAudioEngine::getInstance()->playEffect("boss3Born.mp3");
	}
	

	return true;

}

/*

void BossThree::_callEnemy(Vec2 pos,int speed,int type,Size body,std::string name,int ai){
	auto enemy1 = BaseEnemy::create(name,speed,type,pos,body,ai);

	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto enemylayer = scene->getEnemyLayer();
	enemy1->setTag(1002);
	enemylayer->addChild(enemy1);

	AllVectors::getInstance()->addEnemy(enemy1);
}
void BossThree::_addChild(float t){
	auto allEnemys = AllVectors::getInstance()->getEnemiesVector();

	if (allEnemys.size() < 2 && isDie == false){  //如果Boss没有死 并且剩余的小鬼 数量小于 3 个
		auto allEnemyPos = GetEnemyInfoFromXML::getinstance()->getAllEnemyPosition();
		//速度信息
		auto allEnemySpeed = GetEnemyInfoFromXML::getinstance()->getAllEnemySpeed();
		//类型信息
		auto allEnemyType = GetEnemyInfoFromXML::getinstance()->getAllEnemyType();
		//刚体大小信息
		auto allEnemyBody = GetEnemyInfoFromXML::getinstance()->getAllEnemyBody();
		//名字信息
		auto allEnemyName = GetEnemyInfoFromXML::getinstance()->getAllenemyName();
		//AI信息
		auto allEnemyAI = GetEnemyInfoFromXML::getinstance()->getAllEnemyAI();

		srand(time(0));

		for (int i = 0;i < 2;i++){
			int randNUm =(int)(CCRANDOM_0_1()*4);
			Vec2 m_pos = allEnemyPos[randNUm];
			int m_speed = allEnemySpeed[randNUm];
			int m_type = allEnemyType[randNUm];
			Size m_body = allEnemyBody[randNUm];
			std::string m_name = allEnemyName[randNUm];
			int m_AI = allEnemyAI[randNUm];
			_callEnemy(m_pos,m_speed,m_type,m_body,m_name,m_AI);
		}
	}
}

*/

void BossThree::moveLeftAnimate(){
	m_direction = 1;
	
	auto moveAmt = RoleAnimate::getinstance()->createAmt("boss3MoveLeft_0%d.png",4,0.25,1);
	this->runAction(moveAmt);

	auto ml = MoveBy::create(1,Vec2(-50,0));
	auto spa = Spawn::create(moveAmt,ml,NULL);
	/*auto cf = CallFunc::create([=](){
		m_isSkilled = false;
	});
	auto seq = Sequence::create(spa,cf,NULL);
	seq->setTag(11);*/
	spa->setTag(11);
	this->runAction(spa);
}

void BossThree::moveRightAnimate(){
	m_direction = 2;

	auto moveAmt = RoleAnimate::getinstance()->createAmt("boss3MoveRight_0%d.png",4,0.25,1);
	this->runAction(moveAmt);

	auto ml = MoveBy::create(1,Vec2(50,0));
	auto spa = Spawn::create(moveAmt,ml,NULL);
	/*auto cf = CallFunc::create([=](){
		m_isSkilled = false;
	});
	auto seq = Sequence::create(spa,cf,NULL);
	seq->setTag(11);*/
	spa->setTag(12);
	this->runAction(spa);
}

void BossThree::prepareForSkills(float t){
	m_countToSkill++;
	auto ev = AllVectors::getInstance()->getEnemiesVector();
	float tt = m_countToSkill % 2 + 0.21;
	if (ev.size() < 3){
		m_skillType = 1;
		if (m_direction == 1){
			m_direction = 5;
		}else if (m_direction == 2){
			m_direction = 6;
		}
	}else if (m_countToSkill == 15){
		m_skillType = 2;
		if (m_direction == 1){
			m_direction = 5;
		}else if (m_direction == 2){
			m_direction = 6;
		}
	}else if (m_countToSkill == 30){
		m_skillType = 3;
		if (m_direction == 1){
			m_direction = 5;
		}else if (m_direction == 2){
			m_direction = 6;
		}
		m_countToSkill = 0;
	}
}

void BossThree::move(float t){

	//左右边界的判断
	if (this->getBoundingBox().origin.x > 960 - this->getBoundingBox().size.width - 25){
		m_direction = 3;
	}else if (this->getBoundingBox().origin.x < 25){
		m_direction = 4;
	}
	if (m_direction == 5 || m_direction == 6){
		if (m_skillType == 2){
			this->callFireBall();
		}else if (m_skillType == 1){
			this->callEnemy();
		}else if (m_skillType == 3){
			this->callFire();
		}else if (m_skillType == 0){
			return;
		}
	}else if (m_direction == 3){
		this->moveLeftAnimate();
	}else if (m_direction == 4){
		this->moveRightAnimate();
	}else{
		m_direction = CCRANDOM_0_1() > 0.5 ? 1 : 2;
		if (m_direction == 1){
			this->moveLeftAnimate();
		}else if (m_direction == 2){
			this->moveRightAnimate();
		}
	}
}

void BossThree::callEnemy(){
	GameScene * rScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto eLayer = dynamic_cast<EnemyLayer *>(rScene->getEnemyLayer());

	m_skillType = 0;
	if (m_direction == 5){
		auto callEnemyAmt = RoleAnimate::getinstance()->createAmt("boss3ToCallEnemyLeft_0%d.png",4,0.48,1);
		this->runAction(callEnemyAmt);
	}else if (m_direction == 6){
		auto callEnemyAmt = RoleAnimate::getinstance()->createAmt("boss3ToCallEnemyRight_0%d.png",4,0.48,1);
		this->runAction(callEnemyAmt);
	}

	SimpleAudioEngine::getInstance()->playEffect("boss3Call.wav");

	auto aniSp1 = Sprite::createWithSpriteFrameName("boss3CallEnemyLeft_01.png");
	aniSp1->setScale(1.2);
	aniSp1->setPosition(this->getContentSize().width / 2 - 70,80);
	this->addChild(aniSp1);

	auto callEnemyAmt1 = RoleAnimate::getinstance()->createAmt("boss3CallEnemyLeft_%02d.png",13,0.15,1);
	auto cf1 = CallFunc::create([=](){
		aniSp1->removeFromParentAndCleanup(true);
		float x = this->getPositionX();
		auto rate1 = CCRANDOM_0_1()* 3;
		auto rate2 = CCRANDOM_0_1()* 3;
		if (rate1 >= 0 && rate1 < 1){
			eLayer->add(Vec2(x - 70,120),50,41,Size(55,70),"enemy41Hurt_01.png",1);
		}else if (rate1 >= 1 && rate1 < 2){
			eLayer->add(Vec2(x - 70,120),50,42,Size(55,70),"enemy42Hurt_01.png",8);
		}else if (rate1 >= 2 && rate1 <= 3){
			eLayer->add(Vec2(x - 70,120),50,43,Size(55,70),"enemy43Hurt_01.png",7);
		}
		if (rate2 >= 0 && rate2 < 1){
			eLayer->add(Vec2(x - 70,120),50,44,Size(55,70),"enemy44Hurt_01.png",2);
		}else if (rate2 >= 1 && rate2 < 2){
			eLayer->add(Vec2(x - 70,120),50,45,Size(55,70),"enemy45Hurt_01.png",4);
		}else if (rate2 >= 2 && rate2 <= 3){
			eLayer->add(Vec2(x - 70,120),50,46,Size(55,70),"enemy46Hurt_01.png",6);
		}

		m_direction = 100;
	});
	auto seq1 = Sequence::create(callEnemyAmt1,cf1,NULL);
	aniSp1->runAction(seq1);

	auto aniSp2 = Sprite::createWithSpriteFrameName("boss3CallEnemyRight_01.png");
	aniSp2->setScale(1.2);
	aniSp2->setPosition(this->getContentSize().width / 2 + 100,80);
	this->addChild(aniSp2);

	auto callEnemyAmt2 = RoleAnimate::getinstance()->createAmt("boss3CallEnemyRight_%02d.png",13,0.15,1);
	auto cf2 = CallFunc::create([=](){aniSp2->removeFromParentAndCleanup(true);});
	auto seq2 = Sequence::create(callEnemyAmt2,cf2,NULL);
	aniSp2->runAction(seq2);
}

void BossThree::callFireBall(){
	m_skillType = 0;
	GameScene * rScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	HeroLayer * hlayer = dynamic_cast<HeroLayer *>(rScene->getHeroLayer());
	auto hero = hlayer->getHero();

	Animate * callFireBallAmt = NULL;
	if (m_direction == 5){
		callFireBallAmt = RoleAnimate::getinstance()->createAmt("boss3CallFireBallLeft_0%d.png",4,0.48,1);
	}else if (m_direction == 6){
		callFireBallAmt = RoleAnimate::getinstance()->createAmt("boss3CallFireBallRight_0%d.png",4,0.48,1);
	}
	this->runAction(callFireBallAmt);

	auto e = AllVectors::getInstance()->getEfmusic();
	if (!e)
	{
		SimpleAudioEngine::getInstance()->playEffect("boss3Call.wav");
	}

	auto aniSp1 = Sprite::createWithSpriteFrameName("boss3CallFireBall_01.png");
	aniSp1->setScale(1.5);
	aniSp1->setPosition(hero->getPositionX(),40);
	hlayer->addChild(aniSp1);

	auto callFireBallAmt1 = RoleAnimate::getinstance()->createAmt("boss3CallFireBall_0%d.png",5,0.15,-1);
	aniSp1->runAction(callFireBallAmt1);
		
	auto aniSp2 = Sprite::createWithSpriteFrameName("boss3FireBall_01.png");
	aniSp2->setPosition(hero->getPositionX(),800);
	aniSp2->setName("fireBall");
	hlayer->addChild(aniSp2);
	
	auto fireBallAmt = RoleAnimate::getinstance()->createAmt("boss3FireBall_0%d.png",4,0.1,1);
	auto mb = MoveBy::create(2,Vec2(0,-800));
	auto cf2 = CallFunc::create([=](){
		aniSp1->removeFromParentAndCleanup(true);
		aniSp2->removeFromParentAndCleanup(true);
		m_direction = 100;
	});
	auto seq2 = Sequence::create(mb,cf2,NULL); 
	auto spa = Spawn::create(fireBallAmt,seq2,NULL);
	
	aniSp2->runAction(spa);
	
}

void BossThree::callFire(){
	m_skillType = 0;
	GameScene * rScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	HeroLayer * hlayer = dynamic_cast<HeroLayer *>(rScene->getHeroLayer());
	Animate * callFireAmt = NULL;

	auto e = AllVectors::getInstance()->getEfmusic();
	if (!e)
	{
		SimpleAudioEngine::getInstance()->playEffect("boss3Call.wav");
	}
	if (m_direction == 5){
		callFireAmt = RoleAnimate::getinstance()->createAmt("boss3CallFireLeft_0%d.png",4,0.48,2);
	}else if (m_direction == 6){
		callFireAmt = RoleAnimate::getinstance()->createAmt("boss3CallFireRight_0%d.png",4,0.48,2);
	}
	auto cf1 = CallFunc::create([=](){
		auto aniSp1 = Sprite::create();
		aniSp1->setScale(2);
		aniSp1->setPosition(480,80);
		aniSp1->setName("fire");
		hlayer->addChild(aniSp1);

		auto callFireAmt = RoleAnimate::getinstance()->createAmt("boss3CallFire_0%d.png",7,0.25,1);
		auto cf = CallFunc::create([=](){
			aniSp1->removeFromParentAndCleanup(true);
			m_direction = 100;
		});
		auto seq = Sequence::create(callFireAmt,cf,NULL);
		aniSp1->runAction(seq);
	});
	auto seq1 = Sequence::create(callFireAmt,cf1,NULL);
	this->runAction(seq1);
}

void BossThree::heroPKBoss(float t){
	GameScene * rScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	HeroLayer * hLayer = dynamic_cast<HeroLayer *>(rScene->getHeroLayer());
	auto eLayer = dynamic_cast<EnemyLayer *>(rScene->getEnemyLayer());
	auto hero = hLayer->getHero();
	auto roll = eLayer->getChildByName("roll");
	auto fireBall = hLayer->getChildByName("fireBall");
	auto fire = hLayer->getChildByName("fire");

	if (this->getBoundingBox().containsPoint(hero->getPosition()) && hero->getM_isHurt() == false){
		hero->setM_isHurt(true);
		hero->hurt();
	}
	if (fireBall != NULL ){
		if (fireBall->getBoundingBox().containsPoint(hero->getPosition()) && hero->getM_isHurt() == false){
			hero->setM_isHurt(true);
			hero->hurt();
		}
	}
	if (fire != NULL){
		if (fire->getBoundingBox().containsPoint(hero->getPosition()) && hero->getM_isHurt() == false){
			hero->setM_isHurt(true);
			hero->hurt();
		}
	}
	
	if (roll != NULL){
		if (this->getBoundingBox().containsPoint(roll->getPosition())){
			this->stopAllActions();
			auto scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
			auto enemylayer = dynamic_cast<EnemyLayer *>(scene->getEnemyLayer());
			enemylayer->setRollTime(3);
			this->boss3hurt();
		}
	}
	
	
}

void BossThree::boss3die(){
	if (this->getPositionX() - m_rollPosition.x > 0){
		this->unschedule(schedule_selector(BossThree::move));
		auto dieAmt = RoleAnimate::getinstance()->createAmt("boss3DieLeft_0%d.png",4,0.2,1);
		this->runAction(dieAmt);
		this->removeFromParentAndCleanup(true);
	}else{
		auto dieAmt = RoleAnimate::getinstance()->createAmt("boss3DieRight_0%d.png",4,0.2,1);
		this->runAction(dieAmt);
		this->removeFromParentAndCleanup(true);
	}
}

void BossThree::boss3hurt(){
	m_hp--;
	auto e = AllVectors::getInstance()->getEfmusic();
	if (!e)
	{
		SimpleAudioEngine::getInstance()->playEffect("boss3Hurt.wav");
	}
	if (this->getPositionX() - m_rollPosition.x > 0){
		auto hurtAmt = RoleAnimate::getinstance()->createAmt("boss3DieLeft_0%d.png",2,0.3,1);
		this->runAction(hurtAmt);
	}else{
		auto hurtAmt = RoleAnimate::getinstance()->createAmt("boss3DieRight_0%d.png",2,0.3,1);
		this->runAction(hurtAmt);
	}
	if(m_hp <= 0){
		this->boss3die();
	}
}