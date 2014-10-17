#include "RaiseAnimation.h"


bool RaiseAnimation::init(){
	if (!Layer::init())
	{
		return false;
	}

	chip = 0;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("raise.plist");
	raise_4 = Sprite::createWithSpriteFrameName("raise_4.png");
	raise_1 = Sprite::createWithSpriteFrameName("raise_1.png");
	yellowScrol = LoadingBar::create("raise_2.png",10);
	
	raise_1->setPosition(480,400);
	raise_4->setPosition(480,300);
	initPosition = raise_4->getPosition();

	raise_1->setScale(0.5);
	raise_4->setScale(0.5);
	
	this->addChild(raise_1);
	this->addChild(raise_4,10);
	this->addChild(yellowScrol);
	
	return true;
}

void RaiseAnimation::pushButton(){

	auto dis = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch * t, Event * e){
		if (raise_4->getBoundingBox().containsPoint(t->getLocation()))
		{					
			yellowScrol->setRotation(-90);
			yellowScrol->setPosition(Vec2(487,420));
			yellowScrol->setScale(0.5);
			yellowScrol->setAnchorPoint(Vec2(0.5,0));
		
			return true;
		}
		return false;
	};

	listener->onTouchMoved = [=](Touch * t, Event * e){		
		Point p ;
		p.y = t->getLocation().y;
		p.x = raise_4->getPositionX();
		if (p.y >= (raise_1->getPositionY()-raise_1->getContentSize().height*0.5/2 + 60)
			&& p.y <= (raise_1->getPositionY()+raise_1->getContentSize().height*0.5/2))
		{
			raise_4->setPositionY(p.y);
			float percent = (p.y-initPosition.y)/2.08f;
			//根据百分比给chip赋值
			chip = percent * 4;
			yellowScrol->setPercent(percent);
			//log("------------------%.2f",percent);	
		}		
	};

	listener->onTouchEnded = [&](Touch * t, Event * e){
		chip = (t->getLocation().y - initPosition.y) * 5;	
		if (t->getLocation().y >= raise_1->getPositionY() + raise_1->getContentSize().height*0.5/2)
		{
			auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName("raise_5.png");
			
			auto texture = sf->getTexture();
			raise_4->setTexture(texture);
			
		}
	};

	dis->addEventListenerWithSceneGraphPriority(listener,this);
}
