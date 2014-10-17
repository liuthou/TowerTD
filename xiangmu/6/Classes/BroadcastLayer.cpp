//
//  BroadcastLayer.cpp
//  heroJump
//
//  Created by mazhai on 14-9-23.
//
//

#include "BroadcastLayer.h"
#include "HitBodys.h"
#include "JumpHelp.h"
#include "ConfigUtil.h"
#include "EnemySprite.h"
#include "IceSprite.h"
#include "IceSecondSprite.h"
#include "JumpParameter.h"
bool BroadcastLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    this -> scheduleUpdate();
    return true;
}

void BroadcastLayer::update(float ft){

    checkUseTools(ft);

    checkTools(ft);

    
}

void BroadcastLayer::checkUseTools(float ft){
    for(auto ite = HitBodys::getInstance() ->getUseToolsBaseSprite().begin();
        ite != HitBodys::getInstance() ->getUseToolsBaseSprite().end();++ite){
        if (!(JumpHelp::getRoleSprite() -> jParameter) || JumpHelp::getRoleSprite() -> jParameter == nullptr)
        {
			continue;
        }
        if (((*ite) -> isDie)) {
            continue;
        }
        RoleSprite * rs = JumpHelp::getRoleSprite();
        Rect rsRect = Rect(rs->getBoundingBox().origin.x,rs->getBoundingBox().origin.y,rs->getBoundingBox().size.width,10);
        JumpParameter *j = rs -> jParameter;
        if(j -> getUser_role_direction() == Direction_ROLE::DOWN){
            std::vector<Rect> rects = (*ite) -> getRects();
            for (auto ite2 = rects.begin(); ite2 != rects.end(); ++ite2) {
                Vec2 usetoolsOnBack = ((*ite) -> getParent()) -> convertToWorldSpace((*ite2).origin);
                Rect rect(usetoolsOnBack.x,usetoolsOnBack.y - 25,(*ite2).size.width,((*ite2).size.height - 10) < 1? 1:((*ite2).size.height - 10));
                
                if (rsRect.intersectsRect(rect)) {
                    (*ite) -> collisionRole();
                    auto center = __NotificationCenter::getInstance();
                    center -> postNotification((*ite) -> sendCast(), *ite);
                    break;
                }
            }
        }
    }
}
/**
 *  用于实现砖块等等得和主角的碰撞
 *
 *  type void
 */
void BroadcastLayer::checkTools(float ft){
    for (auto ite = HitBodys::getInstance() ->getToolsBaseControlUserScript().begin();
         ite != HitBodys::getInstance() ->getToolsBaseControlUserScript().end();) {
        if (!(JumpHelp::getRoleSprite() -> jParameter) || JumpHelp::getRoleSprite() -> jParameter == nullptr)
        {
			++ite;
            continue;
        }
        if (!(*ite) || (*ite) -> getDie()) {
            ++ite;
            continue;
        }

        /**
         *  主角方向向上可以碰撞金币
         *  主角方向向下的时候可以碰撞金币以及石阶等
         */
        bool flag = (*ite) -> collitionDirection() == Direction_ROLE::UP;
        Vec2 toolsOnBack;
        auto layer = dynamic_cast<Layer*>((*ite) -> getParent());
        if ((!layer) || nullptr == layer) {
            ++ite;
            continue;
        }
        auto backgoundLayer = layer-> getParent();
        if ((!backgoundLayer) || nullptr == backgoundLayer) {
            ++ite;
            continue;
        }
        JUMP_LOG("backgoundLayerName = %s",backgoundLayer -> getName().c_str());
        
        toolsOnBack = ((*ite) -> getParent()) -> convertToWorldSpace((*ite) -> getPosition());
        
        JUMP_LOG("toolsOnBack.y = %.2f",toolsOnBack.y);
        Rect rect(toolsOnBack.x,(toolsOnBack.y),((*ite) -> getBoundingBox().size.width) * 0.3,(((*ite) -> getBoundingBox().size.height) * 0.3 + (JumpHelp::getRoleSprite() -> getBoundingBox().size.height)/3));
        
        Rect rRole(JumpHelp::getRoleSprite() -> getBoundingBox().origin.x,
                   JumpHelp::getRoleSprite() -> getBoundingBox().origin.y + (JumpHelp::getRoleSprite() -> getBoundingBox().size.height)/2,
                   JumpHelp::getRoleSprite() -> getBoundingBox().size.width,
                   JumpHelp::getRoleSprite() -> getBoundingBox().size.height/2);
        if (rRole.intersectsRect(rect)) {
            if (flag) {
                (*ite) -> collisionRole();
                JumpHelp::getRoleSprite() -> acttck((*ite) -> attack());
                auto center = __NotificationCenter::getInstance();
                center -> postNotification((*ite) -> sendCast(), *ite);
            } else if(JumpHelp::getRoleSprite() -> jParameter -> getUser_role_direction() == (*ite) -> collitionDirection()){
                (*ite) -> collisionRole();
                JumpHelp::getRoleSprite() -> acttck((*ite) -> attack());
                auto center = __NotificationCenter::getInstance();
                center -> postNotification((*ite) -> sendCast(), *ite);
            } else {
                ++ite;
            }

            break;
        } else {
            ++ite;
        }
        
    }
}