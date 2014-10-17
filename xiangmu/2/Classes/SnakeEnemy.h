#ifndef __SNAKEENEMY_H
#define __SNAKEENEMY_H
#include "cocos2d.h"
#include "Person.h"
using namespace cocos2d;
#define SNAKEPROJECTNAME "snakeEnemy"
class SnakeEnemy:public Person
{
protected:
	virtual bool init(std::string fileNameXml);
public:
	static SnakeEnemy *create(std::string fileName);
	virtual void fair();
	virtual void move();
};
#endif