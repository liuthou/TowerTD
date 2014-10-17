#ifndef __SKILLRELEASECONTAINER_R_
#define __SKILLRELEASECONTAINER_R_

#include "cocos2d.h"
#include "SkillBase.h"
using namespace cocos2d;

class SkillReleaseContainer
{
private:
	SkillReleaseContainer(){}
	SkillReleaseContainer(const SkillReleaseContainer & skillReleaseContainer){}
	SkillReleaseContainer operator + (const SkillReleaseContainer & skillReleaseContainer)
	{
	    return skillReleaseContainer;
	}
	static SkillReleaseContainer * instance;
public:
	static SkillReleaseContainer * getInstance();
	//向容器中添加技能
	void addSkillRelease(SkillBase * skill);
	//清除容器中技能标记为true的技能
	void removeSkill();
	//清空容器中所有技能
	void clearContainer();
	CC_SYNTHESIZE_PASS_BY_REF(Vector<SkillBase *>, _skillCreate, SkillCreate);
};

#endif