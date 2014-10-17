#ifndef __MENULAYER_H
#define __MENULAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class MemuLayer:public Layer{
public:
	/*void onItem(Ref *scender);*/
	virtual bool init();
	CREATE_FUNC(MemuLayer);
};
#endif // !__MENULAYER_H
