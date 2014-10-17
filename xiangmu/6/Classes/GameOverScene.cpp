#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SelectGameScene.h"
#include "AudioUtil.h"
#include "BackgroundLayer.h"
#include "UserDateSolve.h"
#include "HitBodys.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

int GameOverScene::scoreMoveLengthPart = 0;

Scene * GameOverScene::createScene(float moveLength){
    
    GameOverScene::scoreMoveLengthPart = moveLength /100 ;
	Scene * scene = Scene::create();
	Layer * layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init(){
	if (!Layer::init()){
		return false;
	}
    AudioUtil::getInstance()->playEffect("die.mp3");
	vSize = Director::getInstance()->getVisibleSize();
	auto overParticle = ParticleSystemQuad::create("overParticle.plist");
	overParticle->setPosition(Vec2(vSize.width/6,vSize.height*4/5));
	auto mo = MoveBy::create(2,Vec2(450,0));
	auto ro = RotateBy::create(0.1,Vec3(0,180,0));
	auto mv = MoveBy::create(2,Vec2(-450,0));
	auto sf = Sequence::create(mo,ro,mv,NULL);
	overParticle->runAction(RepeatForever::create(sf));
	this->addChild(overParticle,10000);
	return true;
}

void GameOverScene::onEnter(){
	Layer::onEnter();
	addBackground();
	addjson();
	addSocre();

    UserDateSolve::userDateSolve(scoreMoveLengthPart);

}

void GameOverScene::addBackground(){
	auto bg = Sprite::create("743_maxaa.jpg");
	auto pSize = bg->getContentSize();
	bg->setPosition(320,480);
	bg->setScale(vSize.height/pSize.height);
	this->addChild(bg,0);
}
void GameOverScene::addjson(){
	Widget * ulayer = GUIReader::getInstance()->widgetFromJsonFile("GameOverScene_Ui_1/GameOverScene_Ui_1.json");
	this->addChild(ulayer);


	//auto tx_txf = (TextBMFont *)ulayer->getChildByName("TX_txf");
	//auto tx_txs = (TextBMFont *)ulayer->getChildByName("TX_txs");

	pb_pb = (LoadingBar *)ulayer->getChildByName("PB_pb");
	this->schedule(schedule_selector(GameOverScene::loadingUpdate));
	auto bt_bts = (Button *)ulayer->getChildByName("BT_bts");
	bt_bts->addTouchEventListener([=](Ref* f,Widget::TouchEventType t){
        HitBodys::getInstance() -> clearUseToolsBaseSprite();
        HitBodys::getInstance() -> clearToolsBaseSprite();
		Director::getInstance()->replaceScene(SelectGameScene::creatScene());
	});
}

void GameOverScene::loadingUpdate(float t){
	pb_pb->setPercent(pb_pb->getPercent() - 10 * t);
	if (pb_pb->getPercent() <= 0){
		this->unschedule(schedule_selector(GameOverScene::loadingUpdate));
	}
}

void GameOverScene::addSocre(){
    
    int score  = scoreMoveLengthPart;
    auto strScore = StringUtils::format("分数：%d",score);
    auto label = Label::createWithSystemFont(strScore, "Arial", 50);
    label->setPosition(320,580);
    label->setColor(Color3B::GREEN);
    this->addChild(label);
    
}
