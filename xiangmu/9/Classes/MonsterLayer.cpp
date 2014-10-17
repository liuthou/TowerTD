#include "MonsterLayer.h"
#include "MonsterSoldier.h"
#include "MonsterGoblin.h"
#include "MonsterBoss.h"
#include "Monsters.h"
#include "MonsterFSM.h"
#include "MonsterLayer.h"

MonsterLayer *MonsterLayer::create(std::string filename)
{
	auto monster = new MonsterLayer();
	if (monster && monster->init(filename)){
		monster->autorelease();
		return monster;
	}
	else{
		CC_SAFE_DELETE(monster);
		return nullptr;
	}
}

bool MonsterLayer::init(std::string filename){
	if (!Layer::init()){
		return false;
	}
	_fileName = filename;
	schedule(schedule_selector(MonsterLayer::createMonster),1);
	//¼ÓÈë×´Ì¬»ú
	addChild(MonsterFSM::create());
	return true;
}

void MonsterLayer::createMonster(float t)
{
	auto mon = Monsters::getInstance();
	if(!_oneBoss)
	{
		_oneBoss = true;
	   MonsterBoss *boos = MonsterBoss::create(_fileName);
        boos->setScale(2.0f);
	   mon->addMonster(boos);
	}
	if (mon->getNowNumber() < 15){
		MonsterSoldier *soldier;
		MonsterGoblin *goblin;
		float t = CCRANDOM_0_1();
		if (t < 0.5){
			soldier = MonsterSoldier::create(_fileName);
			mon->addMonster(soldier);
		}else if (t >= 0.5){
			goblin = MonsterGoblin::create(_fileName);
			mon->addMonster(goblin);
		}
	}
}

void MonsterLayer::stopUnschedu()
{
	unschedule(schedule_selector(MonsterLayer::createMonster));
}

MonsterLayer::~MonsterLayer()
{
	Monsters * monsters = Monsters::getInstance();
	monsters->clearAllMonster();
}

