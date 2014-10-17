//
//  SystemConfigUtil.h
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#ifndef __heroJump__SystemConfigUtil__
#define __heroJump__SystemConfigUtil__
/**
 * add by mabs
 * This is marcos container
 */
#include <iostream>
/**
 *  get windows size and windows orgin
 *
 *  @return WINDOWS_SIZE:is windows size
 *          WINDOWS_ORGIN: is windows orgin
 */
#define CREATE_WINDSIZE_AND_WINORGIN(__TYPE__) \
__TYPE__::WINDOWS_SIZE = Director::getInstance()->getVisibleSize(); \
__TYPE__::WINDOWS_ORGIN = Director::getInstance()->getVisibleOrigin();

#define WINDSIZE_AND_WINORGIN \
protected:  Size WINDOWS_SIZE; \
protected:  Vec2 WINDOWS_ORGIN;


#define GET_WINDOWS_SIZE Director::getInstance()->getVisibleSize()
#define GET_WINDOWS_ORGIN Director::getInstance()->getVisibleOrigin()

#define STONEHEIGHT 70
/**
 *  regist TonchOneByOneLisener for this
 *
 *  @param __TYPE__ class Name
 *
 *  @return 
 */
#define CREATE_EVENTLISENER_FOR_THIS(__TYPE__) \
auto __dis = Director::getInstance() -> getEventDispatcher();\
auto __lisener = EventListenerTouchOneByOne::create(); \
__lisener->setSwallowTouches(true);\
__lisener -> onTouchBegan = std::bind(&__TYPE__::touchBegan,this, std::placeholders::_1, std::placeholders::_2); \
__lisener -> onTouchMoved = std::bind(&__TYPE__::touchMoved,this, std::placeholders::_1, std::placeholders::_2); \
__lisener -> onTouchEnded = std::bind(&__TYPE__::touchEnded,this, std::placeholders::_1, std::placeholders::_2); \
__dis -> addEventListenerWithSceneGraphPriority(__lisener, this);

#define logDebug false

#define JUMP_LOG(...) \
if(logDebug){ \
    log(__VA_ARGS__); \
}



#endif /* defined(__heroJump__SystemConfigUtil__) */
