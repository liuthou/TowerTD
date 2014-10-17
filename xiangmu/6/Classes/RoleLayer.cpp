//
//  RoleLayer.cpp
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#include "RoleLayer.h"
#include "JumpHelp.h"
bool RoleLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    role = RoleSprite::create();
    role -> setPosition(Vec2(getContentSize().width/2, role -> getContentSize().height/2) );
    role -> setName(ROLE_SPRITE);
    this -> addChild(role);
    this -> setAccelerometerEnabled(true);
    this -> setAccelerometerInterval(0.001);
    auto accelerationLitener = EventListenerAcceleration::create(CC_CALLBACK_2(RoleLayer::onAccelerationForRole, this));
    Director::getInstance() -> getEventDispatcher() -> addEventListenerWithSceneGraphPriority(accelerationLitener, this);
    accelerationFlag = true;
    return true;
}
void RoleLayer::onAccelerationForRole(Acceleration* acc, Event* event){
    if (!accelerationFlag) {
        return;
    }
    if (role == nullptr) {
        return;
    }
    if (JumpHelp::getRoleSprite() -> prepareToJumpFlag) {
        return;
    }
    
    auto ballSize=role->getContentSize();
    auto pos=role->getPosition();
    
    pos.x += acc->x * 9.81f;
//    pos.y += acc->y * 9.81f;
    
    FIX_POS(pos.x,(ballSize.width/2) - 14,(GET_WINDOWS_SIZE.width-ballSize.width/2) + 14);
//    FIX_POS(pos.y,(ballSize.height/2),(visibleSize.height-ballSize.height/2));
    role->setPositionX(pos.x);

}

void RoleLayer::onEnter(){
    Layer::onEnter();
}


