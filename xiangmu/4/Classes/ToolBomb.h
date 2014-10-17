#ifndef __TOOLBOMB__
#define __TOOLBOMB__

#include "cocos2d.h"
using namespace cocos2d;
#include "Tool.h"

class ToolBomb : public Tool
{
protected:

	virtual void toolFly();

public:

	virtual bool init(Vec2 position);

	static ToolBomb *create(Vec2 position);

	virtual void onEnter();

};

#endif // __HELLOWORLD_SCENE_H__