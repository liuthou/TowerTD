#ifndef __BULLETS_H
#define __BULLETS_H
#include "cocos2d.h"
#include "BaseBullet.h"
using namespace cocos2d;
class Bullets
{
private:
	Bullets(){}
	Bullets(const Bullets &bullet){}
	Bullets operator=(const Bullets &bullet){return bullet;}
	static Bullets *instence;
	Vector<BaseBullet *>roleBullets;
	Vector<BaseBullet *>enemyBullets;
public:
	static Bullets *getInstence();
	Vector<BaseBullet *> getRoleBullets();
	void addRoleBullets(BaseBullet *bullet);
	void deleteRoleBullets();
	void deleteRoleBulletsAll();
	Vector<BaseBullet *> getEnemyBullets();
	void addEnemyBullets(BaseBullet *bullets);
	void deleteEnemyBullets();
	void deleteEnemyBulletsAll();

};
#endif