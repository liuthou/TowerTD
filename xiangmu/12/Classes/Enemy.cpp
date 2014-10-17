#include "Enemy.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
Enemy::Enemy()
:m_pointCounter(0)
,isIce(false)
,isFire(false)
,isWind(false)
,isWire(false)
,m_name("")
,m_points(NULL)
,m_hpBar(NULL)
,m_hpBgSprite(NULL)
,m_enemySuccessful(false)
{}
Enemy::~Enemy(){
}
Enemy* Enemy::create(std::string str,float hp,float speed,float money) 
{
	Enemy *pRet = new Enemy();
	if (pRet && pRet->init(str,hp,speed,money)){
		pRet->autorelease();
		return pRet;
	} else{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}
bool Enemy::init(std::string str,float hp,float speed,float money){
	if(!EnemyBase::init(hp,speed)){
		return false;
	}
	
	auto scene = GameManager::getInstance()->getStageLayer();
	auto layer = dynamic_cast<MapLayer*>(scene->getChildByName("map"));
	this->m_points=layer->getPoints();
	this->m_money=money;
	this->m_name=str;
	//需要预加载的项
	Armature* amt = Armature::create(m_name+"NewAnimation");
	amt->setName("amimature");
	this->m_orgcolor=amt->getColor();
	this->setContentSize(amt->getContentSize()*2/3);
	this->setPosition(m_points.at(0));
	this->addChild(amt);
	createHpBar();
	setMoveDirection();
	this->schedule(schedule_selector(Enemy::move));
	GameManager::getInstance()->enemyVector.pushBack(this);
	return true;
}
//遍历数组中的点并设置方向
void Enemy::setMoveDirection(){
	p1=currPoint();
	p2=nextPoint();
	if (abs(p1.x-p2.x)>=abs(p1.y-p2.y))
	{
		p1.x>p2.x ?this->setDirection(LEFT):this->setDirection(RIGHT);
	}else
	{
		p1.y>p2.y ?this->setDirection(DOWN):this->setDirection(UP);
	}
	this->runAnimate();
}
//运行不同方向的动画
void Enemy::runAnimate(){
	Armature* amt=this->getChildByName<Armature*>("amimature");
	if (amt != nullptr)
	{
		amt->getAnimation()->stop();
	}
	if(m_direction==UP){
		amt->getAnimation()->play("AnimationUp");	
	}else if(m_direction==DOWN){
		amt->getAnimation()->play("AnimationDown");
	}else if(m_direction==LEFT){
		amt->getAnimation()->play("AnimationLeft");
	}else if(m_direction==RIGHT){
		amt->getAnimation()->play("AnimationRight");
	}
}
//攻击动画
void Enemy::attackAnimate(){
	Armature* amt=this->getChildByName<Armature*>("amimature");
	if (amt != nullptr)
	{
		amt->getAnimation()->stop();
	}
 	amt->getAnimation()->play(m_name+"ACCACK");
}
//死亡动画
void Enemy::dieAnimate(){
	moneyLable();
	if(this->getProperty()==ICE){
		SimpleAudioEngine::getInstance()->playEffect("die1.mp3");
	}else if(this->getProperty()==FIRE){
		SimpleAudioEngine::getInstance()->playEffect("die2.mp3");
	}else if(this->getProperty()==WIRE){
		SimpleAudioEngine::getInstance()->playEffect("die3.mp3");
	}else if(this->getProperty()==WIND){
		SimpleAudioEngine::getInstance()->playEffect("die4.mp3");
	}
	GameManager::getInstance()->enemyVector.eraseObject(this);
 	Armature* amt=this->getChildByName<Armature*>("amimature");
	auto sf = CallFunc::create([=](){
		auto center = __NotificationCenter::getInstance();//创建小兵死亡监听
		center->postNotification("EnemyDie",this);
		this->remove();});
	amt->runAction(Sequence::create(Blink::create(0.2,3),sf,NULL));
}
//创造血量条
void Enemy::createHpBar(){
	Armature* amt=this->getChildByName<Armature*>("amimature");
	float i = 0.45f ;
	if(m_maxhp>200&&m_maxhp<400){
		i=0.55f;
	}else if(m_maxhp>800){
		i=0.7f;
	}
	m_hpBgSprite = Sprite::createWithSpriteFrameName("hpBg1.png.png");
	m_hpBgSprite->setScale(i);
	m_hpBgSprite->setPosition(Point(0,amt->getContentSize().height)*2/3);
	this->addChild(m_hpBgSprite);
	m_hpBar = CCProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
	m_hpBar->setType(ProgressTimer::Type::BAR);
	m_hpBar->setMidpoint(Point(0,0.5f));
	m_hpBar->setBarChangeRate(Point(1, 0));
	m_hpBar->setPercentage(m_curhp/m_maxhp*100);
	m_hpBar->setPosition(Point(m_hpBgSprite->getContentSize().width / 2
		,m_hpBgSprite->getContentSize().height / 3 * 2));
	m_hpBgSprite->addChild(m_hpBar);
	m_hpBgSprite->setVisible(false);
}
//设置血量条
void Enemy::setHpBar(){
	m_hpBgSprite->setVisible(true);
    m_hpBar->setPercentage(m_curhp/m_maxhp*100);
}
//获取数组中第一个点
Vec2 Enemy::currPoint(){
	if (m_points.size() > 0){
		p1=m_points.at(m_pointCounter);
		return this->p1;
	}
}
//获取数组中第二个点
Vec2 Enemy::nextPoint(){
	int maxCount = this->m_points.size();	
	m_pointCounter++;
	if (m_pointCounter < maxCount){
		p2 = this->m_points.at(m_pointCounter);
		return p2;
	}
	else{
		GameManager::getInstance()->enemyVector.eraseObject(this);
		setEnemySuccessful(true);//小怪进城了可以加个观察者减少
		auto center = __NotificationCenter::getInstance();//创建小兵进城监听
		center->postNotification("EnemySuccessful",this);
		setLive(DIE);//可以用来将生命状态为DIE的从容器中清掉
	}
}
//受伤方法
void Enemy::hurt(float attack,HurtState state){
	if(this->getLive()==DIE){return;}
	m_curhp-=attack;
	setHpBar();
	Armature* amt=this->getChildByName<Armature*>("amimature");
	if(m_curhp<=0){
		this->setDirection(STOP);
		if (amt != nullptr)
		{
			amt->getAnimation()->stop();
		}
		setProperty(state);
		setLive(DIE);
		dieAnimate();
	}
	if(this->getLive()!=DIE){
		if(state==ICE){
			iceEvent();
			iceAnimate();
		}
		if(state==FIRE){
			fireEvent();
		}
		if(state==WIND){
			windEvent();
		}
		if(state==WIRE){
			wireEvent();
		}
	}
}
//桢回调移动
void Enemy::move(float t){
	if(getEnemySuccessful()){
		remove();
		return;
	}
	if (this->getDirection()==LEFT||this->getDirection()==RIGHT){
		if(p1.x>p2.x){
			this->setPositionX(this->getPositionX()-m_speed*t);
			if(this->getPositionX()<=p2.x){
				setMoveDirection();
			}
		}else if(p1.x<p2.x){
			this->setPositionX(this->getPositionX()+m_speed*t);
			if(this->getPositionX()>=p2.x){
			setMoveDirection();
			}
		}
	}else if(this->getDirection()==UP||this->getDirection()==DOWN){
		if(p1.y>p2.y ){
			this->setPositionY(this->getPositionY()-m_speed*t);
			if(this->getPositionY()<=p2.y){
			setMoveDirection();
			}
		}else if(p1.y<p2.y ){
			this->setPositionY(this->getPositionY()+m_speed*t);
			if(this->getPositionY()>=p2.y){
			setMoveDirection();
			}
		}
	}
}
//冰属性伤害事件
void Enemy::iceEvent(){
	this->setSPEED(m_speed*0.7);
	if(m_speed<m_origspeed*0.5){//最多减速一半
		this->setSPEED(m_origspeed*0.5);
	}
	//重置状态
	if(isIce){return;}
	Armature* amt=this->getChildByName<Armature*>("amimature");
	amt->setColor(Color3B(89,195,226));
	auto sf = CallFunc::create([=](){
		setISICE(false);
		amt->setColor(m_orgcolor);
		this->setSPEED(m_origspeed);
	});
	this->runAction(Sequence::create(DelayTime::create(4),sf,NULL));
	this->setISICE(true);
}
//火属性伤害事件
void Enemy::fireEvent(){
	if(isFire){return;}
	fireAnimate();
	Armature* amt=this->getChildByName<Armature*>("amimature");
	amt->setColor(Color3B(255,69,0));//变红
	//重置状态
	auto chixud =DelayTime::create(1);//多长时间掉一次血
	auto number = CallFunc::create([=](){//一次掉多少
	   this->hurt(10,NIRGUNA); 
	});
	auto diaoxu = Sequence::create(chixud,number,NULL);
	auto sf = CallFunc::create([=](){//恢复
		setISFIRE(false);
		amt->setColor(m_orgcolor);
	});
	this->runAction(Sequence::create(Repeat::create(diaoxu,3),sf,NULL));
	setISFIRE(true);
}
//风属性伤害事件
void Enemy::windEvent(){
	if(isWind){return;}
	auto sprite2 = Sprite::create("wuyu.png");
	sprite2->setPositionY(40);
	sprite2->setRotation(-90);
	this->addChild(sprite2);
	if(this->getDirection()==UP){
		this->runAction(JumpBy::create(0.1,Vec2(0,-30),30,1));
	}else if(this->getDirection()==DOWN){
		this->runAction(JumpBy::create(0.1,Vec2(0,30),30,1));
	}else if(this->getDirection()==LEFT){
		this->runAction(JumpBy::create(0.1,Vec2(30,0),30,1));
	}else if(this->getDirection()==RIGHT){
		this->runAction(JumpBy::create(0.1,Vec2(-30,0),30,1));
	}
	//重置状态
	auto sf = CallFunc::create([=](){
		setISWIND(false);
		sprite2->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create(DelayTime::create(5),sf,NULL));
	setISWIND(true);
}
//雷电属性伤害事件
void Enemy::wireEvent(){
	if(isWire){return;}
	//重置状态
	wireAnimate();
	auto sf = CallFunc::create([=](){setISWIRE(false);});
	this->runAction(Sequence::create(DelayTime::create(2),sf,NULL));
	setISWIRE(true);
}
//冰动画
void Enemy::iceAnimate(){
	auto sprite = Sprite::createWithSpriteFrameName("ice1.png");
	this->addChild(sprite);
	auto sprite2 = Sprite::create("pen.png");
	sprite2->setPositionY(40);
	this->addChild(sprite2);
	auto an = Animation::create();
	for(int i=1;i<6;i++){
		auto str =StringUtils::format("ice%d.png",i);
		auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			an->addSpriteFrame(fram);
		}
		an->setDelayPerUnit(0.05f);
		an->setLoops(1);
		auto cf = CallFunc::create([=](){
			sprite->removeFromParentAndCleanup(true);
			sprite2->removeFromParentAndCleanup(true);
		});
		sprite->runAction(Sequence::create(Animate::create(an),cf,NULL));
		
}
//火动画
void Enemy::fireAnimate(){
	auto sprite = Sprite::createWithSpriteFrameName("fire1.png");
	this->addChild(sprite);
	auto sprite2 = Sprite::create("wa.png");
	sprite2->setPositionY(40);
	this->addChild(sprite2);
	auto an = Animation::create();
	for(int i=1;i<6;i++){
		auto str =StringUtils::format("fire%d.png",i);
		auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		an->addSpriteFrame(fram);
	}
	an->setDelayPerUnit(0.05f);
	an->setLoops(1);
	auto cf = CallFunc::create([=](){
		sprite->removeFromParentAndCleanup(true);
		sprite2->removeFromParentAndCleanup(true);
	});
	sprite->runAction(Sequence::create(Animate::create(an),cf,NULL));
}
//电属性动画
void Enemy::wireAnimate(){
	auto sprite = Sprite::createWithSpriteFrameName("wire1.png");
	this->addChild(sprite);
 	auto sprite2 = Sprite::create("pa.png");
 	sprite2->setPositionY(40);
 	this->addChild(sprite2);
	auto an = Animation::create();
	for(int i=1;i<13;i++){
		auto str =StringUtils::format("wire%d.png",i);
		auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		an->addSpriteFrame(fram);
	}
	an->setDelayPerUnit(0.05f);
	an->setLoops(1);
	auto cf = CallFunc::create([=](){
		sprite->removeFromParentAndCleanup(true);
		sprite2->removeFromParentAndCleanup(true);
	});
	sprite->runAction(Sequence::create(Animate::create(an),cf,NULL));
}
void Enemy::moneyLable(){
	auto moneysprite = Sprite::create("moneysprite.png");
	this->addChild(moneysprite);
	moneysprite->setScale(0.6);
	moneysprite->setPositionY(this->getContentSize().height*2/3);
	auto lable = Label::create(StringUtils::format("%.f",m_money),"fonts/Marker Felt.ttf",40);
	moneysprite->addChild(lable);
	moneysprite->runAction(MoveBy::create(0.1,Vec2(0,50)));
}