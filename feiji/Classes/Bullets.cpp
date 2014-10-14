#include "Bullets.h"
//×Óµ¯ÈÝÆ÷µ¥Àý
Bullets * Bullets::instance =nullptr;
Bullets * Bullets::getInstance() 
{
	if(!instance)
	{
		instance =new Bullets();
	}
	return instance;
}
void Bullets::addBullet(BaseBullet * bt)
{
	bulletsVector.pushBack(bt);
}
void Bullets::deleteBullet(BaseBullet* bullet){
	bulletsVector.eraseObject(bullet);
}
