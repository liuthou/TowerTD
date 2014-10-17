
#ifndef __Dota_Legend__LeftMenuLayer__
#define __Dota_Legend__LeftMenuLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class LeftMenuLayer :public Layer {
protected:
	void playerInformation(Ref * sender);
public:
	virtual bool init();
	CREATE_FUNC(LeftMenuLayer);
	void update(float t);

};
#endif /* defined(__Dota_Legend__LeftMenuLayer__) */
