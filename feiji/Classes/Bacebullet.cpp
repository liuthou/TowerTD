#include "Bacebullet.h"
#include "GameScene.h"
#include "Bullets.h"
bool BaseBullet::initWithSpriteFrameName(std::string name,Vec2 position,int speed)
{
	if(!Sprite::initWithSpriteFrameName(name))
	{
		return false;
	}
	this->setPosition(position);
	//得到显示区高度
	float height = Director::getInstance()->getVisibleSize().height;
	//移动动画。
	//移动位置为屏幕上方+飞机图片的高度。
	auto to = MoveTo::create((height-position.y)/speed,Vec2(position.x,height+this->getContentSize().height));
	auto cf = CallFunc::create(std::bind(&BaseBullet::remove,this));
	this->runAction(Sequence::create(to,cf,NULL));
	this->runAction(to);
	//得到游戏场景的实例
	GameScene * scene =dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	//通过游戏场景得到游戏层并把子弹贴在游戏层
	scene->getPlantLayer()->addChild(this);
	//加入单例容器中
	Bullets::getInstance()->addBullet(this);
	return true;
}
 void BaseBullet::remove(){
	Bullets::getInstance()->deleteBullet(this);
 	this->removeFromParentAndCleanup(true);

 }
