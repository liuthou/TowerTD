#include "SuperBigskills.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;
Superbigskills *Superbigskills::create(int type)
{
	auto pef = new Superbigskills();
	if (pef&&pef->init(type))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool Superbigskills::init(int type){
	if(!Sprite::init()){
		return false;
	}

	Armature* skillsamt = Armature::create("skillsAnimation");
	this->addChild(skillsamt);
	if(type==1){
		skillsamt->getAnimation()->play("wireskills");
	}else if(type==2){
		skillsamt->getAnimation()->play("iceskills");
	}else if(type==3){
		skillsamt->getAnimation()->play("fireskills");
	}
	
	return true;
}
void Superbigskills::iceHurt(){
	auto vector = GameManager::getInstance()->enemyVector;
	for (auto iter = vector.begin();iter != vector.end();iter++)
	{
		(*iter)->hurt(30,ICE);
	}
}
void Superbigskills::firehurt(){
	auto vector = GameManager::getInstance()->enemyVector;
	for (auto iter = vector.begin();iter != vector.end();iter++)
	{
		(*iter)->hurt(35,FIRE);
	}
}
void Superbigskills::wireHurt(){
	auto vector = GameManager::getInstance()->enemyVector;
	for (auto iter = vector.begin();iter != vector.end();iter++)
	{
		(*iter)->hurt(30,WIRE);
	}
}