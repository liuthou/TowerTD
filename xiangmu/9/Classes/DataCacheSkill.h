#ifndef __DATACAHESKILL_R_
#define __DATACAHESKILL_R_

#include "cocos2d.h"
#include "string.h"
using namespace cocos2d;

class DataCacheSkill : public Ref
{
public:
	//存放数据库中的技能的数据
	//技能的ID
	CC_SYNTHESIZE(int, _id, Id);
	//技能的伤害值
	CC_SYNTHESIZE(int, _attickValue, AttickValue);
	//技能的耗魔量
	CC_SYNTHESIZE(int, _consumeMp, ConsumeMp);
	//技能是否解锁
	CC_SYNTHESIZE(int, _isShow, IsShow);
	//技能的等级
	CC_SYNTHESIZE(int, _skillGrade, SkillGrade);
	//技能升一级的加成
	CC_SYNTHESIZE(double, _skillAddition, SkillAddition);
	//技能消耗的sp
	CC_SYNTHESIZE(int, _skillUserSp, SkillUserSp);
	virtual bool init();
	CREATE_FUNC(DataCacheSkill);
	DataCacheSkill(){}
	~DataCacheSkill(){}
};

#endif