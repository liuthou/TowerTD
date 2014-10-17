
#ifndef __Dota_Legend__AttackMapLayer__
#define __Dota_Legend__AttackMapLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class AttackMapLayer :public Layer{
protected:
	void changeMap_a_1(Ref * sender);
	void changeMap_a_2(Ref * sender);
	void changeMap_a_3(Ref * sender);
	void changeMap_a_4(Ref * sender);
	void changeMap_a_5(Ref * sender);
	void addMapMenu();
public:
	virtual bool init();
	CREATE_FUNC(AttackMapLayer);
};

#endif /* defined(__Dota_Legend__AttackMapLayer__) */
