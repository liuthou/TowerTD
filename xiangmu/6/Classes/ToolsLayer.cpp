//
//  ToolsLayer.cpp
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#include "ToolsLayer.h"
#include "JumpHelp.h"

#include "BackgroundLayer.h"
#include "RubberbandSprite.h"
#include "ConfigUtil.h"
#include "HitBodys.h"
#include "ToolsUtils.h"
bool ToolsLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    /**
     *  默认使用木棍
     */
    nowType = NOW_USE_TYPE::USE_WOOD;
    p1 = Vec2(0, 0);
    p2 = Vec2(0,0);
    CREATE_EVENTLISENER_FOR_THIS(ToolsLayer);
    return true;
}


void ToolsLayer::setNowUseType(NOW_USE_TYPE nType){
    nowType = nType;
}

void ToolsLayer::onEnter(){
    Layer::onEnter();

}

void ToolsLayer::addTools(){
    
}

bool ToolsLayer::touchBegan(Touch* t, Event* e){
    HitBodys::getInstance() -> clearUseToolsBaseSprite();
    switch (nowType) {
        case NOW_USE_TYPE::USE_WOOD:
            break;
        case NOW_USE_TYPE::USE_RUBBERBAND:{
            p1 = t -> getLocation();
        }
            break;
        default:
            break;
    }
    return true;
}
void ToolsLayer::touchMoved(Touch* t, Event* e){
    switch (nowType) {
        case NOW_USE_TYPE::USE_WOOD:
            break;
        case NOW_USE_TYPE::USE_RUBBERBAND:{
            p2 = t -> getLocation();
        }
            break;
        default:
            break;
    }
}
void ToolsLayer::touchEnded(Touch* t, Event* e){
    switch (nowType) {
        case NOW_USE_TYPE::USE_WOOD:{
            auto wood = WoodSprite::create();
            BackgroundLayer* backgroundLayer = JumpHelp::getBackgroundLayer();
            Vec2 vec2 = backgroundLayer -> currMidLayer -> convertToNodeSpace(t -> getLocation());
            wood-> setPosition(vec2);
            backgroundLayer -> currMidLayer  -> addChild(wood);
        }
            break;
        case NOW_USE_TYPE::USE_RUBBERBAND:{
            
            auto rubberbank = RubberbandSprite::create();
            BackgroundLayer* backgroundLayer = JumpHelp::getBackgroundLayer();
            Vec2 vec1 = backgroundLayer -> currMidLayer -> convertToNodeSpace(p1);
            Vec2 vec2 = backgroundLayer -> currMidLayer -> convertToNodeSpace(p2);
            rubberbank -> setP1(vec1);
            rubberbank -> setP2(vec2);
            rubberbank -> setRubberAngle((atan2((vec2.y-vec1.y),(vec2.x-vec1.x))*180/PI) > 0 ? (atan2((vec2.y-vec1.y),(vec2.x-vec1.x))*180/PI):(atan2((vec2.y-vec1.y),(vec2.x-vec1.x))*180/PI) + 180);

            backgroundLayer -> currMidLayer  -> addChild(rubberbank,1000);
            p1 = Vec2(0, 0);
            p2 = Vec2(0,0);
        }
            break;
        default:
            break;
    }
    
}
void ToolsLayer::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated){
   ToolsUtils::drawRubberband(p1,p2,transform);
}
void ToolsLayer::draw(Renderer *renderer,const Mat4& transform ,uint32_t flags){
    Layer::draw(renderer, transform, flags);
    if (NOW_USE_TYPE::USE_RUBBERBAND == nowType) {
        if ((p1.x != 0 && p1.y != 0) && (p2.x != 0 && p2.y != 0)) {
            _customCommand.init(_globalZOrder);
            _customCommand.func = CC_CALLBACK_0(ToolsLayer::onDraw, this, transform, flags);
            renderer->addCommand(&_customCommand);
        }
    }

}
