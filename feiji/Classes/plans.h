#ifndef __PLANS_H
#define __PLANS_H
#include "cocos2d.h"
#include "BaseEnemyplan.h"
using namespace cocos2d;
class plans
{
private:
	plans(){}
	plans(const plans & b){}
	plans operator =(const plans & b)
	{
		return b;
	}
protected:
	static plans *instance;
public:
	void deleteEnemy(BaseEnemyplan* enemy);
	static plans * getInstance();
	void addplan(BaseEnemyplan * bt);
	Vector<BaseEnemyplan *>plansVector;
};
#endif