
#ifndef __Dota_Legend__ChangeAttackBGLayer__
#define __Dota_Legend__ChangeAttackBGLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class ChangeAttackBGLayer :public Layer {
protected:
	void returnLast(Ref * sender);
	void addBackground();
	void addReturnMenu();
public:
	virtual bool init();
	CREATE_FUNC(ChangeAttackBGLayer);
};
#endif /* defined(__Dota_Legend__ChangeAttackBGLayer__) */
