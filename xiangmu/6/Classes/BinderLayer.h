#ifndef __BINDERLAYER_H_
#define __BINDERLAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class BinderLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BinderLayer);
protected:
private:
};
#endif