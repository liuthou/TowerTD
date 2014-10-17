#include "WinScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool WinScene::init(){
	if (!Scene::init())
	{
	    return false;
	}
    Number =100;
	reNumber = 0;
	Size size =  Director::getInstance()->getVisibleSize();
	Sprite *bg = Sprite::create("bg34.png");
	bg->setPosition(size/2);
	this->addChild(bg);
//	Label *label = Label::createWithBMFont("futura-48.fnt","win!!!");
//	label->setScale(2.5);
//	label->setPosition(size.width/2,size.height*0.65);
//	this->addChild(label);
	NumberLabel = Label::createWithBMFont("futura-48.fnt","0000");
	NumberLabel->setScale(0.7);
	NumberLabel->setColor(Color3B::BLACK);
	NumberLabel->setPosition(bg->getContentSize().width/2,bg->getContentSize().height*0.3);
	this->addChild(NumberLabel);
	//////////////////////////////////////////
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* event){
		if (doubleclick == true)
		{
			Director::getInstance()->popScene();
			////Í£Ö¹ÒôÐ§////////////////////////////////////////////////////////////////////////////////
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
		}else
		{
			doubleclick = true;
			this->scheduleOnce(schedule_selector(WinScene::changeClick),1);
		}
		
		
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void WinScene::setNumber(int Number){
	this->Number = Number;
	reNumber = 0;
	this->schedule(schedule_selector(WinScene::resetScore),0.01,Number-1,0);
}
void WinScene::resetScore(float t){
	reNumber++;
	NumberLabel->setString(StringUtils::format("%d",reNumber));
}

void WinScene::changeClick(float dt){
	doubleclick = false;
}