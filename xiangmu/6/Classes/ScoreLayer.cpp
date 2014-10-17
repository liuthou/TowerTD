//
//  ScoreLayer.cpp
//  heroJump
//
//  Created by lius on 14-9-17.
//
//

#include "ScoreLayer.h"
#include "BaseRewards.h"
#include "PlayGameScene.h"
 bool ScoreLayer::init(){
	 if (!Layer::init()){
		 return false;
	 }

	vSize = Director::getInstance()->getVisibleSize();

	curScore = 0;
	maxScore = UserDefault::getInstance()->getIntegerForKey("maxScore");

	curCoin = 0;
	maxCoin = UserDefault::getInstance()->getIntegerForKey("maxCoin");

	curMeters = 0;
	maxMeters = UserDefault::getInstance()->getIntegerForKey("maxMeter");

	auto playGameScene = dynamic_cast<PlayGameScene *>(Director::getInstance()->getRunningScene());
	auto bgLayer = playGameScene->getBackgroundLayer();
	curMeters = bgLayer->getFinalLength();
	maxMeters = UserDefault::getInstance()->getIntegerForKey("maxMeters");

	auto center = __NotificationCenter::getInstance();
	center->addObserver(this, callfuncO_selector(ScoreLayer::recvAward),"Award",nullptr);

	 return true;
 }

 void ScoreLayer::onEnter(){
	 Layer::onEnter();
	 addLabel();
	 curMetersLabel->setString(StringUtils::format("%d",curMeters));
 }

 void ScoreLayer::addLabel(){

	 curScoreLabel = Label::createWithSystemFont("0","",30);
	 curCoinLabel = Label::createWithSystemFont("0","",30);
	 curMetersLabel = Label::createWithSystemFont("0","",30);
	 
	 curMetersLabel->setPosition(vSize.width/10+6,vSize.height-60);
	 curMetersLabel->setAnchorPoint(Vec2(0,0));
	 curMetersLabel->setColor(cocos2d::Color3B::BLACK);

	 curScoreLabel->setPosition(vSize.width*2/5+14,vSize.height-60);
	 curScoreLabel->setAnchorPoint(Vec2(0,0));
	 curScoreLabel->setColor(cocos2d::Color3B::BLACK);

	 curCoinLabel->setPosition(vSize.width*7/10+22,vSize.height-60);
	 curCoinLabel->setAnchorPoint(Vec2(0,0));
	 curCoinLabel->setColor(cocos2d::Color3B::BLACK);

	 this->addChild(curMetersLabel);
	 this->addChild(curScoreLabel);
	 this->addChild(curCoinLabel);
 }
 void ScoreLayer::recvAward(Ref * obj){

	 auto award = static_cast<BaseRewards *>(obj);
	 CCASSERT(award,"obj not award!");

	 curScore = curScore + award->getScore();
	 curScoreLabel->setString(StringUtils::format("%d",curScore));

	 curCoin = curCoin + award->getCoin();
	 curCoinLabel->setString(StringUtils::format("%d",curCoin));

 }
 int ScoreLayer::getCurScore(){
	 return curScore;
 }
 int ScoreLayer::getCurCoin(){
		return curCoin;
 }
 int ScoreLayer::getCurMeter(){
	 return curMeters;
 }