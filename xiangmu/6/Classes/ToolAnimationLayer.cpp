#include "ToolAnimationLayer.h"
#include "ToolAnimationSprite.h"
#include "JumpHelp.h"
#include "EnemySprite.h"
#include "IceSprite.h"
#include "IceSecondSprite.h"
#include "JumpHelp.h"
#include "ColoudSprite.h"
#include "LineSprite.h"
#include "ConfigUtil.h"

#include "BinderRoleStone.h"
bool ToolAnimationLayer::init(){
	if (!Layer::init()){
		return false;
	}
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fazhen4.plist");
	touchNumber = 1;
	auto center = __NotificationCenter::getInstance();
//	senter->addObserver(this,callfuncO_selector(ToolAnimationLayer::recfEnemy),EATE_TOOLS_ENEMYSPRITE_USER,nullptr);
    center->addObserver(this,callfuncO_selector(ToolAnimationLayer::roleHitGost),GOST_EMEMY_HIT_ROLE,nullptr);
    center->addObserver(this,callfuncO_selector(ToolAnimationLayer::roleHitColoud),COLOUD_ENEMY_HIT_ROLE,nullptr);
    center->addObserver(this,callfuncO_selector(ToolAnimationLayer::roleHitShit),SHIT_ENEMY_HIT_ROLE,nullptr);
    center->addObserver(this,callfuncO_selector(ToolAnimationLayer::roleHitdou),DOU_ENEMY_HIT_ROLE,nullptr);
    center->addObserver(this,callfuncO_selector(ToolAnimationLayer::roleHitBinder),BINDER_ENEMY_HIT_ROLE,nullptr);
	return true;
}
void ToolAnimationLayer::onEnter(){
	Layer::onEnter();
	
}
void ToolAnimationLayer::roleHitdou(Ref *sender){
    auto sp = ToolAnimationSprite::create("0.png",3);
    auto p_height = sp->getContentSize().height/2;
    auto p_width = sp->getContentSize().width/2;
    sp->setPosition(JumpHelp::getRoleSprite()->getPositionX() + p_width,JumpHelp::getRoleSprite()->getPositionY() + p_height);
    this->addChild(sp);
    auto dou = dynamic_cast<LineSprite *>(sender);
    if (dou!= NULL) {
        dou -> die();
    }
}
void ToolAnimationLayer::roleHitShit(Ref *sender){
    auto sp = ToolAnimationSprite::create("0.png",6);
    auto p_height = sp->getContentSize().height/2;
    auto p_width = sp->getContentSize().width/2;
    sp->setPosition(JumpHelp::getRoleSprite()->getPositionX() + p_width-25,JumpHelp::getRoleSprite()->getPositionY() + p_height-25);
    this->addChild(sp);
    auto shit = dynamic_cast<EnemySprite *>(sender);
    if (shit!= NULL) {
        shit -> die();
    }
}
void ToolAnimationLayer::roleHitBinder(Ref *sender){
    auto sp = ToolAnimationSprite::create("0.png",7);
    auto p_height = sp->getContentSize().height/2;
    sp->setPosition(JumpHelp::getRoleSprite()->getPositionX(),JumpHelp::getRoleSprite()->getPositionY() + p_height);
    this->addChild(sp);
    auto binder = dynamic_cast<BinderRoleStone *>(sender);
    if (binder!= NULL) {
        binder -> die();
    }
}
void ToolAnimationLayer::roleHitColoud(Ref *sender){
    auto sp = ToolAnimationSprite::create("0.png",5);
    auto p_height = sp->getContentSize().height/2;
    sp->setPosition(JumpHelp::getRoleSprite()->getPositionX(),JumpHelp::getRoleSprite()->getPositionY() + p_height);
    this->addChild(sp);
    auto coloud = dynamic_cast<ColoudSprite*>(sender);
    if (NULL!= coloud) {
        coloud -> die();
    }
}
void ToolAnimationLayer::roleHitGost(Ref *sender){
    auto gost = dynamic_cast<IceSprite*>(sender);
    auto sp = IceSecondSprite::create("PBStar-21.png");
    auto p_height = sp->getContentSize().height/2;
    sp->setPosition(JumpHelp::getRoleSprite()->getPositionX(),JumpHelp::getRoleSprite()->getPositionY() - p_height);
    this->addChild(sp);
    if (gost != NULL) {
        gost -> die();
    }
}
