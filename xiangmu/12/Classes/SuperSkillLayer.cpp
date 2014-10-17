#include "SuperSkillLayer.h"
#include "SuperSkill.h"
#include "GameManager.h"

SuperSkillLayer * SuperSkillLayer::create()
{
	auto pef = new SuperSkillLayer();
	if (pef&&pef->init())
	{   
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool SuperSkillLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    sprite = nullptr;
	this->type=1;
	//火大招
	auto fireMenu = Sprite::create("fireskills.png");
	fireMenu->setPosition(1060,50);
	fireMenu->setScale(1.5);
	this->addChild(fireMenu);
	firecoolingBar = CCProgressTimer::create(Sprite::create("fireitem2.png"));
	firecoolingBar->setType(ProgressTimer::Type::BAR);
	firecoolingBar->setMidpoint(Point(0,0.5f));
	firecoolingBar->setBarChangeRate(Point(1,0));
	firecoolingBar->setPercentage(100);
	firecoolingBar->setPosition(Point(fireMenu->getContentSize()/ 2));
	firecoolingBar->setRotation(-90);
	fireMenu->addChild(firecoolingBar);
	//冰大招
	auto iceMenu = Sprite::create("iceskills.png");
	iceMenu->setPosition(1140,50);
	iceMenu->setScale(1.5);
	this->addChild(iceMenu);
	icecoolingBar = CCProgressTimer::create(Sprite::create("iceitem2.png"));
	icecoolingBar->setType(ProgressTimer::Type::BAR);
	icecoolingBar->setMidpoint(Point(0,0.5f));
	icecoolingBar->setBarChangeRate(Point(1,0));
	icecoolingBar->setPercentage(100);
	icecoolingBar->setPosition(Point(iceMenu->getContentSize()/2));
	icecoolingBar->setRotation(-90);
	iceMenu->addChild(icecoolingBar);
	//雷电大招
	auto wireMenu = Sprite::create("wireskills.png");
	wireMenu->setPosition(980,50);
	wireMenu->setScale(1.5);
	this->addChild(wireMenu);
	wirecoolingBar = CCProgressTimer::create(Sprite::create("wireitem2.png"));
	wirecoolingBar->setType(ProgressTimer::Type::BAR);
	wirecoolingBar->setMidpoint(Point(0,0.5f));
	wirecoolingBar->setBarChangeRate(Point(1,0));
	wirecoolingBar->setPercentage(100);
	wirecoolingBar->setPosition(Point(wireMenu->getContentSize()/ 2));
	wirecoolingBar->setRotation(-90);
	wireMenu->addChild(wirecoolingBar);
	//风大招
	auto windMenu = Sprite::create("windskills.png");
	windMenu->setPosition(900,50);
	windMenu->setScale(1.5);
	this->addChild(windMenu);
	windcoolingBar = CCProgressTimer::create(Sprite::create("winditem2.png"));
	windcoolingBar->setType(ProgressTimer::Type::BAR);
	windcoolingBar->setMidpoint(Point(0,0.5f));
	windcoolingBar->setBarChangeRate(Point(1,0));
	windcoolingBar->setPercentage(100);
	windcoolingBar->setPosition(Point(windMenu->getContentSize()/ 2));
	windcoolingBar->setRotation(-90);
	windMenu->addChild(windcoolingBar);

    listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t,Event *e){
		if (fireMenu->getBoundingBox().containsPoint(t->getLocation())||
			iceMenu->getBoundingBox().containsPoint(t->getLocation())||
			wireMenu->getBoundingBox().containsPoint(t->getLocation())||
			windMenu->getBoundingBox().containsPoint(t->getLocation())){
				if(fireMenu->getBoundingBox().containsPoint(t->getLocation())){
					this->type=1;
				}else if(iceMenu->getBoundingBox().containsPoint(t->getLocation())){
					this->type=2;
				}else if(wireMenu->getBoundingBox().containsPoint(t->getLocation())){
					this->type=4;
				}else if(windMenu->getBoundingBox().containsPoint(t->getLocation())){
					this->type=3;
				}
		listener->setSwallowTouches(true);
		sprite = Sprite::createWithSpriteFrameName("skills.png");
		this->addChild(sprite);
		sprite->setPosition(t->getLocation());
		return true;
		}else{
			return false;
		}};
	listener->onTouchMoved = [&](Touch *t,Event *e){
		
		auto point = this->convertTouchToNodeSpace(t);
		
		if (sprite == nullptr)
		{
			return;
		}
		sprite->setPosition(sprite->getPosition()+t->getDelta());
	};
	listener->onTouchEnded = [=](Touch *t,Event *e){
		if (sprite == nullptr)
		{
			return;
		}
		auto points = GameManager::getInstance()->getStageLayer()->convertToNodeSpace(sprite->getPosition());
		if(type==1&&firecoolingBar->getPercentage()==0){
			SimpleAudioEngine::getInstance()->playEffect("TITANHEAD_DEATH.mp3");
		auto skill = SuperSkill::create(points,type);
		firecoolingBar->setPercentage(100);
		}else if(type==2&&icecoolingBar->getPercentage()==0){
			 SimpleAudioEngine::getInstance()->playEffect("iceMagicSound.wav");
			auto skill = SuperSkill::create(points,type);
			icecoolingBar->setPercentage(100);
		}else if(type==3&&windcoolingBar->getPercentage()==0){
			SimpleAudioEngine::getInstance()->playEffect("abstacleDestroy.wav");
			auto skill = SuperSkill::create(points,type);
			windcoolingBar->setPercentage(100);
		}else if(type==4&&wirecoolingBar->getPercentage()==0){
			SimpleAudioEngine::getInstance()->playEffect("LINA_ATK3.mp3");
			auto skill = SuperSkill::create(points,type);
			wirecoolingBar->setPercentage(100);
		}else{
			auto skillssp = Sprite::create("jinenglenque.png");
			skillssp->setPosition(1020,100);
			this->addChild(skillssp);
			auto sf =CallFunc::create([=](){skillssp->removeFromParentAndCleanup(true);});
			skillssp->runAction(Sequence::create(DelayTime::create(0.5),sf,NULL));
		}
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
		listener->setSwallowTouches(false);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	this->schedule(schedule_selector(SuperSkillLayer::updateSkills),1);
	return true;
}
void SuperSkillLayer::updateSkills(float t){
	icecoolingBar->setPercentage(icecoolingBar->getPercentage()-10);
	firecoolingBar->setPercentage(firecoolingBar->getPercentage()-10);
	wirecoolingBar->setPercentage(wirecoolingBar->getPercentage()-10);
	windcoolingBar->setPercentage(windcoolingBar->getPercentage()-10);
}
SuperSkillLayer::~SuperSkillLayer()
{
	_eventDispatcher->removeEventListener(listener);
}