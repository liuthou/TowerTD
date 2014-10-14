#include "MainplanLayer.h"
#include "Mainplan.h"
bool MainplanLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//放置主机
	//屏幕的适配大小
	Size vSize =Director::getInstance()->getVisibleSize();
	auto hero = Mainplan::create();
	hero->setPosition(vSize.width/2,vSize.height/6);
	this->addChild(hero);
	//增加Touch处理
	auto dis = Director::getInstance()->getEventDispatcher();
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan=[=](Touch * t,Event *e)->bool{
		//如果点击飞机上返回true
		if(hero->getBoundingBox().containsPoint(t->getLocation()))
		{
			return true;
		}
		return false;
	};
	//处理手指移动的位置。
	listen->onTouchMoved=[=](Touch * t,Event *e){
		Point movePoint =t->getLocation();
		//Touch 的左边界。
		float pleft = movePoint.x-hero->getContentSize().width/2;
		//如果超出layer的碰撞框,重置movePoint的x为飞机宽度一办。
		if(pleft < this->getBoundingBox().origin.x)
		{
			movePoint.x =hero->getContentSize().width/2;
		}
		float pright = movePoint.x+hero->getContentSize().width/2;
		if(pright > this->getBoundingBox().size.width )
		{
			movePoint.x =this->getBoundingBox().size.width-hero->getContentSize().width/2;
		}
		float pup = movePoint.y+hero->getContentSize().height/2;
		if(pup > this->getBoundingBox().size.height)
		{
			movePoint.y =this->getBoundingBox().size.height-hero->getContentSize().height/2;
		}
		float pdown = movePoint.y-hero->getContentSize().height/2;
		if(pdown < this->getBoundingBox().origin.y)
		{
			movePoint.y =hero->getContentSize().height/2;
		}
		hero->setPosition(movePoint);
	};
	dis->addEventListenerWithSceneGraphPriority(listen,this);
	return true;
}