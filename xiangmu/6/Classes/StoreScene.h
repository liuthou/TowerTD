#ifndef __STORESCENE_H_
#define __STORESCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
class StoreScene:public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(StoreScene);
protected:
	void addMenuItemLayer();
    
private:
};
#endif