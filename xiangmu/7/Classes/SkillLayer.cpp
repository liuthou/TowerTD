#include "SkillLayer.h"
#include "RoleAnimate.h"
#include "BossTwo.h"
#include "GameScene.h"
#include "EnemyLayer.h"
#include "BaseEnemy.h"
#include "HeroLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool SkillLayer::init(){
	if(!Layer::init()){
		return false;
	}

	this->schedule(schedule_selector(SkillLayer::update),0,-1,7);
	return true;
}

void SkillLayer::addSkillOne(){
	auto rscene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto herolayer = dynamic_cast<HeroLayer *>(rscene->getHeroLayer());
	auto hero = herolayer->getHero();
	
	Sprite * iceRain = Sprite::createWithSpriteFrameName("IceSwordRain1.png");
	iceRain->setName("iceRain");
	iceRain->setPosition(Vec2(hero->getPositionX(),800));
	this->addChild(iceRain);
	
	auto moveby = MoveBy::create(1.5,Vec2(0,-750));
	std::vector<std::string>fileNames;
	for (int i = 1;i <= 6 ;i++){
		std::string fileName = StringUtils::format("iceBroke%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.2,1);
	auto cf = CCCallFunc::create([=](){
		iceRain->removeFromParentAndCleanup(true);
	});
	auto iceblink = RoleAnimate::getinstance()->iceBlink();
	auto cf1 = CCCallFunc::create([=](){
		unsigned type = CCRANDOM_0_1() * 4 + 11;
		std::string fileName = StringUtils::format("enemy%dHurt_01.png",type);
		
		auto rscene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
		auto enemylayer = rscene->getEnemyLayer();
		enemylayer->add(iceRain->getPosition(),50,type,Size(40,60),fileName,3);
		SimpleAudioEngine::getInstance()->playEffect("icerainhit.wav");
	});
	auto spa = Spawn::create(moveby,iceblink,NULL);
	auto seq = Sequence::create(spa,cf1,iceblink,cf,NULL);

	iceRain->runAction(seq);
}

void SkillLayer::addSkillTwo(){
	auto rscene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto enemylayer = dynamic_cast<EnemyLayer *>(rscene->getEnemyLayer());
	auto herolayer = dynamic_cast<HeroLayer *>(rscene->getHeroLayer());
	auto hero = herolayer->getHero();
 	bosstwo = (BossTwo *)enemylayer->getChildByTag(3000);
	if(bosstwo->getbossTwoDirection() == 1){
		Sprite * snackskill = Sprite::createWithSpriteFrameName("SnackSkill1.png");
		snackskill->setName("snackskill");
		snackskill->setPosition(bosstwo->getPosition());
		snackskill->setScale(0.5);
		this->addChild(snackskill);
		
		auto ani = RoleAnimate::getinstance()->SnackSkill();
		auto moveby = MoveBy::create(1,Vec2(400,0));
		auto cf = CCCallFunc::create([=](){
			snackskill->removeFromParentAndCleanup(true);
		});
		auto spw = Spawn::create(ani,moveby,NULL);
		auto seq = Sequence::create(spw,cf,NULL);
		snackskill->runAction(seq);
	}else{
		Sprite * snackskill = Sprite::createWithSpriteFrameName("SnackSkill1.png");
		snackskill->setName("snackskill");
		snackskill->setPosition(bosstwo->getPosition());
		snackskill->setScale(0.5);
		if(snackskill->getBoundingBox().containsPoint(hero->getPosition())){
			hero->die();
		}
		this->addChild(snackskill);
		auto ani = RoleAnimate::getinstance()->SnackSkill();
		auto moveby = MoveBy::create(1,Vec2(-400,0));
		auto cf = CCCallFunc::create([=](){
			snackskill->removeFromParentAndCleanup(true);
		});
		auto spw = Spawn::create(ani,moveby,NULL);
		auto seq = Sequence::create(spw,cf,NULL);
		snackskill->runAction(seq);
	}
}

void SkillLayer::update(float t){
	auto rscene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto herolayer = dynamic_cast<HeroLayer *>(rscene->getHeroLayer());
	auto hero = herolayer->getHero();
	Sprite *snackskill = this->getChildByName<Sprite *>("snackskill");
	if(snackskill != nullptr){
		if(snackskill->getBoundingBox().containsPoint(hero->getPosition())){
			hero->hurt();
			snackskill->removeFromParentAndCleanup(true);
		}
	}
	auto iceRain = this->getChildByName<Sprite *>("iceRain");
	if (iceRain != nullptr){
		if(iceRain->getBoundingBox().containsPoint(hero->getPosition())){
			hero->hurt();
			iceRain->removeFromParentAndCleanup(true);
		}
	}
}