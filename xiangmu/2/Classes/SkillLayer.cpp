#include "SkillLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
#include "SelectRole.h"
bool SkillLayer::init(){
	if(!Layer::init()){
		return false;
	}
	
	return true;
}
void SkillLayer::addSkill(){
	SelectRole::getInstence()->getRoleArmatures().at(0)->setArmaturestatic(skillStatic);
 	Armature *skill = Armature::create("skill");
 	skill->getAnimation()->play("skill");
 	if(SelectRole::getInstence()->getEnemyArmatures().size()>0){
 		skill->setPosition(SelectRole::getInstence()->getEnemyArmatures().at(0)->getPosition());
 	}else{
 		skill->setPosition(480,320);
 	}
 	this->addChild(skill);
	auto attacktime = DelayTime::create(0.8);
 	auto skillAttack = CallFunc::create([=](){
 		auto enemys = SelectRole::getInstence()->getEnemyArmatures();
		for(int i = 0;i< enemys.size();i++){
			auto enemy = enemys.at(i);
			if(enemy->getBoundingBox().intersectsRect(skill->getBoundingBox())){
				enemy->setHp(enemy->getAttackValue()+30);;
			}
		}
 	});
	auto seqAttack = Sequence::create(attacktime,skillAttack,nullptr);
	this->runAction(seqAttack);
 	auto delayTime = DelayTime::create(1.5);
	auto killskill = CallFunc::create([=](){
		skill->removeFromParentAndCleanup(true);
	});
 	auto seq = Sequence::create(delayTime,killskill,nullptr);
 	this->runAction(seq);
}
void SkillLayer::listenAddSkill(Ref *sender){
	this->addSkill();
}
void SkillLayer::onEnter(){
	Layer::onEnter();
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(SkillLayer::listenAddSkill),"skill",nullptr);
}
void SkillLayer::onExit(){
	__NotificationCenter::getInstance()->destroyInstance();
	Layer::onExit();
}