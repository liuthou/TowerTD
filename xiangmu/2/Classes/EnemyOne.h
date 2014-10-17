#ifndef __ENEMY_H
#define __ENEMY_H
#include "cocos2d.h"
using namespace cocos2d;
#include "Person.h"
#define FLYPROJECTNAME "EnemyFlyOne"
class EnemyOne:public Person
{
protected:
	virtual bool init(std::string fileNameXml);
public:
	virtual void move();
	static EnemyOne *create(std::string fileNameXml);
	virtual void fair();
};
#endif