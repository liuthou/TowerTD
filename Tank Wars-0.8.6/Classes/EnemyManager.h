#ifndef __ENEMYMANAGER_H
#define __ENEMYMANAGER_H
#include "cocos2d.h"
#include "BaseTank.h"
USING_NS_CC;
//子弹管理器
class EnemyManager
{  
	static EnemyManager *enemyManger;
	Vector<BaseTank*> enemyVector;
public:
	void addEnemy(BaseTank * tank);//添加敌军
	void removeEnemy(BaseTank * tank);//移除敌军
	void removeAllenemys();//移除所有敌军
	void cleanAll();
	Vector<BaseTank*>& getEnemyManger();//获取敌军子弹容器
	static EnemyManager* getInstance();
};
#endif // !__BULLTMANAGER_H
