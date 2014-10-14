#include "Basebullet.h"
#include "GameScene.h"
#include "BulletManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Basebullet* Basebullet::Createbullet(Vec2 position,moverect STATE){
	Basebullet *bullet =new Basebullet();
	if(bullet && bullet->initWithTank(position,STATE))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}
bool Basebullet::initWithTank(Vec2 position,moverect STATE){
	if(!Sprite::initWithSpriteFrameName("bullet.png")){
		return false;
	}
	
	this->Attack=BULLETATTACK;
	this->STATE = STATE;
	this->setRotation(90*STATE);
	this->position=position;
	this->setPosition(position);
	vsize = Director::getInstance()->getVisibleSize();
	
	GameScene * scene =dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	//通过游戏场景得到游戏层并把子弹贴在游戏层
	scene->getTanklayer()->addChild(this);
	this->move();
	this->isdie=false;
	return true;
}
//移动方法的实现
void Basebullet::move(){
	if(STATE==0){
		auto to = MoveTo::create(((vsize.height-this->getPositionY())/YIDONGSUDU),Vec2(this->getPositionX(),(vsize.height)));
		auto cf = CallFunc::create(std::bind(&Basebullet::remove,this));
		this->runAction(Sequence::create(to,cf,NULL));
	}else if(STATE==2){
		auto to = MoveTo::create((this->getPositionY()/YIDONGSUDU),Vec2(this->getPositionX(),0));
		auto cf = CallFunc::create(std::bind(&Basebullet::remove,this));
		this->runAction(Sequence::create(to,cf,NULL));
	}else if(STATE==3){
		auto to = MoveTo::create((this->getPositionX()/YIDONGSUDU),Vec2(0,this->getPositionY()));
		auto cf = CallFunc::create(std::bind(&Basebullet::remove,this));
		this->runAction(Sequence::create(to,cf,NULL));
	}else if(STATE==1){
		auto to = MoveTo::create(((640-this->getPositionX())/YIDONGSUDU),Vec2(640,this->getPositionY()));
		auto cf = CallFunc::create(std::bind(&Basebullet::remove,this));
		this->runAction(Sequence::create(to,cf,NULL));
	}
}
//将移除屏幕的子弹弄死
void Basebullet::remove(){
	this->isdie=true;
	this->removeFromParentAndCleanup(true);
}
