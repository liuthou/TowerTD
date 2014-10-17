#ifndef  __EnemyAI_H
#define  __EnemyAI_H
#include "cocos2d.h"
class Enemy;
enum LastDirection{        //枚举
	UPLAST = 1,
	DOWNLAST = 2,
	LEFTLAST = 3,
	RIGHTLAST = 4,
};
class Enemy;
using namespace cocos2d;
class EnemyAI :public Node{
public:
	//AI类的init方法
	virtual bool init(Enemy* enemy,float dt);
	//重写Create方法
	static EnemyAI* create(Enemy* enemy,float dt);
	//得到传入的敌人对象
	CC_SYNTHESIZE(Enemy*,enemy,Enemy);
	//敌人上一次运动的方向
	CC_SYNTHESIZE(int,dir,LastDirection);
	//移动时间
	CC_SYNTHESIZE(float,steptime,StepTime);
	//成员变量success的赋值
	void setMoveSuccess(bool success){
		this->success=success;
	}
	//是否移动成功
	bool isMoveSuccess(){
		return success;
	}
	//得到当前移动对象的移动方向
	virtual void getDirection(float dt);
	//下一次移动位置和上一次移动方向
	void nextStepandOldDirection(float dt);
	//下一次移动位置和新的移动方向
	void nextStepandNewDirection(float dt);
	//敌人的自动开火

protected:
	void checkfire(float t);
	bool success;//成员变量 :敌人的移动是否成功
	EnemyAI();
	~EnemyAI();
};
#endif
