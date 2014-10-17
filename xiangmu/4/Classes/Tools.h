#ifndef __Tools__
#define __Tools__

#include "cocos2d.h"
using namespace cocos2d;
#include "Tool.h"

class Tools : public cocos2d::Layer
{
public:
	static Tools *getInstance();
	CC_SYNTHESIZE(Vector<Tool *>,toolVector,ToolVector);
	void addTools(Tool *tool);
	void deleteTool();
	void reset();
private:
	Tools() {}
	Tools(const Tools &tool) {}
	Tools operator = (const Tools &tool) {
		return tool;
	}
	static Tools *instance;
};

#endif 