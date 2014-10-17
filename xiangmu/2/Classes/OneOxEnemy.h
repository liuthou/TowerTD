#ifndef __ONEOXENEMY_H
#define __ONEOXENEMY_H
#include "cocos2d.h"
#include "Person.h"
using namespace cocos2d;
#define ONEOXPROJECT "sheep"
class OneOxEnemy:public Person
{
protected:
	virtual bool init(std::string fileNameXml);
public:
	static OneOxEnemy *create(std::string fileNameXml);
	virtual void move();
	virtual void fair();
};
#endif