#ifndef __SKILLLAYER_H
#define __SKILLLAYER_H
#include "cocos2d.h"
#include "BossTwo.h"
using namespace cocos2d;
class SkillLayer:public Layer
{
public:
	BossTwo * bosstwo;
	virtual bool init();
	CREATE_FUNC(SkillLayer);
	void addSkillOne();
	void addSkillTwo();
	void update(float t);
private:

};
#endif // !__SKILLLAYER_H
