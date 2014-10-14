#ifndef __TWOENEMYPLAN_H
#define __TWONEMYPLAN_H
#include "BaseEnemyplan.h"
#define TWOHP 250
class TwoEnemyplan:public BaseEnemyplan{
public:
	virtual bool init(int Speed);
	static TwoEnemyplan* create(int Speed);
};
#endif