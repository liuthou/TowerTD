//
//  RubberBand.cpp
//  herojump
//
//  Created by lanou3g on 14-9-24.
//
//

#include "RubberBand.h"
bool RubberBand::init(){
    if (!Layer::init()) {
        return false;
    }
    auto dn = DrawNode::create();
    this->addChild(dn,10);
    
    //get first and the end position for the rubber band use
    auto listen = EventListenerTouchOneByOne::create();
    listen->onTouchBegan = [=](Touch *t, Event *e){
        firstTouchPosition = t->getLocation();
        v.push_back(firstTouchPosition);
        beginDrawRubberBand = t->getLocation().x ;
        dn->drawDot(firstTouchPosition, 10, Color4F::RED);
        return true;
    };
    
    listen->onTouchMoved = [=](Touch* t, Event* e){
        endTouchPosition = t->getLocation();
        v.push_back(endTouchPosition);
        endDrawRubberBand = t->getLocation().x;
        dn->drawSegment(*v.begin(),*v.end(),  5, Color4F::RED);
    };
    
    listen->onTouchEnded = [=](Touch *t ,Event *e){
        //auto sp  = Sprite::cre ate();
        //sp->setPosition(endTouchPosition)
        v.clear();
        
    };
    
    auto dis = Director::getInstance()->getEventDispatcher();
    dis->addEventListenerWithSceneGraphPriority(listen, this);

   
    return true;
}

Scene * RubberBand::createScene(){
    auto scene = Scene::create();
    auto layer = RubberBand::create();
    scene->addChild(layer);
    return  scene;
}