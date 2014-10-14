#include "BulletManager.h"
BulletManager *BulletManager::bulletManger = nullptr;
BulletManager *BulletManager::getInstance()
{
	if (bulletManger==nullptr)
	{
		bulletManger = new BulletManager();
		return bulletManger;
	}
	return bulletManger;
}
void BulletManager::addEnemyBullet(Basebullet * bullet)
{
	enemybullet.pushBack(bullet);
}
void BulletManager::addTankBullet(Basebullet * bullet)
{
	tankbullet.pushBack(bullet);
}
void BulletManager::removeEnemyBullet(Basebullet * bullet)
{
	enemybullet.eraseObject(bullet);
}
void BulletManager::removeTankBullet(Basebullet *bullet)
{
	tankbullet.eraseObject(bullet);
}
void BulletManager::removeAllBullets()
{
	for (auto biter = tankbullet.begin();biter!=tankbullet.end();)
	{
		if ((*biter)->getISDIE())
		{
			biter = tankbullet.erase(biter);
		}
		else
		{
			biter++;
		}
	}
	for (auto eiter = enemybullet.begin();eiter!=enemybullet.end();)
	{
		if ((*eiter)->getISDIE())
		{
			eiter = enemybullet.erase(eiter);
		}
		else
		{
			eiter++;
		}
	}
}
void BulletManager::cleanAll()
{
	tankbullet.clear();
	enemybullet.clear();
}
Vector<Basebullet*>& BulletManager::getEnemyBulletManger(){
	return enemybullet;
}
Vector<Basebullet*>& BulletManager::getTankBulletManager(){
	return tankbullet;
}