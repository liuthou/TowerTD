#ifndef __BOUNDINGBOX_R_
#define __BOUNDINGBOX_R_

#include "cocos2d.h"
using namespace cocos2d;

class BoundingBox : public Ref 
{
public:
	bool init();
	bool conductBoundingBox(Vec2 spWordPoint, float spWith, Vec2 sp2WordPoint, float spWith2);
	CREATE_FUNC(BoundingBox);
};

#endif