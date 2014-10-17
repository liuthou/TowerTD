#include "Enemy.h"
#include "Bullet.h"
#include "MainScene.h"
#include "EnemyAI.h"
#include "MonsterAttribute.h"
#include "MonsterAttributeConfType.h"
#include "EntityManager.h"
#include "GlobalInfo.h"
bool Enemy::init(int id){
    auto instance = MonsterAttribute::getInstance(id);
    auto filename = instance->getStringAttribute(Monster_Runanimate,"long.png");
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);
    float w =texture->getPixelsWide();
    float h = texture->getPixelsHigh();

	if(!Sprite::initWithTexture(texture,Rect(0,0,w/4,h/4)))return false;
    this->hp = instance->getIntAttribute(Monster_HP,3);
    this->def = instance->getIntAttribute(Monster_Defence,50);
    this->attrange =instance->getIntAttribute(Monster_AttackScope,200);
    this->buName = instance->getStringAttribute(Monster_Bullet_Pic,"jiantou.png");
    this->buattackValue = instance->getIntAttribute(Monster_Attack,50);
    this->buspeed = instance->getIntAttribute(Monster_Bullet_FlySpeed,100);
    this->price = instance->getIntAttribute(Monster_Price,10);
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
	this->setIsdie(false);
	auto ai = EnemyAI::create(this,STEPTIME1);
	this->addChild(ai);

	
	return true;
}
Enemy* Enemy::create(int id){
	Enemy * en = new Enemy();
	if (en&&en->init(id)){
		en->autorelease();
		return en;
	}
	CC_SAFE_DELETE(en);
	return nullptr;

}
void Enemy::dieAnimate(std::string fileName){
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(fileName);
	float w =texture->getPixelsWide();
	float h = texture->getPixelsHigh();
	Animate* amt = nullptr;
	for (int i = 0;i <4;i++) {
		auto ani = Animation::create();
		for (int j = 0; j<1; j++){
			Rect r (w*j/4,h*i/4,w/4,h/4);
			ani->addSpriteFrameWithTexture(texture,r);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		amt = Animate::create(ani);
	
	}
	this->runAction(amt);

}

void Enemy::hurtMe(Bullet* bullet){
	this->setAttackEffect(bullet->getAttackEffect());
	bulletattval = bullet->getAttackValue();
	//减速特效
	if (attackeffect.lowspeedtime>0)
	{
		this->lowspeedEffect(attackeffect.lowspeedtime);
	}
	//火焰特效
	if (attackeffect.firetime>0)
	{
		this->fireEffect(attackeffect.firetime);
	}
	//冰冻特效
	if (attackeffect.frozentime>0)
	{
		this->frozenEffect(attackeffect.frozentime);
	}
	this->hp= hp+def-bullet->getAttackValue();
	if (this->getHP() <= 0) {
		this->setIsdie(true);
		this->die();
	}
}
void Enemy::hurtMe(int attvalue){
	this->hp= hp-attvalue;
	if (this->getHP() <= 0) {
		this->setIsdie(true);
		this->die();
	}
}


void Enemy::lowspeedEffect(int time){
	//避免重复添加特效
	if (!islowspeed)
	{
		islowspeed = true;
		//修改速度
		speed = speed*0.5f;
		//添加粒子效果
		snowparticle = ParticleSystemQuad::create("bing.plist");
		Vec2 size = this->getContentSize();
		snowparticle->setPosition(size.x/2,size.y/2);
		this->addChild(snowparticle);
	}
	//更新移除特效的时间
	this->unschedule(schedule_selector(Enemy::removeLowspeedEffect));
	this->scheduleOnce(schedule_selector(Enemy::removeLowspeedEffect),time);
}
void Enemy::frozenEffect(int time){

}
void Enemy::fireEffect(int time){
	if (!isfire)
	{
		isfire = true;
		//修改速度
		speed = speed*1.5f;
		//添加粒子效果
		fireparticle = ParticleSystemQuad::create("Huo.plist");
		Vec2 size = this->getContentSize();
		fireparticle->setPosition(size.x/2,size.y/2);
		this->addChild(fireparticle);
	}
	//刷新特效时间
	this->unschedule(schedule_selector(Enemy::removeFireEffect));
	this->scheduleOnce(schedule_selector(Enemy::removeFireEffect),time);
	//刷新掉血时间
	this->unschedule(schedule_selector(Enemy::intervalHurt));
	this->schedule(schedule_selector(Enemy::intervalHurt),1,time,0);
}

void Enemy::removeLowspeedEffect(float dt){
	if (islowspeed)
	{
		speed = STEP;
		snowparticle->removeFromParent();
		snowparticle = nullptr;
		islowspeed = false;
	}
}
void Enemy::removeFrozenEffect(float dt){

}
void Enemy::removeFireEffect(float dt){
	if (isfire)
	{
		speed = STEP;
		fireparticle->removeFromParent();
		fireparticle = nullptr;
		isfire = false;
		this->unschedule(schedule_selector(Enemy::intervalHurt));
	}
}

void Enemy::intervalHurt(float dt){
	this->hp= hp+def-bulletattval;
	if (this->getHP() <= 0) {
		this->setIsdie(true);
		this->die();
	}
}
void Enemy::die(){
	this->stopAllActions();
	//绑定过加分函数再加分
	if (getmoneyfuncbind)
	{
		earnscore(this->getPrice());
	}
	//绑定过死亡特效再调用
	if (dieeffect)
	{
		dieeffect(this->getPosition());
	}
	//自己消失
	this->setVisible(false);
//	this->dieAnimate();//待填
	//做完动画调用remove
	
}
void Enemy::remove(){
	this->stopAllActions();
	this->unscheduleAllSelectors();
	this->setIsdie(true);
	this->removeFromParentAndCleanup(true);
}
bool Enemy::moveUp(float t){
	//计算新位置
	Vec2 newpos=Vec2(this->getPositionX(),this->getPositionY()+speed);
	Vec2 newpos1=Vec2(this->getPositionX(),this->getPositionY()+speed/2);

	if (!this->checkMove(newpos1)){
		//不能移动,只转向
		this->runAction(m_animates.at(UPBASE)->clone());
		this->setEnemyDir(Directionbase::UPBASE);
		return false;
	};
	//可以移动,转向并且移动
	this->stopAllActions();
    this->runAction(m_animates.at(UPBASE)->clone());
	auto upto = MoveTo::create(t,newpos);
	this->runAction(upto);
	this->setEnemyDir(Directionbase::UPBASE);
	return true;
}
bool Enemy::moveDown(float t){

	Vec2 newpos=Vec2(this->getPositionX(),this->getPositionY()-speed);
	Vec2 newpos1=Vec2(this->getPositionX(),this->getPositionY() -speed/2);

	if (!this->checkMove(newpos1)){
	    this->runAction(m_animates.at(DOWNBASE)->clone());
		this->setEnemyDir(Directionbase::DOWNBASE);
		return false;
	}
	this->stopAllActions();
	this->runAction(m_animates.at(DOWNBASE)->clone());
	auto moveto = MoveTo::create(t,newpos);
	this->runAction(moveto);
	this->setEnemyDir(Directionbase::DOWNBASE);
	return true;
}
bool Enemy::moveLeft(float t){

	Vec2 newpos=Vec2(this->getPositionX()-speed,this->getPositionY());
	Vec2 newpos1=Vec2(this->getPositionX()-speed/2,this->getPositionY());

	if (!this->checkMove(newpos1))
	{
        this->runAction(m_animates.at(LEFTBASE)->clone());
		this->setEnemyDir(Directionbase::LEFTBASE);
		return false;
	}
	this->stopAllActions();
	this->runAction(m_animates.at(LEFTBASE)->clone());
	auto upto = MoveTo::create(t,newpos);
	this->runAction(upto);
	this->setEnemyDir(Directionbase::LEFTBASE);
	return true;
}
bool Enemy::moveRight(float t){

	Vec2 newpos=Vec2(this->getPositionX()+speed,this->getPositionY());
	Vec2 newpos1=Vec2(this->getPositionX()+speed/2,this->getPositionY());

	if (!this->checkMove(newpos1))
	{

		this->runAction(m_animates.at(RIGHTBASE)->clone());
		this->setEnemyDir(Directionbase::RIGHTBASE);
		return false;
	}
	this->stopAllActions();
	this->runAction(m_animates.at(RIGHTBASE)->clone());
	auto upto = MoveTo::create(t,newpos);
	this->runAction(upto);
	this->setEnemyDir(Directionbase::RIGHTBASE);
	return true;
}
bool Enemy::checkMove(Vec2 newpoint){
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
void Enemy::fire(Sprite * tow){
  auto bu = Bullet::create(buName,tow->getPosition(),this->getPosition(),buspeed,buattackValue,attrange,enemyatteffect);
  log("Enemy fire!!(%f,%f)",tow->getPosition().x,tow->getPosition().y);
   bu->setPosition(this->getPosition());
  auto scene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
  scene->getGameLayer()->addChild(bu);
  EntityManager::getInstance()->MonsterBullet.pushBack(bu);
}

void Enemy::setScoreFunc(std::function<void(int)> earnscore){
	this->earnscore=earnscore;
	getmoneyfuncbind = true;
}

void Enemy::setDieEffectFunc(std::function<void(Vec2 dieposition)> dieeffect){
	this->dieeffect = dieeffect;
}