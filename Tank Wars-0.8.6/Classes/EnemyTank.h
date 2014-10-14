#ifndef __ENEMYTANK_H
#define __ENEMYTANK_H
#include "cocos2d.h"
#include "BaseTank.h"
using namespace cocos2d;
class EnemyTank:public BaseTank{
protected:
	Vec2 position;
	//�з�̹���ƶ�
	virtual void Enemymove(float t);
	//��̹�˵������ƶ��Ϳ���
	virtual void update(float t);
	virtual void playMoveEffect();
	void EnemyTestBounding(float t);
public:
//	virtual void move(moverect State);//��̹�˵��ƶ�����
	virtual bool initWithSpriteFrameName(std::string name,int hp,int speed,Vec2 position);
	virtual void fire();//��̹�˵Ŀ��𷽷�
	virtual  void runAnimate();
	CREATE_FUNC(EnemyTank);
	
};
#endif