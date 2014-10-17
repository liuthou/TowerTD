//
//  HelpLayer.cpp
//  heroJump
//
//  Created by liuly on 14-9-19.
//
//

#include "HelpLayer.h"

HelpLayer * HelpLayer::create(int dateType){
	HelpLayer * layer = new HelpLayer();
	if (layer && layer->init(dateType))
	{
		layer->autorelease();
		return layer;
	}
	
	CC_SAFE_DELETE(layer);
	return nullptr;
}
bool HelpLayer::init(int dateType){
	if (!Layer::init())
	{
		return false;
	}
	
	useHelp(dateType);
	return true;
}
void HelpLayer::useHelp(int dateType){
	//Zero on behalf of the board
	if (dateType == 0)
	{
		//Animation function board
	    boardAnimation();
	}
	//A representative monkey holster
	if (dateType == 1)
	{
		log("*********");
		//The animation of the monkey holster
		holsterAnimation();
	}
}
void HelpLayer::boardAnimation(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Help.plist");
	// A rendering load many times
	SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("mood.png");
	visize = Director::getInstance()->getVisibleSize();
	// board
    board = Sprite::createWithSpriteFrame(frame1);
	b_size = board->getContentSize();
	board->setPosition(Vec2(b_size.width/2,visize.height/8));
    this->addChild(board);

	SpriteFrame * frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("mood.png");
	finger = Sprite::createWithSpriteFrame(frame2);
	finger->setPosition(Vec2(board->getPositionX(),board->getPositionY()));
	finger->setAnchorPoint(Vec2(1,1));
	finger->setRotation(270);
	finger->setScale(0.5);
	this->addChild(finger);
	
	auto mo = MoveTo::create(2,Vec2(visize.width - b_size.width/2,board->getPositionY() + b_size.height * 4));
	finger->runAction(mo);
	this->scheduleUpdate();
}
void HelpLayer::update(float t){
	if(finger->getPosition() == Vec2(visize.width - b_size.width/2,board->getPositionY() + b_size.height * 4)){
		board->setPosition(Vec2(finger->getPosition()));
	}

}   
void HelpLayer::holsterAnimation(){
	log("+++++++++++++++++++++");
}
