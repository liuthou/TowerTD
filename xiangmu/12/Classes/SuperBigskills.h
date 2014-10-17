#ifndef SUPERBIGSKILLS_H
#define SUPERBIGSKILLS_H
#include "cocos2d.h"
using namespace cocos2d;

class Superbigskills:public Sprite{
public:
	static Superbigskills* create(int type);
	virtual bool init(int type);
	virtual void iceHurt();
	virtual void firehurt();
	virtual void wireHurt();
};
#endif