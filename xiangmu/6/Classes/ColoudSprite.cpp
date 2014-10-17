//
//  ColoudSprite.cpp
//  herojump
//
//  Created by lanou3g on 14-10-8.
//
//

#include "ColoudSprite.h"
#include "HitBodys.h"
#include "JumpHelp.h"
bool ColoudSprite::init(std::string fileName,int m_id){
	if (!ToolsBaseControlUserScript::init()){
		return false;
	}
	cloud = Sprite::create(fileName);
    this->addChild(cloud);
    
	vSize = Director::getInstance()->getVisibleSize();
	pSize = this->getContentSize();
	m_speed = 50;
	m_number = m_id;
    auto sp = MoveBy::create(vSize.width/m_speed,Vec2(vSize.width - pSize.width/2,-vSize.height/2));
    auto setdie = CallFunc::create([=](void){
        this -> die();
    });
    auto sff = Sequence::create(sp,setdie,NULL);
    this->runAction(sff);
	HitBodys::getInstance()->addToolsBaseControlUserScript(this);
	return true;
    
}
ColoudSprite * ColoudSprite::create(std::string fileName,int m_id){
	ColoudSprite * ice = new ColoudSprite();
    if (ice && ice->init(fileName,m_id)){
		ice->autorelease();
		return ice;
	}
	CC_SAFE_DELETE(ice);
	return nullptr;
}
std::string ColoudSprite::sendCast(){
    return COLOUD_ENEMY_HIT_ROLE;
}
Direction_ROLE ColoudSprite::collitionDirection(){
	return Direction_ROLE::UP;
}
int ColoudSprite::controleRoleSpeed(){
	return NO_CHANGE_ROLE_SPEED;
}
void ColoudSprite::collisionRole(){
	JumpHelp::getRoleSprite() -> hitIce();
}
void ColoudSprite::changeRoleState(){
//    auto sp = MoveBy::create(vSize.width/m_speed,Vec2(vSize.width - pSize.width/2,-vSize.height/2));
//    auto setdie = CallFunc::create([=](void){
//        this->setDie(true);
//        this->removeFromParentAndCleanup(true);
//    });
//    auto sff = Sequence::create(sp,setdie,NULL);
//    this->runAction(sff);

}