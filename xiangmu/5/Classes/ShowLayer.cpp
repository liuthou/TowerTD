#include "ShowLayer.h"
#include "GameData.h"
#include "SuspendLayer.h"
#include "GameOverLayer.h"
#include "GameScene.h"
#include "RoleLayer.h"
#include "DataXML.h"
#include "taskLayer.h"
#include "Role.h"
#include "HelpLayer.h"

bool ShowLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	//设置该层名字
	this->setName("showLayer");
	//设置成员变量暂停层和结束层初值为空
	suLayer = nullptr;
	gameOverLayer = nullptr;

	doubleScoreCount = 0;
	fiftyScore = 50;
	timeScore = TIME_SCORE;
	curScore = 0;
	douScore = nullptr;
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	addTopbar();
	addPauseIcon();
	addTopIcon();
	addDoubleScoreIcon();
	//添加任务层
	addTastLayer();
	addNotification();
	this->schedule(schedule_selector(ShowLayer::increaseCurScore), ADD_SCORE_TIME);
	this->schedule(schedule_selector(ShowLayer::doubleScoreUpdate), 1);

	return true;
}

void ShowLayer::onEnter() {
	Layer::onEnter();
	RoleLayer * layer = GET_ROLE_LAYER;
	role = layer->getRole();
	maxScore = DataXML::getInstence()->getInitialValue("maxScore");
	addScoreLabel();
	addHelpLayerByOneGame();
	addBostZone();
}
//添加右侧双倍积分距离提示
void ShowLayer::addBostZone(){
	auto bostZone = Sprite::createWithSpriteFrameName("boostzone-sheet0.png");
	bostZone->setScale(0.8f);
	bostZone->setPosition(770, 100);
	this->addChild(bostZone);
	auto zoneBlink = Blink::create(3, 6);
	auto removeZone = CallFunc::create([=](){
		bostZone->removeFromParentAndCleanup(true);
	});
	bostZone->runAction(Sequence::create(zoneBlink, removeZone, NULL));
}
//双倍积分标识
void ShowLayer::addDoubleScoreIcon(){
	douScore = Sprite::createWithSpriteFrameName("multiply2-sheet0.png");
	douScore->setPosition(900, 500);
	douScore->setVisible(false);
	this->addChild(douScore);
}
//第一次进入游戏时添加帮助
void ShowLayer::addHelpLayerByOneGame(){
	if (maxScore == 0)
	{
		//停止重力感应
		Device::setAccelerometerEnabled(false);
		Director::getInstance()->pause();
		auto helpLayer = HelpLayer::create();
		helpLayer->setScale(0.8f);
		this->addChild(helpLayer);
	}
}
//添加任务层
void ShowLayer::addTastLayer(){
	auto layer = taskLayer::create();
	this->addChild(layer);
}
//注册并接受通知
void ShowLayer::addNotification(){
	auto center = __NotificationCenter::getInstance();
	center->addObserver(this, callfuncO_selector(ShowLayer::addCurScore), "ADD_50_SCORE", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::addMoreCurScore), "ADD_100_SCORE", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::doubleScore), "DOUBLE_SCORE", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::glodDoubleScore), "GLOD_DOUBLE_SCORE", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::createGameOverLayer), "GAME_OVER", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::bostZoneDoubleScore), "BOST_SCORE", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::deleteBostZoneDoubleScore), "DELETE_BOST_SCORE", NULL);
	center->addObserver(this, callfuncO_selector(ShowLayer::setLayerNull), "SUSLAYER_REMOVED", NULL);
}
//右侧双倍积分
void ShowLayer::bostZoneDoubleScore(Ref * sender){
	doubleScoreCount += 99999;
	douScore->setVisible(true);
	auto bostZone = Sprite::createWithSpriteFrameName("boostzone-sheet0.png");
	bostZone->setScale(0.8f);
	bostZone->setPosition(770, 100);
	bostZone->setTag(1001);
	this->addChild(bostZone);
	if (fiftyScore == 50 && timeScore == TIME_SCORE)
	{
		fiftyScore *= 2;
		timeScore *= 2;
	}
}
//取消右侧双倍积分
void ShowLayer::deleteBostZoneDoubleScore(Ref * sender){
	doubleScoreCount -= 99999;
	auto bostZone = this->getChildByTag(1001);
	bostZone->removeFromParentAndCleanup(true);
	if (doubleScoreCount < 0)
	{
		doubleScoreCount = 0;
	}
}
//增加当前积分100分
void ShowLayer::addMoreCurScore(Ref * sender){
	curScore += fiftyScore * 2;
	std::string hname;
	if (flag){
		hname = "nearmiss-sheet0_01.png";
	}else{
		hname = "nearmiss-sheet0_02.png";
	}
	auto hun = Sprite::createWithSpriteFrameName(hname);
	hun->setPosition(role->getPositionX() + 30 ,role->getPositionY());
	this->addChild(hun);
	hun->setName("hun");
	auto de = DelayTime::create(0.3f);
	auto cf = CallFunc::create([=](){
		this->removeChildByName("hun");
	});
	this->runAction(Sequence::create(de,cf,NULL));
}
//增加当前积分50分
void ShowLayer::addCurScore(Ref * sender){
	curScore += fiftyScore;
	std::string fname;
	if (flag){
		fname = "nearmiss-sheet0_02.png";
	}else{
		fname = "nearmiss-sheet0_05.png";
	}
	auto fif = Sprite::createWithSpriteFrameName(fname);
	fif->setPosition(role->getPositionX() + 30, role->getPositionY());
	this->addChild(fif);
	fif->setName("fif");
	auto de = DelayTime::create(0.3f);
	auto cf = CallFunc::create([=](){
		this->removeChildByName("fif");
	});
	this->runAction(Sequence::create(de, cf, NULL));
}
//增加短时间双倍积分时间
void ShowLayer::doubleScore(Ref * sender){
	EFFECT_MUSIC("bling.mp3", audioFlag);
	douScore->setVisible(true);
	doubleScoreCount += 5;
	if (fiftyScore == 50 && timeScore == TIME_SCORE)
	{
		fiftyScore *= 2;
		timeScore *= 2;
	}
}
//增加长时间双倍积分时间
void ShowLayer::glodDoubleScore(Ref * sender){
	EFFECT_MUSIC("bling.mp3", audioFlag);
	douScore->setVisible(true);
	doubleScoreCount += 15;
	if (fiftyScore == 50 && timeScore == TIME_SCORE)
	{
		fiftyScore *= 2;
		timeScore *= 2;
	}
}
//创建结束层
void ShowLayer::createGameOverLayer(Ref * sender){
	if (gameOverLayer == nullptr)
	{
		//停止重力感应
		Device::setAccelerometerEnabled(false);
		gameOverLayer = GameOverLayer::create();
		gameOverLayer->addScoreLabel(curScore, maxScore);
		this->addChild(gameOverLayer);
		Director::getInstance()->pause();
	}
}
//随时间增加当前积分
void ShowLayer::increaseCurScore(float t){
	float roleHp = role->getM_hp();
	if (roleHp <= 0)
	{
		this->unschedule(schedule_selector(ShowLayer::increaseCurScore));
	}
	curScore += timeScore;
	curScoreLabel->setString(StringUtils::format("%d", curScore));
}
//增加暂停按钮
void ShowLayer::addPauseIcon(){
	//添加暂停层
	MenuItemImage * pauseIcon = MenuItemImage::create();
	pauseIcon->setScale(0.7);
	pauseIcon->setCallback([=](Ref * sender){
		if (suLayer == nullptr)
		{
			//停止重力感应
			Device::setAccelerometerEnabled(false);
			//停止背景音乐
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			EFFECT_MUSIC("click.mp3", audioFlag);
			suLayer = SuspendLayer::create();
			this->addChild(suLayer, 100);
			Director::getInstance()->pause();
		}
	});
	pauseIcon->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PAUSE_BUTTON_1_FILENAME));
	pauseIcon->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PAUSE_BUTTON_2_FILENAME));
	Menu * menu = Menu::create(pauseIcon, NULL);
	menu->setPosition(Vec2(45, 580));
	this->addChild(menu);
}
//添加顶部图标
void ShowLayer::addTopIcon(){
	//最高分与当前分图标
	Sprite * maxScoreIcon = Sprite::createWithSpriteFrameName(MAX_SCORE_FILENAME);
	maxScoreIcon->setScale(0.7);
	maxScoreIcon->setPosition(Vec2(80, 580));
	this->addChild(maxScoreIcon);
	Sprite * curScoreIcon = Sprite::createWithSpriteFrameName(TIMER_FILENAME);
	curScoreIcon->setPosition(Vec2(820, 580));
	this->addChild(curScoreIcon);
}
//显示分数
void ShowLayer::addScoreLabel(){
	//最高分数Label
	maxScoreLabel = Label::createWithSystemFont(StringUtils::format("%d",maxScore), "Arial", 25);
	maxScoreLabel->setPosition(Vec2(95, 580));
	maxScoreLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(maxScoreLabel);
	//当前分数Label
	curScoreLabel = Label::createWithSystemFont("0", "Arial", 40);
	curScoreLabel->setPosition(Vec2(840, 580));
	curScoreLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(curScoreLabel);
}
//添加木条
void ShowLayer::addTopbar(){
	auto topbar = Sprite::createWithSpriteFrameName(TOPBAR_FILENAME);
	topbar->setScaleX((VISIBLE_SIZE.width) / topbar->getContentSize().width);
	topbar->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height - topbar->getBoundingBox().size.height / 2);
	this->addChild(topbar);
}
//双倍积分时间倒计时
void ShowLayer::doubleScoreUpdate(float t){
	if (doubleScoreCount > 0)
	{
		doubleScoreCount--;
		flag = true;
	}else
	{
		if (fiftyScore == 100 && timeScore == (TIME_SCORE * 2))
		{
			fiftyScore /= 2;
			timeScore /= 2;
		}
		douScore->setVisible(false);
		flag = false;
	}
}

ShowLayer::~ShowLayer() {

	if (curScore > maxScore)
	{
		DataXML::getInstence()->saveData("maxScore",curScore);
	}
	__NotificationCenter::getInstance()->removeAllObservers(this);
}

void ShowLayer::setLayerNull(Ref * sender)
{
	suLayer = nullptr;
}
