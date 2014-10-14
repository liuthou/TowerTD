#include "plans.h"
//飞机容器单例
plans * plans::instance =nullptr;
plans * plans::getInstance() 
{
	if(!instance)
	{
		instance =new plans();
	}
	return instance;
}
void plans::addplan(BaseEnemyplan * bt)
{
	plansVector.pushBack(bt);
}
void plans::deleteEnemy(BaseEnemyplan* enemy){
	//容器中删除
	plansVector.eraseObject(enemy);
	//调用敌机的方法删除自己
	//enemy->remove();
}
