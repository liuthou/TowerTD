#ifndef __BASEELITE_H_
#define __BASEELITE_H_

#include "Conf.h"
#include "BaseEnemy.h"
class BaseElite:public BaseEnemy
{	
protected:
	int randomNumber;
	int bulletCount;

public:
	// «∑Ò…¡±‹ Ù–‘÷µ
	CC_SYNTHESIZE(bool,firstCollide,FirstCollide);
	virtual bool initWithSpriteFrameName(std::string fileName, int sb, int level);
	virtual void onEnter();
	
};
#endif