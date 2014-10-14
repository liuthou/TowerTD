#include "backgroundlayer.h"

bool backgroundlayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//得到屏幕显示区的大小。
	vSize = Director::getInstance()->getVisibleSize();
	//增加背景
	bg1 =Sprite::createWithSpriteFrameName("background_2.png");
	//设置背景在屏幕中心显示
	bg1->setPosition(vSize/2);
	//缩放适合屏幕大小
	bg1->setScaleY(vSize.height/bg1->getContentSize().height+0.005);
    bgheight = bg1->getBoundingBox().size.height;
	this->addChild(bg1);
	bg2 =Sprite::createWithSpriteFrameName("background_2.png");
	bg2->setScaleY(vSize.height/bg2->getContentSize().height+0.005);
	Vec2 p2 (vSize.width/2,bg1->getPositionY()+bgheight-5);
	//加一个屏幕的高度。
	bg2->setPosition(p2);
	this->addChild(bg2);
	this->scheduleUpdate();
	return true;
}
void backgroundlayer::update(float t)
{
	//每帧每个背景向下移动
	bg1->setPositionY(bg1->getPositionY()-BGDOWNSPEED*t);
	bg2->setPositionY(bg2->getPositionY()-BGDOWNSPEED*t);
	//重新设置背景的位置。
	if(bg1->getPositionY()+bgheight/2<0)
	{
		bg1->setPositionY(bg2->getPositionY()+bgheight-5);
	}
	if(bg2->getPositionY()+bgheight/2<0)
	{
		bg2->setPositionY(bg1->getPositionY()+bgheight-5);
	}
}