#ifndef _HEROESBULLETS_H
#define _HEROESBULLETS_H

#include "BaseBullet.h"

class HeroesBullets : public BaseBullet{
private:
	HeroesBullets(){}
	HeroesBullets(const HeroesBullets &lb);
	HeroesBullets operator = (const HeroesBullets &lb){
		return lb;
	}
protected:
	Vector<BaseBullet *> linearBullets;
	static HeroesBullets * instance;
public:
	static HeroesBullets *getInstance();
	void addBullet(BaseBullet *);
	Vector<BaseBullet *>  getBullets()const;
	void deleteBullet();
	void reset();
};
#endif