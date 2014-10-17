//
//  BaseColouds.cpp
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#include "BaseColouds.h"
#include "BackgroundLayer.h"
#include "PlayGameScene.h"
#include "Colouds.h"
bool BaseColouds::initWithFile(std::string fileName,int speed){
    if (!Sprite::initWithFile(fileName)) {
        return false;
    }
    Colouds::getInstance()->addColoud(this);
    rand();
    Size vSize = Director::getInstance()->getVisibleSize();
    Size cSize = this->getContentSize();
    float x = CCRANDOM_0_1() * (vSize.width - cSize.width) + cSize.width/2;
    float y = CCRANDOM_0_1() * (vSize.height - cSize.height) + cSize.height/2;
    if (y < 480) {
        this->convertToWorldSpace(Vec2(x,y));
        this->setPosition(x,y);
    }
    else y = 0;
    log("contensize.w = %f,cont.h = %f",cSize.width,cSize.height);
    log("x= %f y=%f",x,y);
//this->runAction(MoveTo::create((cSize.height - this->getPositionX())/speed,Point(480,-cSize.height/2)));
//    auto scene = dynamic_cast<PlayGameScene *>( Director::getInstance()->getRunningScene());
//    auto bgLayer = scene->getBackgroundLayer();
//    bgLayer->addChild(this);
    Colouds::getInstance()->addColoud(this);
    return true;
}