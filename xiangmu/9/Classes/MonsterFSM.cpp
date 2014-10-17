#include "MonsterFSM.h"
#include "MonsterBase.h"

bool MonsterFSM::init(){
	auto center = __NotificationCenter::getInstance();
	center->addObserver(this,callfuncO_selector(MonsterFSM::RecvMonsterPartol),"partol",nullptr);
	center->addObserver(this,callfuncO_selector(MonsterFSM::RecvMonsterPursuit),"pursuit",nullptr);
	center->addObserver(this,callfuncO_selector(MonsterFSM::RecvMonsterAttack),"attack",nullptr);
	center->addObserver(this,callfuncO_selector(MonsterFSM::RecvMonsterHurt),"hurt",nullptr);
	center->addObserver(this,callfuncO_selector(MonsterFSM::RecvMonsterDie),"die",nullptr);
	return true;
}

MonsterFSM::~MonsterFSM(){
	auto center = __NotificationCenter::getInstance();
	center->removeObserver(this,"partol");
	center->removeObserver(this,"pursuit");
	center->removeObserver(this,"attack");
	center->removeObserver(this,"hurt");
	center->removeObserver(this,"die");
}

void MonsterFSM::RecvMonsterPartol(Ref* sender){
	auto m = dynamic_cast<MonsterBase *>(sender);
	m->monsterPartol();
}

void MonsterFSM::RecvMonsterPursuit(Ref* sender){
	auto m = static_cast<MonsterBase *>(sender);
	m->monsterPursuit();
}

void MonsterFSM::RecvMonsterAttack(Ref * sender)
{
	auto m = static_cast<MonsterBase *>(sender);
	m->monsterAttack();
}

void MonsterFSM::RecvMonsterHurt(Ref* sender){
	auto m = static_cast<MonsterBase *>(sender);
	m->monsterHurt(100);
}

void MonsterFSM::RecvMonsterDie(Ref* sender){
	auto m = static_cast<MonsterBase *>(sender);
	m->monsterDie();
}