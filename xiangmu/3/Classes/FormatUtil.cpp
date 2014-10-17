#include "FormatUtil.h"
USING_NS_CC;
bool FormatUtil::init(){
	if (!Sprite::init())
	{
		return false;
	}
	//初始化作用范围
	this->attrange = FORMATUTILATTRANGE;
	this->price = FORMATUTILPRICE;
	//初始化动画
	Vector<SpriteFrame*> animationframe;
	for (int i = 0;i<4;i++)
	{
		std::string tmp_filename = StringUtils::format("explode%d.png",i+1);
		//应该预加载
		auto tmp_frame = Sprite::create(tmp_filename)->getSpriteFrame();
		animationframe.pushBack(tmp_frame);
	}
	Animation* tmp_animation = Animation::createWithSpriteFrames(animationframe);
	this->setAnimation(tmp_animation);
	animation->setDelayPerUnit(0.1);
	animation->setLoops(1);
	return true;
}
void FormatUtil::onEnter(){
	Sprite::onEnter();
	Animate* explode = Animate::create(animation);
	auto tmp_action = Sequence::create(explode,CCCallFunc::create(CC_CALLBACK_0(FormatUtil::explodeFunc,this)),NULL);
	this->runAction(tmp_action);
}

void FormatUtil::setExplodeFunc(std::function<void(FormatUtil* formatutil)>explode){
	this->explode = explode;
}

void FormatUtil::explodeFunc(){
	if (explode)
	{
		this->explode(this);
	}
	this->remove();
}
void FormatUtil::remove(){
	this->removeFromParent();
}