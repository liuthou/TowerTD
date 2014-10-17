#ifndef __SKILLES_R_
#define __SKILLES_R_

#include "cocos2d.h"
#include "DataCacheSkill.h"
using namespace cocos2d;

class Skilles
{
private:
	static Skilles * instance;
public:
	static Skilles * getInstance();
	//添加技能数据类
	void addSkillRef(DataCacheSkill * skill);
	//存放技能数据的容器
	CC_SYNTHESIZE_PASS_BY_REF(Vector<DataCacheSkill *>, _skilles,Skilles);
private:
	Skilles(){}
	Skilles(const Skilles & skilles){}
	Skilles operator + (const Skilles & skilles)
	{
		return skilles;
	}
	//清除容器中的所有元素
	void clearSkilles();
};

#endif