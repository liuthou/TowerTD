#ifndef __INJUREDEFFECT_H_
#define __INJUREDEFFECT_H_
#include "cocos2d.h"
USING_NS_CC;
class InjuredEffect:public Layer{
public:
	CREATE_FUNC(InjuredEffect);
	virtual bool init();
	void beInjured(int fullhp,int nowhp);
	CC_SYNTHESIZE(float,mopacity,Mopacity);
protected:
	float calculateOpacity(int fullhp,int nowhp);
	void refreshOpacity();
	LayerGradient *layerleft;
	LayerGradient *layerright;
	int fullhp,nowhp;
	bool isplayingalarmeffect;
};
#endif