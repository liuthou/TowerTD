#ifndef __ENEMYBASE_H
#define __ENEMYBASE_H
#include "cocos2d.h"

using namespace cocos2d;
enum MoveState{
	STOP,//停止
	UP,//上
	DOWN,//下
	LEFT,//左
	RIGHT//右
};
enum LifeState{
	NORMAL,//正常
	DIE//死亡
};
enum HurtState{
	NIRGUNA,//无属性  只会使血量减少
	FIRE,//火属性     使人物血量减少并且使人物变红
	ICE,//冰属性      使人物血量减少并且使人物减速
	WIND,//风属性     使人物血量减少并且使人物任意方向位移
	WIRE,//电属性     使人物血量减少并且使人物头上笼罩乌云  
}; 
class EnemyBase:public Sprite{
public:	
	EnemyBase();
	~EnemyBase();
	virtual void setMoveDirection()=0;//移动方法
	virtual void runAnimate()=0;//移动时的动画
	virtual void attackAnimate()=0;//攻击时的动画
	virtual void dieAnimate()=0;//死亡时的动画
	virtual void remove();//清除
	virtual void hurt(float attack,HurtState state)=0;//受伤
	virtual bool init(float hp,float speed);
	CC_SYNTHESIZE_READONLY(float,m_maxhp,Maxhp);//最大血量
	CC_SYNTHESIZE_READONLY(float,m_origspeed,OrgSpeed);//初始速度
	CC_SYNTHESIZE(float,m_curhp,Curhp);//当前血量
	CC_SYNTHESIZE_READONLY(float,m_money,Money);//金币值
	CC_SYNTHESIZE(float,m_speed,SPEED);//速度
    CC_SYNTHESIZE(bool,m_isstop,isStop);//是否是停止状态
	CC_SYNTHESIZE(HurtState,m_hurtproperty,Property)//受伤状态
	CC_SYNTHESIZE(MoveState,m_direction,Direction);//移动状态
	CC_SYNTHESIZE(LifeState,m_lifestate,Live);//是否存活
};
#endif