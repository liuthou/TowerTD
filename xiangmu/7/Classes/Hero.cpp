#include "Hero.h"
#include "StartScene.h"
#include "RoleAnimate.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "ExcessiveScene.h"

using namespace CocosDenshion;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;


bool Hero::init(Vec2 position){
	if(!BaseRole::initWithSpriteFrameName("heroMoveRight_01.png")){
		return false;
	}
	m_isFireUp = false;
	m_isRangeUp = false;
	isTaking = false;
	direction = RIGHT;
	isJump = false;
	isFire = false;
	count = 1;
	m_isHurt = false;
	m_speed = 0;
	m_RollDirection = 0;
	this->setM_state(1);
	time = 0;
	this->setPosition(position);
	m_hp = 400;
	//发送通知确定移动方向
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(Hero::heroMoveRight),"rightMove",NULL);
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(Hero::heroMoveLeft),"leftMove",NULL);
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(Hero::stopMove),"stopMove",NULL);
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(Hero::heroJump),"Jump",NULL);
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(Hero::addFire),"Fire",NULL);
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(Hero::Recover),"Stand",NULL);
	standAnimate(direction);

	std::vector<std::string>fileNames;
	for(int i = 1;i < 13;i++){
		std::string filename = StringUtils::format("heroBorn_%02d.png",i);
		fileNames.push_back(filename);
	}
	auto bornAni = RoleAnimate::getinstance()->createAnimate(fileNames,0.1,1);
	this->runAction(bornAni);

	

	return true;
}

void Hero::Recover(Ref * sender){
	this->stopActionByTag(100);
	this->stopActionByTag(101);
	standAnimate(direction);
}

void Hero::standAnimate(int direction){

	if(direction == RIGHT){

		std::vector<std::string>fileNames;
		for(int i = 1;i < 5;i++){
			std::string filename = StringUtils::format("heroStandRight_0%d.png",i);
			fileNames.push_back(filename);
		}
		auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.3,-1);
		ani->setTag(105);
		this->runAction(ani);
	}else
	{
		std::vector<std::string>fileNames;
		for(int i = 1;i < 5;i++){
			std::string filename = StringUtils::format("heroStandLeft_0%d.png",i);
			fileNames.push_back(filename);
		}
		auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.3,-1);
		ani->setTag(106);
		this->runAction(ani);
	}
}
//主角的create方法 传文件名和位置    创建主角
Hero * Hero::create(Vec2 position){
	Hero * hero = new Hero();
	if(hero && hero->init(position)){
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}

//主角的开火方法
void Hero::addFire(Ref * sender){
	if(direction == RIGHT){
		createAnimate("heroFireRight_0%d.png");
	}else{
		createAnimate("heroFireLeft_0%d.png");
	}
}

void Hero::createAnimate(std::string fileName){
	std::vector<std::string>fileNames;
	for(int i = 1;i < 5;i++){
		std::string filename = StringUtils::format(fileName.c_str(),i);
		fileNames.push_back(filename);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.07,1);
	ani->setTag(107);
	auto cf = CCCallFunc::create([=](){
		this->setIsFire(false);
	});
	auto cf1 = CCCallFunc::create([=](){
		if (this->isTaking == true){
			auto ev = AllVectors::getInstance()->getEnemiesVector();
			for (auto it = ev.begin(); it != ev.end(); it++){
				if ((*it)->m_isTaken == true && direction == RIGHT){
					auto rscene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
					auto enemylayer = rscene->getEnemyLayer();
					enemylayer->addRoll((*it)->getPosition());
					m_RollDirection = this->getDirection();
					(*it)->removeFromParentAndCleanup(true);
					(*it)->setIsDie(true);
					__NotificationCenter::getInstance()->postNotification("addscore",nullptr);
					Sprite * rool = enemylayer->roll;
					rool->getPhysicsBody()->setVelocity(Vec2(1500,0));

					auto e = AllVectors::getInstance()->getEfmusic();
					if (!e)
					{
						SimpleAudioEngine::getInstance()->playEffect("throutRoll.wav");
					}
					
					(*it)->m_isFired = true;
				}
				if ((*it)->m_isTaken == true && direction == LEFT){
					auto rscene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
					auto enemylayer = rscene->getEnemyLayer();
					enemylayer->addRoll((*it)->getPosition());
					m_RollDirection = this->getDirection();
					(*it)->removeFromParentAndCleanup(true);
					(*it)->setIsDie(true);
					(*it)->die();
					__NotificationCenter::getInstance()->postNotification("addscore",nullptr);
					Sprite * rool = enemylayer->roll;
					rool->getPhysicsBody()->setVelocity(Vec2(-1500,0));

					auto e = AllVectors::getInstance()->getEfmusic();
					if (!e)
					{
						SimpleAudioEngine::getInstance()->playEffect("throutRoll.wav");
					}
					(*it)->m_isFired = true;
				}
				AllVectors::getInstance()->deleteEnemy();
			}
			this->isTaking =false;
		}else
		{
			auto e = AllVectors::getInstance()->getEfmusic();
			if (!e)
			{
				SimpleAudioEngine::getInstance()->playEffect("heroFire.wav");
			}
			addBullet(direction);
		}
		
	});
	auto sq = Sequence::create(ani,cf,cf1,NULL);
	if(isFire == false){
		this->runAction(sq);
		this->setIsFire(true);
	}
}

void Hero::addBullet(int direction){
	if(direction == RIGHT){
		herobullet = HeroBullet::create("RightBullet1.png",Vec2((this->getPosition().x + this->getContentSize().width/2 - 30),this->getPosition().y));
		if (m_isRangeUp == true){
			herobullet->setM_range(500);
		}
		herobullet->setScale(0.3);
		herobullet->move(direction);
	}else{
		herobullet = HeroBullet::create("LeftBullet1.png",Vec2((this->getPosition().x - this->getContentSize().width/2 + 30),this->getPosition().y));
		if (m_isRangeUp == true){
			herobullet->setM_range(500);
		}
		herobullet->setScale(0.3);
		herobullet->move(direction);
	}
}


//主角的行走方法
Animate * Hero::getLeftAnimate(){
	std::vector<std::string>fileNames;
	for(int i = 1;i < 5;i++){
		std::string filename = StringUtils::format("heroMoveLeft_0%d.png",i);
		fileNames.push_back(filename);
	}
	m_moveLeftAnimate = RoleAnimate::getinstance()->createAnimate(fileNames,0.2,-1);
	m_moveLeftAnimate->setTag(101);
	return m_moveLeftAnimate;
}

Animate * Hero::getRightAnimate(){
	std::vector<std::string>fileNames;
	for(int i = 1;i < 5;i++){
		std::string filename = StringUtils::format("heroMoveRight_0%d.png",i);
		fileNames.push_back(filename);
	}
	m_moveRightAnimate = RoleAnimate::getinstance()->createAnimate(fileNames,0.2,-1);
	m_moveRightAnimate->setTag(100);
	return m_moveRightAnimate;
}

void Hero::heroMoveRight(Ref * sender){
	this->setIsFire(false);
	this->setDirection(RIGHT);
	this->stopAllActions();
	this->runAction(getRightAnimate());
	this->unschedule(schedule_selector(Hero::subStractX));
    //this->unschedule(schedule_selector(Hero::addX));
	this->schedule(schedule_selector(Hero::addX));

}

void Hero::heroMoveLeft(Ref * sender){
	this->setIsFire(false);
	this->setDirection(LEFT);
	this->stopAllActions();
	this->runAction(getLeftAnimate());
    this->unschedule(schedule_selector(Hero::addX));
    //this->unschedule(schedule_selector(Hero::subStractX));
	this->schedule(schedule_selector(Hero::subStractX));
}
//主角的跳跃方法
void Hero::heroJump(Ref * sender){
	auto e = AllVectors::getInstance()->getEfmusic();
	if (!e)
	{
		SimpleAudioEngine::getInstance()->playEffect("heroJump.wav");
	}
	//判断主角是否超过上边界
	if (this->getBoundingBox().getMaxY() >= 630){
		return;
	}

	if (1){
		this->getPhysicsBody()->setVelocity(Vec2(0,530));
		this->getPhysicsBody()->setCategoryBitmask(0);
		scheduleOnce(schedule_selector(Hero::call),0.28);
	}
	
}

void Hero::call(float t){
	this->getPhysicsBody()->setCategoryBitmask(0xA);
}

//主角的受伤方法
void Hero::hurt(){
	m_isRangeUp = false;
	m_isFireUp = false;
	this->getPhysicsBody()->setCollisionBitmask(16);
	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto controler = dynamic_cast<ControlLayer *>(scene->getControlLayer());
	controler->setIsPost(false);

	std::vector<std::string>fileNames;
	if (this->getDirection() == RIGHT)
	{
		for(int i = 1;i < 5;i++){
			std::string filename = StringUtils::format("heroDieRight_0%d.png",i);
			fileNames.push_back(filename);
		}
	}else
	{   for(int i = 1;i < 5;i++){
		std::string filename = StringUtils::format("heroDieLeft_0%d.png",i);
		fileNames.push_back(filename);
	}
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.1,1);
	auto disapear = FadeOut::create(0);
	auto cf = CallFunc::create([=](){
		this->setPosition(100,78);
	});
	auto bAmt = RoleAnimate::getinstance()->createAmt("heroBorn_%02d.png",12,0.1,1);
	auto fOut = FadeIn::create(1.2);
	auto spa = Spawn::create(fOut,bAmt,NULL);
	auto cf1 = CallFunc::create([=](){

		Label * lb = Label::create("HarmLess","Arial",20);
		lb->setPosition(60,120);
		this->addChild(lb);
		auto rb = Blink::create(3,3);
		auto cff = CallFunc::create([=](){
			lb->removeFromParentAndCleanup(true);
		});
		auto seqq = Sequence::create(rb,cff,NULL);
		lb->runAction(seqq);
		controler->setIsPost(true);
		this->scheduleOnce(schedule_selector(Hero::harmLess),3);
	});

	auto seq = Sequence::create(ani,disapear,cf,spa,cf1,NULL);
	this->runAction(seq);

	m_hp -= 100;
	if (m_hp < 0)
	{
		this->die();
	}
}

void Hero::harmLess(float t){

	this->getPhysicsBody()->setCollisionBitmask(17);
	/*this->getPhysicsBody()->setContactTestBitmask(3);
	this->getPhysicsBody()->setCollisionBitmask(0xA);*/
	m_isHurt = false;
}
//主角的死亡方法
void Hero::die(){

	auto recene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto gameOver = GUIReader::getInstance()->widgetFromJsonFile("GameOver_1/GameOver_1.ExportJson");
	recene->addChild(gameOver,100);


	auto curScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto scoreLayer = curScene->getScoreLayer();
	int cur_socre = scoreLayer->getCurScore();

	//比较分数
	auto MaxScore = UserDefault::getInstance()->getIntegerForKey("MaxScore",0);
	if (cur_socre > MaxScore){
		UserDefault::getInstance()->setIntegerForKey("MaxScore",cur_socre);
	}
	auto maxScore = UserDefault::getInstance()->getIntegerForKey("MaxScore",0);
	std::string file = StringUtils::format("%d",maxScore);
	std::string file1 = StringUtils::format("%d",cur_socre);
	auto maxlabel = static_cast<Text*>(Helper::seekWidgetByName(gameOver,"Label_19"));
	maxlabel->setString(file.c_str());
	auto score = static_cast<Text*>(Helper::seekWidgetByName(gameOver,"Label_21"));
	score->setString(file1.c_str());
	//暂停游戏
	Director::getInstance()->pause();

	//againButton 键
	auto againButton = static_cast<Button *>(Helper::seekWidgetByName(gameOver,"Button_11"));
	againButton->addTouchEventListener([=](Ref * s,Widget::TouchEventType t){
		if(t == ui::Widget::TouchEventType::ENDED){
			//__NotificationCenter::getInstance()->postNotification("again");
			Director::getInstance()->resume();
			AllVectors::getInstance()->enemiesVectorCleanUp();
			AllVectors::getInstance()->toolsVectorCleanUp();
			AllVectors::getInstance()->enemyBulletsVectorClearUp();
			AllVectors::getInstance()->heroBulletsVectorClearUp();
			UserDefault::getInstance()->setIntegerForKey("ID",1);
			scoreLayer->setCurScore(0);
			auto exscene = ExcessiveScene::create();
			Director::getInstance()->replaceScene(exscene);
		}
	});
}

void Hero::addX(float t){
	int a = this->getM_state();
	if(this->getPositionX() < 930){
		if (a == 1)
		{
			this->setPosition(this->getPositionX() + 3.5 + getM_speed(),this->getPositionY());
		}
		if (a == 2)
		{
			this->setM_speed(1);
			this->setPosition(this->getPositionX() + 3.5 + getM_speed(),this->getPositionY());
			time += t;
			if (time >= 4)
			{
				this->setM_state(1);
				this->setM_speed(0);
				time = 0;
			}
		}
	}
}

void Hero::subStractX(float t){
	int a = this->getM_state();
	if(this->getPositionX() > 30){
		if (a == 1)
		{
			this->setPosition(this->getPositionX() - 3.5 - getM_speed(),this->getPositionY());
		}
		if (a == 2)
		{
			this->setM_speed(1);
			this->setPosition(this->getPositionX() - 3.5 - getM_speed(),this->getPositionY());
			time += t;
			if (time >= 4)
			{
				this->setM_state(1);
				this->setM_speed(0);
				time = 0;
			}
		}
	}
}

void Hero::stopMove(Ref * sender){
	this->unschedule(schedule_selector(Hero::addX));
	this->unschedule(schedule_selector(Hero::subStractX));
}
