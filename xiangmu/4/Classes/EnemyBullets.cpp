#include "EnemyBullets.h"
EnemyBullets * EnemyBullets::instance =nullptr;
EnemyBullets * EnemyBullets::getInstance(){
	if (!instance)
	{
		instance = new EnemyBullets();
	}
	return instance;
}
void EnemyBullets::addBullet(BaseBullet *enemy){
	EnemybulletsVector.pushBack(enemy);
}
Vector<BaseBullet *> EnemyBullets::getBullet()const{
	return EnemybulletsVector;
}
void EnemyBullets::deleteBullet(){
	for (auto it = EnemybulletsVector.begin();it != EnemybulletsVector.end();)
	{
		if ((*it)->getDie())
		{
			it = EnemybulletsVector.erase(it);
		}else{
			it++;
		}
	}
}
void EnemyBullets::reset(){
	EnemybulletsVector.clear();
}