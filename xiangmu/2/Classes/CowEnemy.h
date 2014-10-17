#ifndef __COWENEMY_H
#define __COWENEMY_H
#include "cocos2d.h"
using namespace cocos2d;
#include "Person.h"
#define	COWPROJECTNAME "cowEnemy"
class CowEnemy:public Person
{
protected: 
	virtual bool init(std::string fileNameXml);
public:
	static CowEnemy *create(std::string fileNameXml);
	virtual void fair();
	virtual void move();
};
#endif