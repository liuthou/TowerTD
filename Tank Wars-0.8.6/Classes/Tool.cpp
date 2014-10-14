#include "Tool.h"
Tool * Tool::create(int type){
	auto t = new Tool();
	if (t && t->init(type)) {
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return nullptr;
}
bool Tool::init(int type){
	std::string tfileName;
	this->type = type;
	if (type == 1) {
		tfileName = "props-tank.png";
	}else{
		tfileName = "props-mine.png";
	}
	if(!initWithSpriteFrameName(tfileName)){
		return false;
	}
	float x = this->getContentSize().width/2 + CCRANDOM_0_1() * (640 - this->getContentSize().width);
	float y = this->getContentSize().height/2 + CCRANDOM_0_1() * (640 - this->getContentSize().height);
	this->setPosition(x,y);
	this->schedule(schedule_selector(Tool::cleanfrom),5);
	return true;
}
void Tool::cleanfrom(float t)
{
	auto blik = Blink::create(1,3);
	auto cf = CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create(blik,cf,NULL));
}