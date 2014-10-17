#ifndef __OXENEMY_H
#define __OXENEMY_H
#include "cocos2d.h"
using namespace cocos2d;
#include "Person.h"
#define OXPROJECT "OxEnemy"
class OxEnemy:public Person
{
protected:
	virtual bool init(std::string fileNameXml);
public:
	static OxEnemy *create(std::string fileNameXml);
	virtual void move();
	virtual void fair();
};
#endif