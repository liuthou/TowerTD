#include "EnemyManager.h"
EnemyManager *EnemyManager::enemyManger = nullptr;
EnemyManager *EnemyManager::getInstance()
{
	if (enemyManger==nullptr)
	{
		enemyManger = new EnemyManager();
		return enemyManger;
	}
	return enemyManger;
}
void EnemyManager::addEnemy(BaseTank * tank)
{
	enemyVector.pushBack(tank);
}

void EnemyManager::removeEnemy(BaseTank * tank)
{
	enemyVector.eraseObject(tank);
}

void EnemyManager::removeAllenemys()
{
	for (auto eiter = enemyVector.begin();eiter!=enemyVector.end();)
	{
		if ((*eiter)->getISdie())
		{
			eiter = enemyVector.erase(eiter);
		}
		else
		{

			eiter++;
		}
	}
}
void EnemyManager::cleanAll()
{
	enemyVector.clear();
}
Vector<BaseTank*>& EnemyManager::getEnemyManger()
{
	return enemyVector;
}