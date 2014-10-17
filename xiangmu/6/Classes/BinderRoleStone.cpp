#include "BinderRoleStone.h"
#include "SystemMarcoUtil.h"
#include "HitBodys.h"
#include "JumpHelp.h"
#include "ConfigUtil.h"
BinderRoleStone * BinderRoleStone::create()
{
	BinderRoleStone *pRet = new BinderRoleStone();
	if (pRet && pRet->init()) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	}
	else 
	{ 
		CC_SAFE_DELETE(pRet); 
		return NULL; 
	} 
}

bool BinderRoleStone::init()
{
	if (!ToolsBaseControlUserScript::init())
	{
		return false;
	}	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stone.plist");
	this->initWithSpriteFrameName("stone1.png");
	setScale(0.5f);
	HitBodys::getInstance()->addToolsBaseControlUserScript(this);

	auto binderStoneAnimation = Animation::create();
	SpriteFrame * binderStoneSprite2;
	binderStoneSprite2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("stone1.png");
	binderStoneAnimation->addSpriteFrame(binderStoneSprite2);
	binderStoneSprite2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("stone2.png");
	binderStoneAnimation->addSpriteFrame(binderStoneSprite2);
	binderStoneAnimation->setDelayPerUnit(0.1);
	binderStoneAnimation->setLoops(-1);
	auto binderStoneAnimate = Animate::create(binderStoneAnimation);
	auto move_binderStonSprite1 = MoveBy::create(10,Vec2(0,-1000));
	this->runAction(Spawn::create(binderStoneAnimate, move_binderStonSprite1,NULL));
	return true;
}
std::string BinderRoleStone::sendCast(){
    return BINDER_ENEMY_HIT_ROLE;
}

Direction_ROLE BinderRoleStone::collitionDirection(){
	return Direction_ROLE::UP;
}
void BinderRoleStone::changeRoleState(){
   //role die
	
}
int BinderRoleStone::controleRoleSpeed(){
	return NO_CHANGE_ROLE_SPEED;
}
void BinderRoleStone::collisionRole(){

}

