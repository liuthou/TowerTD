#include "UiLayer.h"
#include "Enemy.h"
#include "BaseTower.h"
#include "PauseLayer.h"
#include "GameManager.h"
#include "GameOverLayer.h"
#include "SuperBigskills.h"
#include "SuperSkillLayer.h"

UiLayer::UiLayer(){}
bool UiLayer::init(){
	if(!Layer::init()){
		return false;
	}
	this->curhomehp=20;
	this->shuts=GameManager::getInstance()->curlevel;
	this->totalwaves=GameManager::getInstance()->enemyGroups.size();
	this->curmoney=GameManager::getInstance()->getStageMoney();
	this->waves=0;
	//UI½çÃæ
	uilayer = GUIReader::getInstance()->widgetFromJsonFile("NewUi_1/NewUi_1.ExportJson");
	this->addChild(uilayer);
	homehp = (TextBMFont*)uilayer->getChildByName("home");
	homehp->setString(StringUtils::format("%d",curhomehp));
    money = (TextBMFont*)uilayer->getChildByName("money");
	money->setString(StringUtils::format("%d",curmoney));
    wave = (TextBMFont*)uilayer->getChildByName("wave");
	wave->setString(StringUtils::format("%d",waves));
	TextBMFont* shut = (TextBMFont*)uilayer->getChildByName("shut");
	shut->setString(StringUtils::format("%d",shuts));
	TextBMFont* total = (TextBMFont*)uilayer->getChildByName("totalws");
	total->setString(StringUtils::format("%d",totalwaves));
	Button * meinv = (Button*)uilayer->getChildByName("meinv");
	meinv->addTouchEventListener([=](Ref* sender,Widget::TouchEventType type){
		if(type==Widget::TouchEventType::BEGAN){
			auto size = Director::getInstance()->getWinSize();
		    auto label = Label::create("Liu tian hou you tiao pi le","fonts/Marker Felt.ttf",100);
			label->setPosition(size/2);
			label->setColor(Color3B::YELLOW);
			label->setName("liutianhou");
			this->addChild(label);
SimpleAudioEngine::getInstance()->playEffect("Music/homediaoxue.mp3");
		}
		if(type==Widget::TouchEventType::ENDED){
			Label* label = this->getChildByName<Label*>("liutianhou");
			auto remove = CallFunc::create([=](){label->removeFromParentAndCleanup(true);});
			label->runAction(Sequence::create(DelayTime::create(0.1),remove,NULL));
		}
	});
	auto superlayer = SuperSkillLayer::create();
	this->addChild(superlayer);
	Button * skills = (Button*)uilayer->getChildByName("skills");
    skills->addTouchEventListener([=](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::BEGAN)
		{
			if(superlayer->isVisible()){	
			//	superlayer->setVisible(false);
				//	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(superlayer);
			}else{
			//	superlayer->setVisible(true);
			}
		}
	});
	Button * mainmenu = (Button*)uilayer->getChildByName("mainmenu");
	mainmenu->addTouchEventListener([=](Ref* sender,Widget::TouchEventType type){
		if(type==Widget::TouchEventType::BEGAN){
			log("hehe");
		}
		if(type==Widget::TouchEventType::ENDED){
			this->addChild(PauseLayer::create());
			GameManager::getInstance()->pause();
		}
	});
	auto center = __NotificationCenter::getInstance();
	center->addObserver(this,callfuncO_selector(UiLayer::setMoney),"EnemyDie",NULL);
	center->addObserver(this,callfuncO_selector(UiLayer::setHomehp),"EnemySuccessful",NULL);
	center->addObserver(this,callfuncO_selector(UiLayer::updateTower),"update",NULL);
	center->addObserver(this,callfuncO_selector(UiLayer::removeTower),"remove",NULL);
	center->addObserver(this,callfuncO_selector(UiLayer::setWave),"wavedown",NULL);
	return true;
}
void UiLayer::setMoney(Ref* sender){
	SimpleAudioEngine::getInstance()->playEffect("musics/getgold.wav");
	int enemymoney =((Enemy*)sender)->getMoney();
	curmoney+=enemymoney;
	money->setString(StringUtils::format("%d",curmoney));
}
void UiLayer::setHomehp(Ref* sender){
	SimpleAudioEngine::getInstance()->playEffect("Music/homediaoxue.mp3");
	auto str =StringUtils::format("%d",--curhomehp);
	if (curhomehp <= 0)
	{   
		GameManager::getInstance()->pause();
		this->addChild(GameOverLayer::create(1));
	}
	homehp->setString(str);
}
void UiLayer::setWave(Ref* sender){
	waves++;
	if (waves > totalwaves)
	{   
		if (GameManager::getInstance()->curlevel == MAXLEVEL)
		{
			this->addChild(GameOverLayer::create(2));
			return;
		}
		this->addChild(GameOverLayer::create(0));
		return;
	}
	auto str =StringUtils::format("%d",waves);
	wave->setString(str);
}
void UiLayer::updateTower(Ref* sender){
	BaseTower* tower = (BaseTower*)sender;
 	if(tower->getCurgold()<=curmoney){
 		curmoney-=tower->getCurgold();
 		tower->uplevel();
 	}else{
		auto size = Director::getInstance()->getWinSize();
		auto nomoneysp = Sprite::create("nomoney.png");
		this->addChild(nomoneysp);
		nomoneysp->setPosition(tower->getParent()->convertToWorldSpace(tower->getPosition()));
		auto nomoneylabel = Label::create("Lack of money","fonts/Marker Felt.ttf",30);
		nomoneysp->addChild(nomoneylabel);
		nomoneylabel->setColor(Color3B::YELLOW);
		auto call = CallFunc::create([=](){nomoneysp->removeFromParentAndCleanup(true);}); 
		nomoneysp->runAction(Sequence::create(Blink::create(0.3,3),DelayTime::create(0.5),call,NULL));
 	}
	money->setString(StringUtils::format("%d",curmoney));
}
void UiLayer::removeTower(Ref* sender){
	SimpleAudioEngine::getInstance()->playEffect("musics/getgold.wav");
	BaseTower* tower = (BaseTower*)sender;
 	curmoney+=tower->getGoldvalue();
 	tower->removeTower();
	money->setString(StringUtils::format("%d",curmoney));
}
int UiLayer::getcurmoney(){
	return curmoney;
}
UiLayer::~UiLayer()
{
   __NotificationCenter::getInstance()->removeAllObservers(this);
}