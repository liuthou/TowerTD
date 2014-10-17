#ifndef __MONSTERDIEEFFECT_H_
#define __MONSTERDIEEFFECT_H_
#include "cocos2d.h"
USING_NS_CC;
class MonsterDieEffect:public Sprite{
public:
	//粒子效果写成固定的,如果有需要再修改
	//出入两个粒子效果,一个0一个1
	static MonsterDieEffect* create(Vec2 appearpoint,Vec2 disappearpoint,std::string effectfile1 = "monsterdieparticle_0.plist",std::string effectfile2 = "monsterdieparticle_1.plist");
	virtual bool init(Vec2 appearpoint,Vec2 disappearpoint,std::string effectfile1,std::string effectfile2);
	
protected:
	void autoRemoveSelf(float dt);
};
#endif