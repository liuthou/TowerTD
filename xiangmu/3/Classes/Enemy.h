//create by 翟程远 2014 / 9 /19
//  base enemy 

#ifndef __ENTITY_H_
#define __ENTITY_H_
#include "cocos2d.h"
#include "GlobalInfo.h"
USING_NS_CC;

enum Directionbase{
	DOWNBASE = 0,
	LEFTBASE,
	RIGHTBASE,
	UPBASE,
};
class Bullet;
class Enemy:public Sprite{
public:
	static Enemy* create(int id);
	virtual bool init(int id);
	//被攻击
	void hurtMe(Bullet* bullet);
	void hurtMe(int attvalue);
	//攻击
	CC_SYNTHESIZE(int,hp,HP);
	//防御
	CC_SYNTHESIZE(int,def,Defence);
	//开火速度
	CC_SYNTHESIZE(int,firespeed,FireSpeed);
	//攻击范围
	CC_SYNTHESIZE(float,attrange,AttRange);
	//每一步移动距离
	CC_SYNTHESIZE(int,speed,Speed);
	//是否死亡
    CC_SYNTHESIZE(bool,isdie,Isdie);
	//设置敌人移动方向
	CC_SYNTHESIZE(int,direct,EnemyDir);
	CC_SYNTHESIZE(Vec2, target,Target);
	//子弹移动速度
	CC_SYNTHESIZE(int,buspeed,BuSpeed);
	//子弹攻击力
	CC_SYNTHESIZE(int,buattackValue,BuattackValue);
	//子弹名
	CC_SYNTHESIZE(std::string,buName,BuName );
	//怪物价格
	CC_SYNTHESIZE(int,price,Price);
	//被攻击特效
	CC_SYNTHESIZE(attackEffect,attackeffect,AttackEffect);
	//攻击特效
	CC_SYNTHESIZE(attackEffect,enemyatteffect,EnemyattEffect);
	virtual void remove();
	//void move(direction dir,float t);
	void fire(Sprite* tow);
	void die();
	//敌人移动方法
	virtual bool moveUp(float t);
	virtual bool moveDown(float t);
	virtual bool moveLeft(float t);
	virtual bool moveRight(float t);
	bool checkMove(Vec2 newpoint);
	//绑定死亡加分回调函数
	void setScoreFunc(std::function<void(int)> earnscore);
	//绑定死亡特效函数
	void setDieEffectFunc(std::function<void(Vec2 dieposition)> dieeffect);
protected:
	//持续掉血函数
	void intervalHurt(float dt);
	//冰霜效果(减速效果)(效果时间不叠加)
	void lowspeedEffect(int time);
	//冰冻效果(效果时间不叠加)
	void frozenEffect(int time);
	//火焰效果(加速,持续掉血)(效果时间不叠加)
	void fireEffect(int time);
	void removeLowspeedEffect(float dt);
	void removeFrozenEffect(float dt);
	void removeFireEffect(float dt);
protected:
	bool islowspeed;
	bool isfrozen;
	bool isfire;
	ParticleSystemQuad* snowparticle;
	ParticleSystemQuad* fireparticle;
	//敌人行走动画组
	Vector<Animate*> m_animates;
	void dieAnimate(std::string fileName);
	//死亡回调加分函数
	std::function<void(int)> earnscore;
	//死亡特效函数
	std::function<void(Vec2)> dieeffect;
	//加分函数是否绑定过
	bool getmoneyfuncbind;
	//临时变量,记录子弹攻击力,持续掉血时用
	int bulletattval;
	Enemy(){
		hp = 0;
		isdie = false;
		getmoneyfuncbind = false;
		speed = STEP;
		def = 0;
		firespeed = 0;
		attrange = 0;
		//初始化状态
		islowspeed = false;
		isfrozen = false;
		isfire = false;
		attackeffect.firetime = 0;
		attackeffect.frozentime = 0;
		attackeffect.lowspeedtime = 0;
		enemyatteffect.firetime = 0;
		enemyatteffect.frozentime = 0;
		enemyatteffect.lowspeedtime = 0;
		snowparticle = nullptr;
		fireparticle = nullptr;
		bulletattval = 0;
	};
};
#endif