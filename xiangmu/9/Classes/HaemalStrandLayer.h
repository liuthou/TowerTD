#ifndef  __HAEMALSTRANDLAYER_H
#define  __HAEMALSTRANDLAYER_H

#include "cocos2d.h"
#include "T_HeamalStrandLayer.h"
using namespace cocos2d;

class HaemalStrandLayer:public Layer
{
private:
	//猪脚的当前血量
	void heroHurtHp(Ref *f);
	//猪脚的当前魔法值
	void heroCostLan(Ref *f);
public:
	CC_SYNTHESIZE(int, _heroHp, HeroHp);
	CC_SYNTHESIZE(int, _heroMp, HeroMp);
	CC_SYNTHESIZE(int, _attackValue, AttackValue);
	CC_SYNTHESIZE(int, _costLan, CostLan);
	virtual bool init();
	CREATE_FUNC(HaemalStrandLayer);
	void setFill(ProgressTimer* fill){ _fill = fill; }
	void setProgress(float percentage){ _fill->setPercentage(percentage); }
	HaemalStrandLayer(){}
	~HaemalStrandLayer();
private:
	ProgressTimer* _fillBule;
	ProgressTimer* _fillHp;
	ProgressTimer* _fill;
	Sprite * _hpMpGround;
	Sprite * _heroHpStrip;
	Sprite * _heroMpStrip;
};
#endif