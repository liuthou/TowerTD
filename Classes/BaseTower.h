#ifndef __BASETOWER_H
#define __BASETOWER_H
#include "cocos2d.h"
#include "EnemyBase.h"
#include "GameBasic.h"
USING_NS_CC;

class BaseTower:public Sprite
{
public:
	int maxlevel;
	EnemyBase *soldier;//敌人
	Vec2 targetpoint;//目标点

	virtual bool init();	

	CC_SYNTHESIZE(float,scope,Scope);//塔的视线范围
	CC_SYNTHESIZE(int,curlevel,Curlevel);//当前等级
	CC_SYNTHESIZE(int,curgold,Curgold);//升级塔所需要的钱
	CC_SYNTHESIZE(int,goldvalue,Goldvalue);//变卖时的金币值	
	//CREATE_FUNC(BaseTower);
	BaseTower();
	~BaseTower();
	virtual void runAnimate(std::string name);//所有塔执行动画
	 
	virtual void checkNearestEnemy();//检测最近敌人
	virtual void stopAnm() = 0;//精致的动画
	virtual void Attack(float t)=0;//攻击方法
    virtual void postuplevel();//发送升级方法
	virtual void uplevel();//升级
    virtual void postDeleteTower();//发送移除
    virtual void removeTower(); //移除方法
		//塔的发射速度
	virtual void pauseAllTowers(); //暂停所有塔的动画
	//塔运行升级动画
	//virtual void updateTowersAnimation();
	Animation * animat;
	Animate *ani;
	std::string fileName;


protected:
	void setSpeed(float);
	void update(float dt);
	void changeState();
private:
	bool isAttackTime;
	bool isPreAttackTime;
	bool ischangeState;
	float speed;
};
#endif 