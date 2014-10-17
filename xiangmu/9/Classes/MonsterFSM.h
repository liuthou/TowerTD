#ifndef __MONSTERFSM_H
#define __MONSTERFSM_H
#include "cocos2d.h"
using namespace cocos2d;
class MonsterFSM:public Node
{
public:
	CREATE_FUNC(MonsterFSM);
	virtual bool init();
	~MonsterFSM();
	void changeMonsterState();
private:
	void RecvMonsterPartol(Ref* sender);
	void RecvMonsterPursuit(Ref* sender);
	void RecvMonsterAttack(Ref * sender);
	void RecvMonsterHurt(Ref* sender);
	void RecvMonsterDie(Ref* sender);
};
#endif