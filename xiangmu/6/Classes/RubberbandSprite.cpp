//
//  RubberbandSprite.cpp
//  heroJump
//
//  Created by mazhai on 14-10-2.
//
//

#include "RubberbandSprite.h"
#include "ActionHelper.h"
#include "JumpHelp.h"
#include "HitBodys.h"
#include "AudioUtil.h"
#include "ToolsUtils.h"
bool RubberbandSprite::init(){
    if (!UseToolsBaseSprite::init()) {
        return false;
    }
    HitBodys::getInstance() -> clearUseToolsBaseSprite();
    isDie = false;
    isRubber = false;
    isUp = false;
    isStepOn = false;
    p1 = Vec2(0, 0);
    p2 = Vec2(0, 0);
    this -> schedule(schedule_selector(RubberbandSprite::shake), 0.1);
    return true;
}
void RubberbandSprite::collisionRole(){
    isStepOn = true;
    AudioUtil::getInstance()->playEffect("upspring.mp3");
}
void RubberbandSprite::changeRoleState(){
    
}
void RubberbandSprite::onEnter(){
    UseToolsBaseSprite::onEnter();
    HitBodys::getInstance() -> addUseToolsBaseSprite(this);
}

float RubberbandSprite::getRoleSpeedTime(){
    return RUNBBERBAND_SPEED;
}
float RubberbandSprite::getRedians(){
    return rubberAngle;
}
void RubberbandSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
    UseToolsBaseSprite::draw(renderer,transform, flags);
    if ((p1.x != 0 && p1.y != 0) && (p2.x != 0 && p2.y != 0)) {
        _customCommand.init(_globalZOrder);
        _customCommand.func = CC_CALLBACK_0(RubberbandSprite::onDraw, this, transform, flags);
            renderer->addCommand(&_customCommand);
    }
}
void RubberbandSprite::shake(float ft){
    if (isRubber) {
        if (shakeCount %2 == 0) {
            isUp = true;
        } else {
            isUp = false;
        }
        shakeCount++;
    }
}
std::string RubberbandSprite::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_TYPE;
}
void RubberbandSprite::startShake(){
    isRubber = true;
}
void RubberbandSprite::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated){
    if (isRubber) {
        ToolsUtils::drawRubberband(p1,p2,rubberAngle, transform,isUp);
    }else {
        if (isStepOn) {
            /**
             *  已经踩上了
             */
            ToolsUtils::drawRubberband(p1,p2,rubberAngle, transform,false);
        } else {
            ToolsUtils::drawRubberband(p1,p2, transform);
        }

    }

    if(rubberbandPoints.size() == 0){
        if (p1.x < p2.x) {
            rubberbandPoints = JumpHelp::getVec2ByTwoPoint(p1, p2);
        } else {
            rubberbandPoints = JumpHelp::getVec2ByTwoPoint(p2, p1);
        }
    }
}

std::vector<Rect> RubberbandSprite::getRects(){
    return rubberbandPoints;
}
