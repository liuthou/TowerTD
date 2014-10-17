#include "ForwardLayer.h"
#include "MainScene.h"
#include "TouchLayer.h"
#include "MenuLayer.h"
using namespace CocosDenshion;
bool ForwardLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origen =  Director::getInstance()->getVisibleOrigin();
	log("%.2f,%.2f",origen.x,origen.y);
	m_nNumbers = 100;
	m_NumberLoaded = 0;
	m_PlabelPerCent = LabelTTF::create("%0","futura-48.fnt",50);
	m_PlabelPerCent->setColor(Color3B::RED);
	m_PlabelPerCent->setPosition(origen.x+size.width/3,origen.y+size.height*0.3/4);
	this->addChild(m_PlabelPerCent,100);
	//底纹
	Sprite *loadBg = Sprite::create("select.png");
	loadBg->setPosition(origen.x+size.width/3,origen.y+size.height*0.2/4);
	loadBg->setScaleX(0.78);
	this->addChild(loadBg);
	//进度条
	loadProgress = ProgressTimer::create(Sprite::create("normal.png"));
	loadProgress->setPosition(size.width/3,size.height*0.2/4);
	loadProgress->setScaleX(0.78);
	loadProgress->setBarChangeRate(Vec2(1, 0));
	loadProgress->setType(kCCProgressTimerTypeBar);
	loadProgress->setMidpoint(Vec2(0,0));
	loadProgress->setPercentage(0.0f);
	this->addChild(loadProgress);
	//
	//this->schedule(schedule_selector(ForwardLayer::loadingCallBack),0.1);
	
	/////////////////////计分Label/////////////////////////////////////////////////////

	
	return true;
}
void ForwardLayer::onEnter(){
	Layer::onEnter();
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origen =  Director::getInstance()->getVisibleOrigin();
	showsorce = cursorce;
	label = Label::createWithBMFont("futura-48.fnt",StringUtils::format("%dkb/s",showsorce));
	label->setColor(cocos2d::Color3B::YELLOW);
	label->setPosition(size.width-100,size.height-20);
	this->addChild(label);
    ///////////////////////////
	MainScene *scene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	auto layer = dynamic_cast<TouchLayer *>(scene->getChildByName("touchlayer"));
	////////////////////暂停VS开始///////////////////////
	auto item1 = MenuItemImage::create();
	item1->setName("itme1");
	item1->setNormalImage(Sprite::create("qianlei.png"));
	auto item2 = MenuItemImage::create();
	item2->setName("itme2");
	item2->setNormalImage(Sprite::create("light_skill.png"));
	MenuItemToggle*tog = MenuItemToggle::createWithCallback([=](Ref *sender){
		auto m = dynamic_cast<MenuItemToggle*>(sender);
		auto n =  m->getSelectedItem();
		auto im  = dynamic_cast<MenuItemImage*>(n);
		if (im->getName()=="itme2")
		{
            layer->setTouchStop(true);
			Director::getInstance()->pause();
			///暂停音效//////////////////////////////////////////////////////////////////////////////////
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			auto menulayer = MemuLayer::create();
			menulayer->setName("layer");
			scene->addChild(menulayer,100);
		}
		if (im->getName()=="itme1")
		{
			//开始
			Director::getInstance()->resume();
			//回复触摸
			layer->setTouchStop(false);
			//开始音效///////////////////////////////////////////////////////////////////////////////////
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			//移除菜单
			scene->removeChildByName("layer");
			/*layer->setTouchStop(true);
			Director::getInstance()->pause();
			///暂停音效//////////////////////////////////////////////////////////////////////////////////
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			MainScene *sne = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
			auto menulayer = MemuLayer::create();
			menulayer->setName("layer");
			sne->addChild(menulayer);*/
		}
	},item1,item2,NULL);
	Menu *mu = Menu::create(tog,NULL);
	mu->setPosition(size.width-110,origen.y+30);
	this->addChild(mu);
}
 Vec2 ForwardLayer::getScoreLabelPosition(){
	 return label->getPosition();
 }
bool ForwardLayer::cutScore(int sorce){
	//////////////////////////////////////////////////////////////////////////
	if (cursorce>=sorce)
	{
		cursorce-=sorce;
		this->stateSelecterA();
		return true;
	}else
	{
		return false;
	}
}
void ForwardLayer::plusScore(int sorce){
	cursorce+=sorce;
	this->stateSelecterB();
}
//启动定时器
void ForwardLayer::stateSelecterA(){
    int sumA = abs(cursorce-showsorce);
	this->unschedule(schedule_selector(ForwardLayer::resetScoreA));
	this->schedule(schedule_selector(ForwardLayer::resetScoreA),0.02,sumA/5,0);
}
void ForwardLayer::stateSelecterB(){
	int sumB = abs(cursorce-showsorce);
	this->unschedule(schedule_selector(ForwardLayer::resetScoreA));
	this->schedule(schedule_selector(ForwardLayer::resetScoreA),0.01,sumB,0);
}
void ForwardLayer::resetScoreA(float t){
	if (cursorce>showsorce)
	{
		showsorce+=5;
		label->setString(StringUtils::format("%dkb/s",showsorce));
	}
	if (cursorce<showsorce)
	{
		showsorce-=5;
		label->setString(StringUtils::format("%dkb/s",showsorce));
	}
}
void ForwardLayer::resetScoreB(float t){;
	showsorce++;
	label->setString(StringUtils::format("%dkb/s",showsorce));
}
void ForwardLayer::loadingCallBack(float percent){
  log("percent:%.2f",percent);
	float value = percent*100;
	/////////////////////////////////////////////////
	if (value>=100)
	{
		//如果 进度条到了100
		value=100;
	}
	std::string tmp = StringUtils::format("%d%%",(int)value);
	//增加进度
	loadProgress -> setPercentage(value);
	m_PlabelPerCent->setString(tmp);
}
ForwardLayer::~ForwardLayer(){
	auto cener = __NotificationCenter::getInstance();
	cener->removeObserver(this,"Die");
}
