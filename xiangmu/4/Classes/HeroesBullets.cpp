#include "HeroesBullets.h"
HeroesBullets * HeroesBullets::instance = nullptr;
HeroesBullets * HeroesBullets::getInstance(){
	if (!instance)
	{
		instance = new HeroesBullets();
	}
	return instance;
}
void HeroesBullets::addBullet(BaseBullet * lb){
	linearBullets.pushBack(lb);
}
Vector<BaseBullet *> HeroesBullets::getBullets()const{
	return linearBullets;
}
void HeroesBullets::deleteBullet(){
	for (auto it = linearBullets.begin(); it != linearBullets.end();)
	{
		if ((*it)->getDie())
		{
			it = linearBullets.erase(it);
		}
		else{
			it++;
		}
	}
}

void HeroesBullets::reset() {
	linearBullets.clear();
}
