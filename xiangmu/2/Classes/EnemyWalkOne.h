#ifndef __ENEMYWALKONE_H
#define __ENEMYWALKONE_H
#include "cocos2d.h"
using namespace cocos2d;
#include "Person.h"
#define ENEMYWALKONEPROJECT "che"
class EnemyWalkOne:public Person
{
public:
	static EnemyWalkOne *create(std::string fileNameXml);
	virtual void move();
	virtual void fair();
protected:
	virtual bool init(std::string fileNameXml);
};
#endif