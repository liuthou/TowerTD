#include "VictorySprite.h"
#include "EntityManager.h"
bool VirctoSprite:: init(int hp,int needfile,float selfrecoverspeed){
	if (!Sprite::init())return false;
	fullhp = hp;
	curhp = hp;
	receivedfile = 0;
    this->needfile = needfile;
	this->selfrecoverspeed = selfrecoverspeed;
	return true;
}
void VirctoSprite:: onEnter(){
	Sprite::onEnter();
	this->scheduleUpdate();
	this->schedule(schedule_selector(VirctoSprite::selfRecover),selfrecoverspeed);
}
void VirctoSprite::update(float t){
	increaseprogress();
	EntityManager::getInstance()->CheckEnemyInsterVsp(this);
}
VirctoSprite*VirctoSprite::create(int hp,int needfile,float selfrecoverspeed){
	auto vsp  = new VirctoSprite();
	if (vsp&&vsp->init(hp,needfile,selfrecoverspeed)){
		vsp->autorelease();
		return vsp;
	}
	CC_SAFE_DELETE(vsp);
	return nullptr;
}
int VirctoSprite::hurt(int attackValue){
    curhp-=attackValue;
	if (hurteffect)
	{
		hurteffect(fullhp,curhp);
	}
	if (curhp<=0&&losefunc)
	{
		losefunc();
	}
	return curhp;
}
void VirctoSprite::increaseprogress(){
	if (EntityManager::getInstance()->CheckInsterData(this)){
		receivedfile+= 1;
		float progress = 1.0f*receivedfile/needfile;

		log("progress:%.2f,receive :%d,needfile :%d",progress,receivedfile,needfile);
		if (gameprogress)
		{
			this->gameprogress(progress);
		}
		if (progress>=1)
		{
			if (winfunc)
			{
				this->winfunc();
			}
		}
	}
}
void VirctoSprite::selfRecover(float dt){
	if (curhp<fullhp)
	{
		curhp+=(float)fullhp/25;
		if (curhp>fullhp)
		{
			curhp = fullhp;
		}
		if (hurteffect)
		{
			hurteffect(fullhp,curhp);
		}
	}
}
void VirctoSprite:: setProgressFunc(std::function<void(float)> gameprogress){
	this->gameprogress = gameprogress;
	getprogressfuncbind = true;
}
void VirctoSprite::setHurtEffectFunc(std::function<void(int fullhp,int curhp)> hurteffect){
	this->hurteffect = hurteffect;
}
void VirctoSprite::setLoseFunc(std::function<void()>losefunc){
	this->losefunc = losefunc;
}
void VirctoSprite::setWinFunc(std::function<void()>winfunc){
	this->winfunc = winfunc;
}