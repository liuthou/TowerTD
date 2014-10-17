#ifndef __NECROLE_H
#define __NECROLE_H
#include "cocos2d.h"
#include "Person.h"

using namespace cocos2d;

#define PROJECTNAME "Nec"

class NECRole :public Person
{
protected:
	virtual bool init(std::string fileName);
public:
	static NECRole * create(std::string fileName);
	virtual void move();
	virtual void fair();
	CC_SYNTHESIZE(int, mp, Mp);
};

#endif
