#include "BackgroundLayer.h"

bool BackgroundLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	number = 0;
	//Ìí¼Ó±³¾°Í¼Æ¬
	addBackground();
	//»Øµ÷º¯Êý£¬Ã¿Ö¡»Øµ÷
	this->scheduleUpdate();
	return true;
}

void BackgroundLayer::addBackground() {
	//ÔÚ²ãÉÏÌù±³¾°Í¼Æ¬bg1
	vSize = Director::getInstance()->getVisibleSize();
	bg1 = Sprite::create(FILENAME);
	//bg1->setScaleX(vSize.width/bg1->getContentSize().width+0.05);
	bg1->setScaleY(vSize.height/bg1->getContentSize().height);
	bg1->setPosition(vSize.width/2,vSize.height/2);
	this->addChild(bg1);
	//ÔÚ²ãÉÏÌù±³¾°Í¼Æ¬bg2
	bg2 = Sprite::create(FILENAME);
	//¸²¸ÇÏñËØ
	//bg2->setScaleX(vSize.width/bg2->getContentSize().width+0.05);
	bg2->setScaleY(vSize.height/bg2->getContentSize().height);
	bg2->setScaleX(-1);
	bg2->setPosition(bg1->getPositionX()+bg1->getBoundingBox().size.width-3,vSize.height/2);
	this->addChild(bg2);
}

void BackgroundLayer::createSprite() {
	this->schedule(schedule_selector(BackgroundLayer::addSprite),2);
}

void BackgroundLayer::update(float t) {
	bg1->setPositionX(bg1->getPositionX()-t*BGMOVESPEED);
	bg2->setPositionX(bg2->getPositionX()-t*BGMOVESPEED);
	if(bg1->getPositionX()+bg1->getBoundingBox().size.width/2 < 0) {
		//createSprite();
		bg1->setPositionX(bg1->getBoundingBox().size.width + bg2->getPositionX()-3);
	}
	if(bg2->getPositionX()+bg2->getBoundingBox().size.width/2 < 0) {
		//createSprite();
		bg2->setPositionX(bg1->getBoundingBox().size.width + bg1->getPositionX()-3);
	}
}

void BackgroundLayer::addSprite(float t) {
	float x = CCRANDOM_0_1()*(vSize.width/2+100)+(vSize.width/3);
	float y = CCRANDOM_0_1()*(vSize.height/2+100)+(vSize.height/4);
	auto sp1 = Sprite::create(SPRITENAME);
	sp1->setVisible(true);
	sp1->setScale(0.2);
	sp1->setPosition(x,y);
	this->addChild(sp1);
	number++;
	if (number == TOTALNUM)
	{
		this->unschedule(schedule_selector(BackgroundLayer::addSprite));
	}
	float dis1 = vSize.width;
	auto move1 = MoveBy::create(dis1/SPRITEMOVESPEED,Vec2(-dis1,0));
	auto cf = CallFunc::create([=](){
		sp1->removeFromParentAndCleanup(true);
	});
	sp1->runAction(Sequence::create(move1,cf,NULL));
}