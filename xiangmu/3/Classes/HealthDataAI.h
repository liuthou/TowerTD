#ifndef  __HelthDataAI_H
#define  __HelthDataAI_H
#include "cocos2d.h"

enum DataLastDirection{        //枚举
	DATAUPLAST = 1,
	DATADOWNLAST = 2,
	DATALEFTLAST = 3,
	DATARIGHTLAST = 4,
};
class hHalthData;
using namespace cocos2d;
class HealthDataAI :public Node{
public:
	//AI类的init方法
	virtual bool init(HealthData* healthData,float dt);
	//重写Create方法
	static HealthDataAI* create(HealthData* healthData,float dt);
	//得到传入的敌人对象
	CC_SYNTHESIZE(HealthData*,healthData,HealthData);
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
	bool success;//成员变量 :敌人的移动是否成功
	HealthDataAI();
	~HealthDataAI();
};
#endif
