#ifndef __BASEHEROES__
#define __BASEHEROES__

#include "Conf.h"


class BaseHeroes : public cocos2d::Sprite
{
protected:
	CC_SYNTHESIZE(bool, isProtect, IsProtect);
	CC_SYNTHESIZE(std::string,_fileName,FileName);

	ActionInterval * aniFly;

	virtual void fly() = 0;

	Vec2 position;
	//发射子弹
	void addFire(float t);
	//设置回调发射子弹
	virtual void onEnter();
	//死亡方法
	virtual void die() = 0;
	//受伤害动画
	virtual ActionInterval * hurtAnimate() = 0;

	virtual ActionInterval * flyAnimate() = 0;

	virtual void protect();
public:
	//初始化方法
	virtual bool initWithSpriteFrameName(std::string fileName);
	//设置子弹等级
	CC_SYNTHESIZE(float, _bulletLevel,BulletLevel);
	//设置子弹是否发射的属性
	CC_SYNTHESIZE(bool,_isAddFire,IsAddFire);
	//受伤害方法
	virtual void hurt();

	Rect getBox() const;
};

#endif