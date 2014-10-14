#include "BaseTank.h"
#include "Basebullet.h"
#include "GameScene.h"
#include "MapLayer.h"

bool BaseTank::initWithSpriteFrameName(std::string name,int hp,int speed){
	if(!Sprite::initWithSpriteFrameName(name)){
		return false;
	}
	this->score = 0;
	this->setisStop(true);
	this->runAnimate();
	this->hp=hp;
	this->speed=speed;
	this->state=Up;
	this->isdie=false;
	this->schedule(schedule_selector(BaseTank::move));
	this->BlinkAnimation();
	return true;
}
//ÒÆ¶¯·½·¨
void BaseTank::move(float t){
	this->setRotation(state*90);
	if (isstop)
	{
		return;
	}
	if(state==Up){
		if (boundingBox(Vec2(this->getPositionX(),this->getPositionY()+speed * t))||(this->getPositionY()+this->getContentSize().height/2>640))
		{
			return;
		}
		this->setPositionY(this->getPositionY()+speed * t);
	}else if(state==Down){
		if (boundingBox(Vec2(this->getPositionX(),this->getPositionY()-speed * t))||(this->getPositionY()-this->getContentSize().height/2<0))
		{
			return;
		}
		this->setPositionY(this->getPositionY()-speed * t);
	}else if(state==Left){
		if (boundingBox(Vec2(this->getPositionX()-speed * t,this->getPositionY()))||(this->getPositionX()-this->getContentSize().width/2<0))
		{
			return;
		}
		this->setPositionX(this->getPositionX()-speed * t);
	}else if(state==Right){
		if (boundingBox(Vec2(this->getPositionX()+speed * t ,this->getPositionY()))||(this->getPositionX()+this->getContentSize().width/2>640))
		{
			return;
		}
		this->setPositionX(this->getPositionX()+speed * t);
	}
}

bool BaseTank::boundingBox(Vec2 position)//ÒÆ¶¯ºóÅö×²¼ì²â
{
	auto scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto layer = dynamic_cast<MapLayer*>(scene->getMaplayer());
	auto point1 = Vec2(position.x - 12, position.y - 12);
	auto point2 = Vec2(position.x - 12, position.y + 12);
	auto point3 = Vec2(position.x + 12, position.y + 12);
	auto point4 = Vec2(position.x + 12, position.y - 12);
	auto point5 = Vec2(position.x - 12, position.y);
	auto point6 = Vec2(position.x,position.y + 12);
	auto point7 = Vec2(position.x + 12, position.y );
	auto point8 = Vec2(position.x ,position.y - 12);
	if (!layer->checkIsNode(point1) && !layer->checkIsNode(point2) && !layer->checkIsNode(point3) && !layer->checkIsNode(point4)
		&&!layer->checkIsNode(point5) && !layer->checkIsNode(point6) && !layer->checkIsNode(point7) && !layer->checkIsNode(point8)){
		return false;
	}

	return true;
}
void BaseTank::hurt(int hp){
	auto center = __NotificationCenter::getInstance();
	this->hp-=hp;
	center->postNotification("TankHurt",this);
	if(this->hp<=0){
		this->isdie=true;
		center->postNotification("EnemyDie",this);
		this->dieAnimation();
	}	
}
Vec2& BaseTank::getNextFramePostion()
{   
	float fps = Director::getInstance()->getAnimationInterval();
	auto point = this->getPosition();
	if(state==Up){
		point.y =this->getPositionY()+speed*fps;
	}else if(state==Down){
		point.y = this->getPositionY()-speed*fps;
	}else if(state==Left){
		point.x = this->getPositionX()-speed*fps;
	}else if(state==Right){
		point.x = this->getPositionX()+speed*fps;
	}
	return point;
}
//µØÍ¼¼ì²â
Rect& BaseTank::getNextFrameBoundingBox()
{   
	auto point = getNextFramePostion();
	auto height = this->getContentSize().height;
	auto width = this->getContentSize().width;
	float x = point.x - width/2;
	float y = point.y - height/2;
	return Rect(x,y,width,height);
}
//ËÀÍö¶¯»­
void BaseTank::dieAnimation(){
	this->unscheduleAllSelectors();
	auto animt =Animation::create();
	auto cache =SpriteFrameCache::getInstance();
	animt->addSpriteFrame(cache->getSpriteFrameByName("explode-1.png"));
	animt->addSpriteFrame(cache->getSpriteFrameByName("explode-2.png"));
	animt->addSpriteFrame(cache->getSpriteFrameByName("explode-3.png"));
	animt->setDelayPerUnit(0.1f);
	animt->setLoops(1);	
	auto  cf =CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create(Animate::create(animt),cf,NULL));	
}
//ÉÁË¸¶¯»­
void BaseTank::BlinkAnimation(){	
	auto animt =Animation::create();
	auto cache =SpriteFrameCache::getInstance();
	animt->addSpriteFrame(cache->getSpriteFrameByName("xing1.png"));
	animt->addSpriteFrame(cache->getSpriteFrameByName("xing2.png"));
	animt->addSpriteFrame(cache->getSpriteFrameByName("xing3.png"));
	animt->addSpriteFrame(cache->getSpriteFrameByName("xing4.png"));
	animt->setDelayPerUnit(0.3f);
	animt->setLoops(1);	
	animt->setRestoreOriginalFrame(true);
	this->runAction(Animate::create(animt));
}