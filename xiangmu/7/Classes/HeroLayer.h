/************************************************************************/
/* 
	贴主角


*/
/************************************************************************/
#ifndef __HEROLAYER_H
#define __HEROLAYER_H

#include "cocos2d.h"
#include "Hero.h"
#include "AllVectors.h"

using namespace cocos2d;

class HeroLayer:public Layer{

public:

	virtual bool init();
	CREATE_FUNC(HeroLayer);

	
	Size visSize;		//可视区的大小

	Hero *sp;
	void getFieBall(float t);
	Hero *getHero();

};
#endif // !__HEROLAYER_H