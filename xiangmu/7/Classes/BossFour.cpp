#include "BossFour.h"
#include "RoleAnimate.h"
#include "AllVectors.h"
#include "GetEnemyInfoFromXML.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool BossFour::init(){
	if (!Sprite::init()){
		return false;
	}

	m_dir = MOVELEFT;		//设置默认的方向是向左
	m_bossIsHurt = false;
	hp = 300;
	isDie = false;

	this->setPosition(Vec2(450,165));

	this->schedule(schedule_selector(BossFour::move),2,-1,1);	//每个 2秒调用 move方法
	this->scheduleOnce(schedule_selector(BossFour::bornAnimate),0);
	this->schedule(schedule_selector(BossFour::_update),2,-1,0);
	this->schedule(schedule_selector(BossFour::fireBallPKBoss));
	this->setVisible(false);

	return true;
    
}
void BossFour::_update(float t){
	
	auto allEnemys = AllVectors::getInstance()->getEnemiesVector();
	//log("%d",allEnemys.size());
	if (allEnemys.size() <= 3 && isDie == false){  //如果Boss没有死 并且剩余的小鬼 数量小于 3 个
		auto e = AllVectors::getInstance()->getEfmusic();
		if (!e)
		{
			SimpleAudioEngine::getInstance()->playEffect("Boss4callenemy.wav");
		}
		
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
			callEnemy(m_pos,m_speed,m_type,m_body,m_name,m_AI);
		}
	}
}
//获取 Boss的状态
bool BossFour::getState(){
	return isDie;
}


void BossFour::callEnemy(Vec2 pos,int speed,int type,Size body,std::string name,int ai){		//招小怪

	auto enemy1 = BaseEnemy::create(name,speed,type,pos,body,ai);

	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto enemylayer = scene->getEnemyLayer();
	enemy1->setTag(1002);
	enemylayer->addChild(enemy1);

	AllVectors::getInstance()->addEnemy(enemy1);

}
void BossFour::move(float t){
	m_dir = CCRANDOM_0_1() > 0.5 ? direction::MOVELEFT : direction::MOVERIGHT;
	if (m_dir == MOVELEFT){
		this->moveLeftAnimate();
	}else{
		this->moveRightAnimate();//运行向右的动画
	}
	if (this->getPositionX() >= 640){//边界检测
        moveLeftAnimate();
	}
	if (this->getPositionX()<= 300){
        moveRightAnimate();
	}
}
void BossFour::moveLeftAnimate(){ //向左移动动画
	m_dir = MOVELEFT;
	//站立着运行动画
	auto moveAni = RoleAnimate::getinstance()->createAmt("boss1MoveLeft_0%d.png",4,0.5,1);
    moveAni->setTag(1000);
	this->runAction(moveAni);
	//移动运行动画
	auto moveleft = MoveBy::create(2,Vec2(-70,0));
	auto spa = Spawn::create(moveAni,moveleft,NULL);

	this->runAction(spa);

}

void BossFour::moveRightAnimate(){	//向右移动动画
	m_dir = MOVERIGHT;
	//站立着运行动画
	auto moveAni = RoleAnimate::getinstance()->createAmt("boss1MoveRight_0%d.png",4,0.5,1);
    moveAni->setTag(2000);
	this->runAction(moveAni);
	//
	auto moveleft = MoveBy::create(2,Vec2(80,0));
	auto spa = Spawn::create(moveAni,moveleft,NULL);

	this->runAction(spa);

}

void BossFour::bornAnimate(float t){		//出生动画
	
	auto bornAni = RoleAnimate::getinstance()->createAmt("born0%d.png",14,0.1,1);
	this->runAction(bornAni);
	this->setVisible(true);
}

void BossFour::hurtAnimate(){		//受伤动画
	Animate *ani;
    //this->stopActionByTag(1000);
    //this->stopActionByTag(2000);
	if (m_dir == MOVELEFT){
		ani = RoleAnimate::getinstance()->createAmt("boss1HurtLeft_0%d.png",4,0.5,1);
	}else{
		ani = RoleAnimate::getinstance()->createAmt("boss1HurtRight_0%d.png",4,0.5,1);
	}
	this->runAction(ani);
}

void BossFour::dieAnimate(){		//死亡动画
	Animate *ani;
	if (m_dir == MOVELEFT){
		ani = RoleAnimate::getinstance()->createAmt("boss1DieLeft_0%d.png",4,0.5,1);
	}else{
		ani = RoleAnimate::getinstance()->createAmt("boss1DieRight_0%d.png",4,0.5,1);
	}
	this->runAction(ani);
}

void BossFour::hurt(){
	m_bossIsHurt = true;
	hurtAnimate();
	this->hp -= 100;
	if (hp <= 0 ){
		isDie = true;
		die();
    }
}

void BossFour::die(){
	dieAnimate();
	auto remo = CCCallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
    this->runAction(Sequence::create(DelayTime::create(2),remo,NULL));

}

void BossFour::fireBallPKBoss(float t){
	//获润兴的场景
	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	//获取 敌人层
	auto enemylayer = scene->getEnemyLayer();

	auto roll = enemylayer->getChildByName("roll");

	if (roll != NULL){
		if ( (roll->getPositionY() < this->getPositionY()-40) &&this->getBoundingBox().containsPoint(roll->getPosition())){
            this->hurt();
			enemylayer->setRollTime(3);
		}
	}

}

	

