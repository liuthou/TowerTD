#include "Mainplan.h"
#include "OneBullet.h"
#include "TwoBullet.h"
bool Mainplan::init()
{
	if(!Sprite::initWithSpriteFrameName("hero_fly_1.png"))
	{
		return false;
	}
	//加载飞机动画。
	addAnimation();
	return true;
}

void Mainplan::addAnimation()
{
	//加载飞机动画。
	auto anim = Animation::create();
	SpriteFrame *sf;
	//通过桢缓存名字动画 加入第一帧
	sf =SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_fly_1.png");
	anim->addSpriteFrame(sf);
	//加入第二帧
	sf =SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_fly_2.png");
	anim->addSpriteFrame(sf);
	//设置帧循环播放次数  -1代表无限循环
	anim->setLoops(-1);
	//设置帧播放的间隔
	anim->setDelayPerUnit(0.01f);
	//根据anim序列创建anim动画an 
	auto an =Animate::create(anim);
	//让飞机运行帧动画
	this->runAction(an);
}
void Mainplan::onEnter()
{
	//访问父类的Onenter
	Sprite::onEnter();
	//设置回调发射子弹
	this->schedule(schedule_selector(Mainplan::addFire),0.15);
}
void Mainplan::addFire(float t)
{
	//创建子弹自动发射
	//this是飞机
	OneBullet::create(Vec2(this->getPositionX(),this->getPositionY()+this->getContentSize().height/2));
	TwoBullet::create(Vec2(this->getPositionX(),this->getPositionY()+this->getContentSize().height/2));
	//this->addChild(bullet);
}