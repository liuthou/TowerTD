#ifndef __HEROLAYER_R_
#define __HEROLAYER_R_

#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
using namespace std;


class HeroLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(HeroLayer);
};

#endif