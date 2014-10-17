#ifndef __SFROLE_H
#define __SFROLE_H
#include "cocos2d.h"
#include "Person.h"
using namespace cocos2d;
#define PROJECTNAME "dota"
class SFRole:public Person
{
protected:
	virtual bool init(std::string fileName);
public:
	static SFRole * create(std::string fileName);
	virtual void move();
	virtual void fair();
	CC_SYNTHESIZE(int, mp, Mp);
};

#endif
