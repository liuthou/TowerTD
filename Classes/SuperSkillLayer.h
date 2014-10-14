#ifndef __SUPERSKILLLAYER_H
#define __SUPERSKILLLAYER_H
#include "cocos2d.h"
#include "GameBasic.h"
class SuperSkillLayer:public Layer
{   
	Sprite * sprite;
	int type;
	EventListenerTouchOneByOne *listener;
	~SuperSkillLayer();
public:
	virtual bool init();
	static SuperSkillLayer *create();
	ProgressTimer* icecoolingBar;//冰技能冷却条
	ProgressTimer* firecoolingBar;//火技能冷却条
	ProgressTimer* wirecoolingBar;//电技能冷却条
	ProgressTimer* windcoolingBar;//风技能冷却条
	virtual void updateSkills(float t);
};
#endif // !__SUPERSKILLLAYER_H
