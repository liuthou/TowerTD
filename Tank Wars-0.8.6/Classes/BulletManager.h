#ifndef __BULLETMANAGER_H
#define __BULLETMANAGER_H
#include "cocos2d.h"
#include "Basebullet.h"
USING_NS_CC;
//子弹管理器
class BulletManager
{  
	static BulletManager *bulletManger;
   Vector<Basebullet*> enemybullet;//敌方子弹容器
   Vector<Basebullet*> tankbullet;//我方坦克子弹容器
public:
	void addEnemyBullet(Basebullet * bullet);//添加己方子弹
	void addTankBullet(Basebullet * bullet);//添加坦克子弹
	void removeEnemyBullet(Basebullet * bullet);//移除敌军子弹
	void removeTankBullet(Basebullet * bullet);//移除坦克子弹
	void removeAllBullets();//移除所有子弹
	void cleanAll();
	Vector<Basebullet*>& getEnemyBulletManger();//获取敌军子弹容器
	Vector<Basebullet*>& getTankBulletManager();//获取我方子弹容器
	static BulletManager* getInstance();
};
#endif // !__BULLTMANAGER_H
