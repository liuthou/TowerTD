#include "Monsters.h"

Monsters *Monsters::instance = nullptr;

Monsters *Monsters::getInstance()
{
	if (!instance){
		instance = new Monsters();
	}
	return instance;
}

void Monsters::addMonster(MonsterBase *monster)
{
	monsterVector.pushBack(monster);
	nowNumber += 1;
}

void Monsters::clearMonster()
{
	for (auto it = monsterVector.begin(); it != monsterVector.end();){
		if ((*it)->getMonsterDie() == true){
			it = monsterVector.erase(it);
			nowNumber--;
		}
		else{
			it++;
		}
	}
}

void Monsters::clearAllMonster()
{
	monsterVector.clear();
	nowNumber = 0;
}