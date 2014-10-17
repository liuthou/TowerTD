#include "MonsterManager.h"
#include "Enemy.h"
#include "MonsterAttributeConfType.h"
#include "MonsterAttribute.h"
#include "MainScene.h"
#include "EntityManager.h"
#include "MonsterDieEffect.h"
#include "ForwardLayer.h"
#include "MonsterManagerAttribute.h"
#include "MonsterManagerAttributeConfType.h"
USING_NS_CC;
bool MonsterManager::init(){
	if (!Node::init())
	{
		return false;
	}
	srand(time(0));
	return true;
}
void MonsterManager::onEnter(){
	Node::onEnter();
	this->initLevel();
	auto tmp = Director::getInstance()->getRunningScene()->getChildByName("wode");
}
void MonsterManager::initLevel(){
	auto managerattribute = MonsterManagerAttribute::getInstance();
	//初始化相关变量
	//第一轮出怪 
	wavecount=1;
	//第1波怪
	nowwaves = 0;
	//将来改成可配置的
	totalwaves = managerattribute->getWavesCount();
	for (int i = 0;i < totalwaves;i++)
	{
		//读取每一波的id,id从1开始
		int tmpmonster =  managerattribute->getIntAttribute(i+1,MonsterManagerAttributeConfigType::MonsterManager_MonsterID,1);
		monsters_id[i] = tmpmonster;
		//10s出一波
		int tmpdelaytimeperwave = managerattribute->getIntAttribute(i+1,MonsterManagerAttributeConfigType::MonsterManager_Delaytime,10);
		delaytimeperwave[i] = tmpdelaytimeperwave;
		//每一波5个怪
		int tmpmonsternumperwave = managerattribute->getIntAttribute(i+1,MonsterManagerAttributeConfigType::MonsterManager_Monsternum,5);
		monsternumperwave[i] = tmpmonsternumperwave;
	}
	int tmp_delaytime = delaytimeperwave[nowwaves];
	this->schedule(schedule_selector(MonsterManager::waveMonster),1,1,tmp_delaytime);
	
}
//出现一波怪物
void MonsterManager::waveMonster(float dt){
	//出一波怪,wave加1
	nowwaves++;
	log("wave monster:%d",nowwaves);
	//所有波次完成
	//难度翻倍
	if ( !(nowwaves < totalwaves))
	{
		this->unschedule(schedule_selector(MonsterManager::waveMonster));
		//难度翻倍
		if (wavecount<=5)
		{
			wavecount++;
		}
		//重新出第一波怪
		nowwaves = 1;
	}else{
		this->unschedule(schedule_selector(MonsterManager::waveMonster));
	}
	//计算当前波次出几个怪
	int tmp_numperwave = monsternumperwave[nowwaves]*wavecount;
	//每隔0.3s出一个怪,共出numperwave[waves]个
	this->schedule(schedule_selector(MonsterManager::createMonster),0.3,tmp_numperwave,0);
	//开始出下一波怪物
	int tmp_delaytime = delaytimeperwave[nowwaves];
	this->schedule(schedule_selector(MonsterManager::waveMonster) , 1 , 1 , tmp_delaytime);
}
//生成一个怪物
void MonsterManager::createMonster(float dt){
	log("create a monster!");
	log("monster id:%d now wave:%d" , monsters_id[nowwaves-1] , nowwaves);
	//出怪测试
	int tmp_id = monsters_id[nowwaves-1];
	auto tmp_monster = Enemy::create(tmp_id);
	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	auto mapLayer = mScene->getMapLayer();
	auto map = mapLayer->getTiledMap();
	tmp_monster->setPosition(monsterCreatePosition());//从地图上拿怪物出生位置
	mapLayer->addChild(tmp_monster);
	
	//绑定死亡加分函数
	if (monsteraddprice)
	{
		tmp_monster->setScoreFunc(monsteraddprice);
	}
	//绑定死亡特效函数
	tmp_monster->setDieEffectFunc(CC_CALLBACK_1(MonsterManager::monsterDieEffect,this));
	EntityManager::getInstance()->Monster.pushBack(tmp_monster);
}

void MonsterManager::setEarnScoreFunc(std::function<void(int)> monsteraddprice){
	this->monsteraddprice=monsteraddprice;
}
Vec2 MonsterManager::monsterCreatePosition(){
	
	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	MapLayer *mapLayer = mScene->getMapLayer();
	std::vector<Vec2> burnpoints = mapLayer->enemyBurnPosition();
	int pointsnum = burnpoints.size();
	int i = CCRANDOM_0_1()*pointsnum;
	Vec2 burnp = burnpoints.at(i);
	return burnp;
}
void MonsterManager::monsterDieEffect(Vec2 diepoint){
	auto scene = Director::getInstance()->getRunningScene();
	auto forwardlayer = dynamic_cast<ForwardLayer*>(scene->getChildByName("progressLayer"));
	auto gamelayer = dynamic_cast<GameLayer*>(scene->getChildByName("wode"));
	auto tmp_effect = MonsterDieEffect::create(diepoint,forwardlayer->getScoreLabelPosition());
	gamelayer->addChild(tmp_effect);
}