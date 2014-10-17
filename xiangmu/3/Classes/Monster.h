#ifndef __MONSTER_H_
#define __MONSTER_H_
#include "cocos2d.h"
#include "Monster.h"
class Monster:public Enemy{
public:
	CREATE_FUNC(Monster);
	virtual bool init();
};
#endif