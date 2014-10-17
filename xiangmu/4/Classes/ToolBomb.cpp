#include "ToolBomb.h"
#include "Tool.h"
#include "ShapeBullet.h"
bool ToolBomb::init(Vec2 position) {
	if (!Tool::initWithSpriteFrameName("ToolBomb1.png", position))
	{
		return false;
	}


	return true;
}

void ToolBomb::onEnter(){

	Tool::onEnter();

}

ToolBomb *ToolBomb::create(Vec2 position) {
	auto tb = new ToolBomb();
	if (tb && tb->init(position)) {
		tb->autorelease();
		return tb;
	}
	CC_SAFE_DELETE(tb);
	return nullptr;
}

void ToolBomb::toolFly(){
	auto toolFly = ShareFunc::getAct("ToolBomb1.png", 1, 6, 0.2, -1);
	this->runAction(toolFly);
}




