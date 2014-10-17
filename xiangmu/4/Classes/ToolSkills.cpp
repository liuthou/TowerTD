#include "ToolSkills.h"
#include "Tool.h"
#include "ShapeBullet.h"
bool ToolSkills::init(Vec2 position) {
	if (!Tool::initWithSpriteFrameName("ToolSkills1.png", position))
	{
		return false;
	}
	

	return true;
}

void ToolSkills::onEnter(){

	Tool::onEnter();

}

ToolSkills *ToolSkills::create(Vec2 position) {
	auto ts = new ToolSkills();
	if (ts && ts->init(position)) {
		ts->autorelease();
		return ts;
	}
	CC_SAFE_DELETE(ts);
	return nullptr;
}

void ToolSkills::toolFly(){

	auto toolFly = ShareFunc::getAct("ToolSkills1.png", 1, 10, 0.2, -1);
	this->runAction(toolFly);
	
}

