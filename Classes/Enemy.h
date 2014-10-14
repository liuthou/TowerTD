#ifndef __ENEMY_H
#define __ENEMY_H
#include "cocos2d.h"
#include "EnemyBase.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;
class Enemy:public EnemyBase{
private:
	Color3B m_orgcolor; 
	int m_pointCounter;
	std::string m_name;
	Sprite* m_hpBgSprite;
	Vec2 p1,p2;
	std::vector<Vec2>m_points;
public:
	Enemy();
	~Enemy();
	CC_SYNTHESIZE(bool,isIce,ISICE);//是否处于冰冻状态
	CC_SYNTHESIZE(bool,isFire,ISFIRE);//是否处于火烧状态
	CC_SYNTHESIZE(bool,isWind,ISWIND);//是否处于分吹状态
	CC_SYNTHESIZE(bool,isWire,ISWIRE);//是否处于雷电状态
	CC_SYNTHESIZE(ProgressTimer*,m_hpBar,HpBar);//血量条精灵
	CC_SYNTHESIZE(bool,m_enemySuccessful, EnemySuccessful);//
	static Enemy* create(std::string str,float hp,float speed,float money);
	virtual bool init(std::string str,float hp,float speed,float money);
	virtual void setMoveDirection();//设置移动方向
	virtual void runAnimate();//帧动画
	virtual void attackAnimate();//攻击动画
	virtual void dieAnimate();//死亡动画
	virtual void createHpBar();//创造血量框和血量条
	virtual void setHpBar();//设置血量条
	virtual void hurt(float attack,HurtState state);//受伤冰设置血量条
	virtual void move(float t);//移动方法
	virtual void iceEvent();//冰属性
	virtual void fireEvent();//火属性
	virtual void windEvent();//风属性
	virtual void wireEvent();//电属性
	virtual void iceAnimate();//冰属性被击动画
	virtual void fireAnimate();//火属性被击动画
	virtual void wireAnimate();//电属性被击动画
	virtual void moneyLable();//死亡金钱标题
	Vec2 currPoint();//当前点
	Vec2 nextPoint();//下一个点
};
#endif