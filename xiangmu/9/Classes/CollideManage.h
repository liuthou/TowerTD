#ifndef __COLLIDEMANAGE_R_
#define __COLLIDEMANAGE_R_

#include "cocos2d.h"
#include "SkillReleaseContainer.h"
#include "Monsters.h"
#include "HeroBase.h"
#include "BoundingBox.h"
using namespace cocos2d;


class CollideManage : public Layer
{
private:
	SkillReleaseContainer * _skillReleaseContainer;
	Monsters* _monsterVector;
	HeroBase * _hero;
	BoundingBox * _boundingBox;
	int _skillTime;
public:
    CollideManage():_skillTime(0){}
	virtual bool init();
	CREATE_FUNC(CollideManage);
private:
	//各种碰撞的管理
	void manageContainer();
    //检测碰撞和是否清除容器中的不用元素
	void containerUpdate(float t);
	//删除技能释放容器中不用的元素
	void skillReleaseContainerManger();
	//删除怪物容器中不用的元素
	void monsterContainerManger();
	void onEnter();
	void heroAttackAndMonsterBounding();// 人打怪物和怪物打人
	void heroSkillBounding();
};

#endif