//this layer is a test layer
#ifndef __TESTLAYER_H
#define __TESTLAYER_H
#include "cocos2d.h"
USING_NS_CC;
class testLayer:public Layer
{  
  
public: 
	static Layer* shareTowerLayer;
	virtual bool init();
	CREATE_FUNC(testLayer);
	void addEnemy(float t);
};
#endif // !__TESTLAYER_H
