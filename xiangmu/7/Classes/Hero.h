/************************************************************************/
/* 
需要实现的功能：
	属性：

		继承自BaseRole
		给基类传照片 
		m_hp//血量
		move()移动   
		m_speed速度
		m_attack攻击了（主角的攻击力为0）
		jump()跳  
		hurt()    
		die()   死亡  
		bornAnimate() 出生动画  
		dieRunAnimation()死亡动画    通过子类传过给基类照片来做死亡动画
		m_state 状态

		fire（）主角发射子弹

*/
/************************************************************************/
#ifndef __HERO_H_
#define __HERO_H_

#include "cocos2d.h"
#include "BaseRole.h"
#include "HeroBullet.h"



class BaseRole;
using namespace cocos2d;
enum HeroState
{
	alive = 0,
	died,
	addBulletAttack,
	addBulletRange
};
enum HeroDirection
{
	RIGHT = 1,
	LEFT
};
class Hero:public BaseRole
{
protected:
	HeroBullet * herobullet;
	Vec2 m_position;
	CC_SYNTHESIZE(bool,m_isRangeUp,M_isRangeUp);
	CC_SYNTHESIZE(bool,m_isFireUp,M_isFireUp);
public:
	CC_SYNTHESIZE(int, m_speed ,M_speed);
	CC_SYNTHESIZE(int, m_state ,M_state);
	CC_SYNTHESIZE(int, m_attack ,M_attack);
	CC_SYNTHESIZE(int, m_hp ,M_hp);
	CC_SYNTHESIZE(bool,m_isHurt,M_isHurt);
	CC_SYNTHESIZE(int,m_RollDirection,M_RollDirection);

/*	CC_SYNTHESIZE(int ,m_range,M_range);*/
	bool isTaking;
	Animate * m_moveLeftAnimate;
	Animate * m_moveRightAnimate;
	Animate * getRightAnimate();
	Animate * getLeftAnimate();
	CC_SYNTHESIZE(bool,isJump,IsJump);  //是否跳
	//设置主角方向
	CC_SYNTHESIZE(HeroDirection,direction,Direction);
	CC_SYNTHESIZE(bool,isFire,IsFire);
	virtual bool init(Vec2 position);


	void addBullet(int direction);//初始化子弹

	//主角的create方法 传文件名和位置创建主角
	static Hero * create(Vec2 position);

	//主角的开火方法
	virtual void addFire(Ref * sender);
	//主角的受伤方法
	virtual void hurt();

	//主角的出生动画
	//virtual void bornAnimate();

	//主角的行走方法
	virtual void heroMoveRight(Ref * sender);
	virtual void heroMoveLeft(Ref * sender);
	//主角的跳跃方法
	virtual void heroJump(Ref * sender);

	//主角的死亡方法
	virtual void die();
	void dieAnimate();
	//回复原来站立动画
	void Recover(Ref * sender);
	//站立动画
	void standAnimate(int direction);
	//主角的死亡动画
	//virtual void dieRunAnimation();

	//主角x坐标轴的加减
	void addX(float t);

	void subStractX(float t);
	//停止移动
	void stopMove(Ref * sender);


	void call(float t);
	int count;

	void createAnimate(std::string fileName);

	//void AddSpeed();
	float time;
	void harmLess(float t);

private:
	~Hero(){
		__NotificationCenter::getInstance()->removeAllObservers(this);
	}
};

#endif
