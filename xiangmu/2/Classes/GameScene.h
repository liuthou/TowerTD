
#ifndef __Dota_Legend__GameScene__
#define __Dota_Legend__GameScene__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class GameScene :public Scene
{
public:
	void onEnter();
	virtual bool init();
	CREATE_FUNC(GameScene);

};

#endif /* defined(__Dota_Legend__GameScene__) */
