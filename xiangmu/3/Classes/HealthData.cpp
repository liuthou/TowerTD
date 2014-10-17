#include "HealthData.h"
#include "MainScene.h"
#include "HealthDataAI.h"
#include "GlobalInfo.h"
bool HealthData::init(std::string fileName,int speed,int hp){
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	float w =texture->getPixelsWide();
	float h = texture->getPixelsHigh();
	if(!Sprite::initWithTexture(texture,Rect(0,0,w/4,h/4)))return false;
	//加载动画
	for (int i = 0;i <4;i++) {
		auto ani = Animation::create();
		for (int j = 0; j<4; j++){
			Rect r (w*j/4,h*i/4,w/4,h/4);
			ani->addSpriteFrameWithTexture(texture,r);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		m_animates.pushBack(amt);
	};
	//初始化数值
	hp = hp;
	fileName = fileName;
	speed = speed;
	auto ai  = HealthDataAI::create(this,DATASTEPTIME);
	this->addChild(ai);
	this->setIsdie(false);
	return true;
}
HealthData* HealthData::create(std::string filename,int speed,int hp){
	auto sp = new HealthData();
	if (sp&&sp->init(filename,speed,hp)){
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}
bool HealthData::moveUp(float t){
	//计算新位置
	Vec2 newpos=Vec2(this->getPositionX(),this->getPositionY()+DATASTEP);
	Vec2 newpos1=Vec2(this->getPositionX(),this->getPositionY()+DATASTEP/2);

	if (!this->checkMove(newpos1)){
		//不能移动,只转向
		this->runAction(m_animates.at(UPDATA)->clone());
		this->setDataDir(DirectionData::UPDATA);
		return false;
	};
	//可以移动,转向并且移动
	this->stopAllActions();
	this->runAction(m_animates.at(UPDATA)->clone());
	auto upto = MoveTo::create(t,newpos);
	this->runAction(upto);
	this->setDataDir(DirectionData::UPDATA);

	return true;
}
bool HealthData::moveDown(float t){

	Vec2 newpos=Vec2(this->getPositionX(),this->getPositionY()-DATASTEP);
	Vec2 newpos1=Vec2(this->getPositionX(),this->getPositionY() -DATASTEP/2);

	if (!this->checkMove(newpos1)){
		this->runAction(m_animates.at(DOWNDATA)->clone());
		this->setDataDir(DirectionData::DOWNDATA);
		return false;
	}
	this->stopAllActions();
	this->runAction(m_animates.at(DOWNDATA)->clone());
	auto moveto = MoveTo::create(t,newpos);
	this->runAction(moveto);
	this->setDataDir(DirectionData::DOWNDATA);

	return true;
}
bool HealthData::moveLeft(float t){

	Vec2 newpos=Vec2(this->getPositionX()-DATASTEP,this->getPositionY());
	Vec2 newpos1=Vec2(this->getPositionX()-DATASTEP/2,this->getPositionY());

	if (!this->checkMove(newpos1))
	{
		this->runAction(m_animates.at(LEFTDATA)->clone());
		this->setDataDir(DirectionData::LEFTDATA);
		return false;
	}
	this->stopAllActions();
	this->runAction(m_animates.at(LEFTDATA)->clone());
	auto upto = MoveTo::create(t,newpos);
	this->runAction(upto);
	this->setDataDir(DirectionData::LEFTDATA);

	return true;
}
bool HealthData::moveRight(float t){

	Vec2 newpos=Vec2(this->getPositionX()+DATASTEP,this->getPositionY());
	Vec2 newpos1=Vec2(this->getPositionX()+DATASTEP/2,this->getPositionY());

	if (!this->checkMove(newpos1))
	{

		this->runAction(m_animates.at(RIGHTDATA)->clone());
		this->setDataDir(DirectionData::RIGHTDATA);
		return false;
	}
	this->stopAllActions();
	this->runAction(m_animates.at(RIGHTDATA)->clone());
	auto upto = MoveTo::create(t,newpos);
	this->runAction(upto);
	this->setDataDir(DirectionData::RIGHTDATA);
	return true;
}
bool HealthData::checkMove(Vec2 newpoint){
	auto * scene =dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* map = scene->getMapLayer();
	Vec2 leftup=Vec2((newpoint.x-this->getContentSize().width/2+1),(newpoint.y+this->getContentSize().height/2-1));
	Vec2 rightup=Vec2((newpoint.x+this->getContentSize().width/2-1),(newpoint.y+this->getContentSize().height/2-1));
	Vec2 leftdown=Vec2((newpoint.x-this->getContentSize().width/2+1),(newpoint.y-this->getContentSize().height/2+1));
	Vec2 rightdown=Vec2((newpoint.x+this->getContentSize().width/2-1),(newpoint.y-this->getContentSize().height/2+1));

	if (map->couldPass(leftup)&&map->couldPass(rightup)&&map->couldPass(leftdown)&&map->couldPass(rightdown))
	{
		return true;
	}
	return false;
}
void HealthData::remove(){
	this->setIsdie(true);
	this->removeFromParentAndCleanup(true);
}
void HealthData::die(){
	this->runAction(Blink::create(1,2));
	this->remove();
}