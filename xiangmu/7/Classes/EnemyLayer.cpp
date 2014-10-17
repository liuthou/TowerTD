#include "EnemyLayer.h"
#include "BaseEnemy.h"
#include "AllVectors.h"
#include "GetEnemyInfoFromXML.h"
#include "BossTwo.h"
#include "BossThree.h"
#include "BossFour.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "GameScene.h"

using namespace ui;
using namespace cocostudio;

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


using namespace ui;
using namespace cocostudio;

Scene *EnemyLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = EnemyLayer::create();
	scene->addChild(layer);
	return scene;
}

bool EnemyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	m_curGuna = NULL;
	m_time = 60;

	rolltime = 0;
	roll = NULL;

	this->scheduleOnce(schedule_selector(EnemyLayer::addEnemy),0.5);

	this->schedule(schedule_selector(EnemyLayer::addTime),1,-1,2);
	this->scheduleOnce(schedule_selector(EnemyLayer::addLabel),1);
	this->schedule(schedule_selector(EnemyLayer::update));

	return true;

}

void EnemyLayer::reload(){
	m_time = 61;
	this->schedule(schedule_selector(EnemyLayer::addTime),1,-1,2);
}

void EnemyLayer::resetLabel(float t){
	time_label->setString("30");
}

Label *EnemyLayer::getLabel(){
	return time_label;
}

void EnemyLayer::addLabel(float t){
	time_label = Label::createWithSystemFont("","Arial",30);
	std::string ti = StringUtils::format("%d s",m_time);
	time_label->setString(ti);
	time_label->setColor(Color3B(120,120,120));
	time_label->setPosition(Vec2(650,610));
	this->addChild(time_label);
}

void EnemyLayer::addRoll(Vec2 position){
	roll = Sprite::createWithSpriteFrameName("fireBall_01.png");
	roll->setPosition(position);
	roll->setTag(1000);
	roll->setScale(0.5);
	roll->setName("roll");
	this->addChild(roll);

	//添加缸体
	roll->setPhysicsBody(PhysicsBody::createCircle(30));
	roll->getPhysicsBody()->setCategoryBitmask(2);
	roll->getPhysicsBody()->setCollisionBitmask(25);
	roll->getPhysicsBody()->setContactTestBitmask(25);
	roll->getPhysicsBody()->setRotationEnable(true);
	roll->getPhysicsBody()->getShape(0)->setRestitution(1);
}

void EnemyLayer::update(float t){

	if(roll == nullptr){
		return;
	}
	rolltime += t;
	if(this->getRollTime() >= 0.5){
		this->unschedule(schedule_selector(EnemyLayer::update));
		if(roll == nullptr){
			return;
		}
		Vec2 rPosi = roll->getPosition();
		auto sp = Sprite::create();
		sp->setPosition(rPosi);
		this->addChild(sp);
		roll->removeFromParentAndCleanup(true);
		auto eAmt = RoleAnimate::getinstance()->createAmt("RollExplode_0%d.png",6,0.2,1);
		auto cf = CallFunc::create([=](){
			sp->removeFromParentAndCleanup(true);
		});
		auto cf1 = CCCallFunc::create([=](){
			this->schedule(schedule_selector(EnemyLayer::update));
			this->setRollTime(0);
			roll = nullptr;
		});
		auto seq = Sequence::create(eAmt,cf1,cf,NULL);
		sp->runAction(seq);
	}
}



void EnemyLayer::addEnemy(float t){
	//总关数
	m_totleGuan = Label::createWithSystemFont("/15","Arial",30);
	m_totleGuan->setPosition(Vec2(485,610));
	m_totleGuan->setColor(Color3B(120,120,120));
	this->addChild(m_totleGuan,5);
	if (m_curGuna){
		m_curGuna->removeFromParentAndCleanup(true);
	}
	
	//当前关
	int ID = UserDefault::getInstance()->getIntegerForKey("ID",1);
	std::string _ID = StringUtils::format("%d",ID);
	m_curGuna = Label::createWithSystemFont(_ID,"Arial",30);
	m_curGuna->setPosition(Vec2(450,610));
	m_curGuna->setColor(Color3B(120,120,120));
	this->addChild(m_curGuna,5);


	if (ID == 5){
		BossFour *boss4 = BossFour::create();
		this->addChild(boss4);
	}
	if (ID == 15){
		BossThree *boss3 = BossThree::create();
		this->addChild(boss3,9);
	}
    if (ID == 10){
        BossTwo *boss2 = BossTwo::create();
		boss2->setTag(3000);
        this->addChild(boss2,9);
    }
	
	//========================================获取所有小鬼的信息================================================
	//位置信息

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

	for (int i =0;i<allEnemySpeed.size();i++){
		m_pos = allEnemyPos[i];
		m_speed = allEnemySpeed[i];
		m_type = allEnemyType[i];
		m_body = allEnemyBody[i];
		m_name = allEnemyName[i];
		m_AI = allEnemyAI[i];
		add(m_pos,m_speed,m_type,m_body,m_name,m_AI);
	}
}

void EnemyLayer::addTime(float t){
	m_time--;
	
	auto allenemy = AllVectors::getInstance()->getEnemiesVector();

	if (allenemy.size() == 0)
	{
		this->unschedule(schedule_selector(EnemyLayer::addTime));
	}

	if (m_time == -1)
	{
		auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
		auto heroLayer = scene->getHeroLayer();
		auto hero = (Hero *)heroLayer->getChildByName("hero");
		hero->hurt();
		m_time = 60;

	}
	
		std::string ti = StringUtils::format("%d s",m_time);
		time_label->setString(ti);
	
}

void EnemyLayer::add(Vec2 pos,int speed,int type,Size body,std::string name,int AI){
	
	auto enemy1 = BaseEnemy::create(name,speed,type,pos,body,AI);
	enemy1->setTag(1002);
	this->addChild(enemy1);
	//将产生的小鬼放在小鬼的集合中
	AllVectors::getInstance()->addEnemy(enemy1);

}