#ifndef __DINOSAURENEMY_H
#define __DINOSAURENEMY_H
#include "cocos2d.h"
using namespace cocos2d;
#include "Person.h"
#define DINOSAURPROJECTNAME "dinosaurEnemy"
class DinosaurEnemy:public Person
{
protected:
	virtual bool init(std::string fileNameXml);
public:
	static DinosaurEnemy *create(std::string fileNameXml);
	virtual void move();
	virtual void fair();
};
#endif