
#ifndef __Dota_Legend__LevelLayer__
#define __Dota_Legend__LevelLayer__

#include <iostream>
#include<cocos2d.h>

using namespace cocos2d;
class LevelLayer :public Layer{
protected:
	void goChange(Ref * sender);
public:
	virtual bool init(std::string level);
	static Layer * create(std::string level);
};
#endif /* defined(__Dota_Legend__LevelLayer__) */
