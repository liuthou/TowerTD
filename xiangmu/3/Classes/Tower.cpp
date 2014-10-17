#include "Tower.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "TowerAttribute.h"
#include "TowerAttributeConfType.h"
#include "EntityManager.h"
#include "MainScene.h"
#include "TowerAI.h"
#include "MapLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool Tower::init(int id){
	auto instance = TowerAttribute::getInstance(id);
	auto filename = instance->getStringAttribute(Tower_Runanimate,"long.png");
	this->hp = instance->getIntAttribute(Tower_HP,3);
	this->def = instance->getIntAttribute(Tower_Defence,50);
	this->scope =instance->getIntAttribute(Tower_AttackScope,200);
	this->firespeed = instance->getIntAttribute(Tower_Firespeed,1);
	this->buName = instance->getStringAttribute(Tower_Bullet_Pic,"jiantou.png");
	this->buattackValue = instance->getIntAttribute(Tower_Attack,50);
	this->buspeed = instance->getIntAttribute(Tower_Bullet_FlySpeed,100);
	this->price = instance->getIntAttribute(Tower_Price,50);
	this->atteffect.firetime = instance->getIntAttribute(Tower_Firetime,0);
	this->atteffect.frozentime = instance->getIntAttribute(Tower_Frozentime,0);
	this->atteffect.lowspeedtime = instance->getIntAttribute(Tower_Lowspeedtime,0);
	this->isdie = false;
	if (!Sprite::initWithFile(filename))return false;
	return true;
}
void Tower::onEnter(){
	Sprite::onEnter();
	//Tower贴不上,木有办法了...
	ai = TowerAI::create(this);
	auto scene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	//记得remove自己时先把ai移除
	scene->getGameLayer()->addChild(ai);
}
Tower* Tower::create(int id){
	auto tow = new Tower();
	if (tow &&tow->init(id)){
		tow->autorelease();
		return tow;
	}
	CC_SAFE_DELETE(tow);
	return nullptr;
}
void Tower::fire (Sprite* monster){
	//回调单例的方法,获取目标
	//创建子弹
	//加音效
	SimpleAudioEngine::getInstance()->playEffect("TowerAttack.wav");
	auto bu = Bullet::create(buName,monster->getPosition(),this->getPosition(),buspeed,buattackValue,scope,atteffect);
	log("Tower fire!!(%f,%f)",monster->getPosition().x,monster->getPosition().y);
	bu->setPosition(this->getPosition());
	auto scene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	scene->getGameLayer()->addChild(bu);
	EntityManager::getInstance()->TowerBullet.pushBack(bu);
}
void Tower::remove(){
	this->stopAllActions();
	this->unscheduleAllSelectors();
	ai->removeFromParent();
	this->setIsdie(true);
	this->removeFromParentAndCleanup(true);
}
void Tower::towerhurt(int monsterAttack){
	this->hp-=monsterAttack;
	if (this->hp<=0){
		this->setIsdie(true);
		this->runAction(Blink::create(0.5,2));
		die();
	}
}
void Tower::die(){
	auto mainscene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	//修改塔所在位置上的地图的相应GID
	mainscene->getMapLayer()->removeGID(this->getPosition());
	//做死亡动画
	//做完动画再掉remove
}
