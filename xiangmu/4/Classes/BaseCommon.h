#ifndef __BASECOMMON_H_
#define __BASECOMMON_H_

#include "Conf.h"
#include "BaseEnemy.h"
class BaseCommon:public BaseEnemy
{
protected:
	int randomNumber;

public:
	virtual void onEnter();
	virtual bool initWithSpriteFrameName(std::string fileName, int sb, int level);

};
#endif