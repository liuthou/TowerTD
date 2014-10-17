#ifndef  __MONSTERS_H
#define  __MONSTERS_H
#include "cocos2d.h"
#include "MonsterBase.h"
class Monsters
{
private:
	Monsters():nowNumber(0){}
	~Monsters(){}
	static Monsters *instance;
public:
	static Monsters *getInstance();
	//总数量
	CC_SYNTHESIZE_PASS_BY_REF(Vector<MonsterBase *>, monsterVector, MonsterVector);
	//现有数量
	CC_SYNTHESIZE(int, nowNumber, NowNumber);
	//增加怪物
	void addMonster(MonsterBase *monster);
	//删除怪物
	void clearMonster();
	//清除容器中所有怪物
	void clearAllMonster();
};
#endif