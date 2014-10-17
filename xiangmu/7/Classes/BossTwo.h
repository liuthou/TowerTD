#ifndef __BOSSTWO_H
#define __BOSSTWO_H
#include "cocos2d.h"
#include "BaseRole.h"
#include "Hero.h"
using namespace cocos2d;
class BossTwo:public BaseRole
{
public:
	int m_Hp;
	Size vsize;
	Hero * hero;
	CC_SYNTHESIZE(int,bossTwoDirection,bossTwoDirection);
	virtual bool init();
	CC_SYNTHESIZE(bool,isAttacked,IsAttacked);
	CREATE_FUNC(BossTwo);
private:
	
	void move(float t);
	void addvoice(float t);
	void skillOne();
	void skillTwo();
	void addSkill(float t);
	void update(float t);
	Vec2 m_position;
	void RollPkBossTwo(float t);
	void BossTwoHurt();
	void BossTwoDie();

	void _addChild(float t);
	bool isDie;
	void _callEnemy(Vec2 pos,int speed,int type,Size body,std::string name,int ai);
};
#endif // !__BOSSTWO_H
