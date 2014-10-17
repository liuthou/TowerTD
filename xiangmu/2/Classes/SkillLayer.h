#ifndef __SKILLLAYER_H
#define __SKILLLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class SkillLayer:public Layer
{
protected:
	virtual bool init();
public:
	CREATE_FUNC(SkillLayer);
	void addSkill();
	void up(float t);
	void listenAddSkill(Ref *sender);
	void onEnter();
	void onExit();
};
#endif