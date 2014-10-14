#ifndef __ONEENEMYPLAN_H
#define __ONEENEMYPLAN_H
#include "BaseEnemyplan.h"
#define ONEHP 100
class OneEnemyplan:public BaseEnemyplan{
public:
	virtual bool init(int Speed);
    static OneEnemyplan* create(int Speed);
private:
};
#endif