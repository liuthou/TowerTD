#ifndef __THREEENEMYPLAN_H
#define __THREEENEMYPLAN_H
#include "BaseEnemyplan.h"
#define THREEHP 500
class ThreeEnemyplan:public BaseEnemyplan{
public:
	virtual bool init(int Speed);
	static ThreeEnemyplan* create(int Speed);
};
#endif