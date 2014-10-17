#ifndef __ELITE_SHADOW_H_
#define __ELITE_SHADOW_H_
#include "Conf.h"
#include "BaseElite.h"
#define kElite_ShadowFileName "EnemyCommon_two1.png"
#define kElite_ShadowSpeed 100
#define kElite_ShadowHp 100
class Elite_Shadow:public BaseElite
{
protected:
	//∑…––∂Øª≠
	virtual void enemyFly();
	//À¿Õˆ∂Øª≠
	virtual ActionInterval * enemyDie();
	void eliteCB();
public:
	CC_SYNTHESIZE(bool,firstCollide,FirstCollide);
	CC_SYNTHESIZE(bool,isProtect,IsProtect);
	virtual bool initWithSpriteFrameName(int sb, int level);
	static Elite_Shadow *create(int sb, int level);
	virtual void hurt(int attack);
	virtual void onEnter();	
	virtual void elude();
	virtual Rect getBoundingBox(int) const;
	virtual Rect getBoundingBox() const;
	
};

#endif