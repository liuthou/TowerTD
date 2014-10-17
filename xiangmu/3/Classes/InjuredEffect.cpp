#include "InjuredEffent.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
bool InjuredEffect::init(){
	if (!Layer::init())
	{
		return false;
	}
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();
	layerleft = LayerGradient::create(Color4B(255,0,0,0),Color4B(0,0,0,0),Vec2(size.width/4,0));
	layerright = LayerGradient::create(Color4B(255,0,0,0),Color4B(0,0,0,0),Vec2(-size.width/4,0));
	this->addChild(layerleft);
	this->addChild(layerright);
	isplayingalarmeffect = false;
	return true;
}
void InjuredEffect::beInjured(int fullhp,int nowhp){
	this->fullhp = fullhp;
	this->nowhp = nowhp;
	calculateOpacity(fullhp,nowhp);
	refreshOpacity();
}
float InjuredEffect::calculateOpacity(int fullhp,int nowhp){
	if (nowhp<=(float)fullhp/2)
	{
		//快要死了,发警报
		if (isplayingalarmeffect == false)
		{
			SimpleAudioEngine::getInstance()->playEffect("alarm.wav");
			isplayingalarmeffect = true;
		}
	}else
	{
		if (isplayingalarmeffect == true)
		{
			isplayingalarmeffect = false;
		}
	}
	mopacity = 128.0f*abs(fullhp-nowhp)/fullhp;
	return mopacity;
}
void InjuredEffect::refreshOpacity(){
	layerleft->setStartOpacity(mopacity);
	layerright->setStartOpacity(mopacity);
}