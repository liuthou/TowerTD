#ifndef __TOOLSSKILLS__
#define __TOOLSSKILLS__

#include "cocos2d.h"
using namespace cocos2d;
#include "Tool.h"

class ToolSkills : public Tool
{
protected:

	virtual void toolFly();

public:
	
	virtual bool init(Vec2 position);

	static ToolSkills *create(Vec2 position);

	virtual void onEnter();
};

#endif // __HELLOWORLD_SCENE_H__