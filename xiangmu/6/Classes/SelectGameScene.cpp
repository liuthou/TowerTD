#include "SelectGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ScoreLayer.h"
#include "PlayGameScene.h"
#include "SetAudioSceneLayer.h"
#include "StoreScene.h"
#include "UserDateSolve.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
Scene * SelectGameScene::creatScene(){
	Scene * scene = Scene::create();
	Layer * layer = SelectGameScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectGameScene::init(){
	if (!Layer::init()){
		return false;
	}
	vSize = Director::getInstance()->getVisibleSize();
    auto waterFunction = ParticleSystemQuad::create("WaterFountain.plist");
    this->addChild(waterFunction,10000);

	auto bg = Sprite::create("bg10.jpg");
	bg->setScale(vSize.height/bg->getContentSize().height);
	bg->setPosition(vSize.width/2,vSize.height/2);
	this->addChild(bg);
    
	return true;
}

void SelectGameScene::onEnter(){
	Layer::onEnter();
	addButton();
	TestUserDefaule();
	addLabel();
}

void SelectGameScene::addButton(){
	Widget * ulayer = GUIReader::getInstance()->widgetFromJsonFile("Start_Ui_1/Start_Ui_1.json");
	this->addChild(ulayer);


	auto bt_btf = (Button *)ulayer->getChildByName("BT_btf");
	bt_btf->addTouchEventListener([=](Ref* r,Widget::TouchEventType t){

		auto scene = PlayGameScene::create();
		scene->retain();
		Director::getInstance()->replaceScene(scene);

	});

	auto bt_bts = (Button *)ulayer->getChildByName("BT_bts");
	bt_bts->addTouchEventListener([=](Ref* r,Widget::TouchEventType t){

	});

	auto bt_btt = (Button *)ulayer->getChildByName("BT_btt");
	bt_btt->addTouchEventListener([=](Ref* r,Widget::TouchEventType t){
        auto scene = SetAudioSceneLayer::createScene();
        Director::getInstance()->pushScene(scene);
	});

	auto bt_btfo = (Button *)ulayer->getChildByName("BT_btfo");
	bt_btfo->addTouchEventListener([=](Ref* r,Widget::TouchEventType t){

	});

	auto bt_btfi = (Button *)ulayer->getChildByName("BT_btfi");
	bt_btfi->addTouchEventListener([=](Ref* r,Widget::TouchEventType t){
        /**
         *  增加商城
         */
        auto scene = StoreScene::create();
        Director::getInstance()->pushScene(scene);
	});


}
void SelectGameScene::TestUserDefaule(){
	/*if (UserDefault::isXMLFileExist()){

	}else{

	}*/
}
void SelectGameScene::addLabel(){
	
    int score = UserDateSolve::selectMaxScore();
    auto scoreLable = StringUtils::format("%d",score);
    
	curScoreLabel = Label::createWithSystemFont("0","Arial",80);
    maxScoreLabel = Label::createWithSystemFont(scoreLable,"Arial",50);
	maxMetersLabel = Label::createWithSystemFont("0","Arial",50);


	curScoreLabel->setPosition(vSize.width/6,vSize.height/4+50);
	curScoreLabel->setAnchorPoint(Vec2(0,0));
	curScoreLabel->setColor(Color3B::ORANGE);

	maxScoreLabel->setPosition(vSize.width/6,vSize.height/4-55);
	maxScoreLabel->setAnchorPoint(Vec2(0,0));
	maxScoreLabel->setColor(Color3B::RED);

	maxMetersLabel->setPosition(vSize.width/6,vSize.height/4-150);
	maxMetersLabel->setAnchorPoint(Vec2(0,0));
	maxMetersLabel->setColor(Color3B::RED);


	this->addChild(curScoreLabel);
	this->addChild(maxScoreLabel);
	this->addChild(maxMetersLabel);

}
void SelectGameScene::addScore(){
	/*PlayGameScene * scene = dynamic_cast<PlayGameScene *>(Director::getInstance()->getRunningScene());
	ScoreLayer * layer = scene->getScoreLayer();
	auto curscore = layer->getCurScore();
	curScoreLabel->setString(StringUtils::format("%d",curscore));*/
}
