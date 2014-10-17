#include "ToolAnimationSprite.h"
#include "ConfigUtil.h"
bool ToolAnimationSprite::init(std::string fileName,int t_id){
	if (!Sprite::initWithSpriteFrameName(fileName)){
		return false;
	}
	m_id = t_id;
	return true;
}
ToolAnimationSprite * ToolAnimationSprite::create(std::string fileName,int t_id){
	ToolAnimationSprite * tas = new ToolAnimationSprite();
	if (tas && tas->init(fileName,t_id)){
		tas->autorelease();
		return tas;
	}
	CC_SAFE_DELETE(tas);
	return nullptr;
}
void ToolAnimationSprite::onEnter(){
	Sprite::onEnter();
	changeRoleState1();

}
void ToolAnimationSprite::changeRoleState1(){
	auto cache = SpriteFrameCache::getInstance();
	SpriteFrame * sp;
	Animation * ani = Animation::create();
	std::string fileName;

	if (FAZHEN6 == m_id){
		for (int i = 18; i < 28; i++){
			fileName = StringUtils::format("%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	} else

	if (FAZHEN5 == m_id){
		for (int i = 86; i < 98; i++){
			fileName = StringUtils::format("%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	} else

	if (FAZHEN4 == m_id){
		for (int i = 58; i < 68; i++){
			fileName = StringUtils::format("%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	} else

	if (FAZHEN3 == m_id){
		for (int i = 42; i < 58; i++){
			fileName = StringUtils::format("%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	} else

	if (FAZHEN2 == m_id){
		for (int i = 30; i < 42; i++){
			fileName = StringUtils::format("%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	} else

	if (FAZHEN1 == m_id){
		for (int i = 0; i < 18; i++){
			fileName = StringUtils::format("%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	} else if (BINDBOOM == m_id){
		for (int i = 1; i < 8; i++){
			fileName = StringUtils::format("stone%d.png",i);
			sp = cache->getSpriteFrameByName(fileName);
			ani->addSpriteFrame(sp);
		}
	}

	ani->setDelayPerUnit(0.1);
	ani->setLoops(1);
	Animate * amt = Animate::create(ani);
	auto sf = CallFunc::create([=](void){
		this->removeFromParentAndCleanup(true);
	});
	auto ant = Sequence::create(amt,sf,NULL);
	this->runAction(ant);
	
}