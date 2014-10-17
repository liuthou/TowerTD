#ifndef _FIRSTBOSS_H
#define _FIRSTBOSS_H
#include "BaseBoss.h"
class FirstBoss : public BaseBoss{
protected:
	int number;
	std::string myfileName;
	std::string myfileName_Die;
	int FrameNumber;
	int FrameNumberDie;
	int level;
public:
	static FirstBoss * create(int level);
	virtual bool initWithSpriteFrameName(int level);
	virtual void addFire(float t);
	virtual void onEnter();
	virtual void addFireStyle(float t);
	void bulletshape(float t);
	void bulletliner(float t);
	virtual void enemyFly();
	//使用xml随机产生boss
	void xmlCreate_boss();
	//死亡动画
	virtual ActionInterval * enemyDie();
	void enemyHurt();
	void SpeicalBullet(float t);
};
#endif // !_FIRSTBOSS_H
