#ifndef _ENEMYBULLETS_H
#define _ENEMYBULLETS_H
#include "BaseBullet.h"
class EnemyBullets
{
private:
	EnemyBullets(){}
	EnemyBullets(const BaseBullet & b){}
	EnemyBullets operator = (const EnemyBullets & b){
		return b;
	}
protected:
	Vector<BaseBullet *>EnemybulletsVector;
	static EnemyBullets *instance;
public:
	static EnemyBullets *getInstance();
	void addBullet(BaseBullet *);
	//自己写的代码
	Vector<BaseBullet *> getBullet()const;
	void deleteBullet();
	void reset();
};
#endif // !1