#include "StartScene.h"
#include "SelectScene.h"
#include "MonsterGuide.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool StartScene::init(){
	if (!Scene::init())return false;
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");

	layer = GUIReader::getInstance()->widgetFromJsonFile("MyUI_1/MyUI_1.json");
	this->addChild(layer);
	auto btn_next  =(Button*)(layer->getChildByName("Button_21"));
	btn_next->addTouchEventListener([=](Ref*sender,Widget::TouchEventType t){
		if(t == Widget::TouchEventType::ENDED){
			auto scene = SelectScene::create();
			Director::getInstance()->pushScene(scene);
		}}
	);
	Size size = CCDirector::getInstance()->getWinSize();
	auto starSprite = Sprite::create("h3.png");
	starSprite->setScale(0.8f);
	this->addChild(starSprite, 11);

	auto _emitter = ParticleSystemQuad::create("button2.plist");
	_emitter->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(_emitter->getTexture());
	batch->addChild(_emitter);
	starSprite->setPosition(Point(btn_next->getPosition().x + btn_next->getContentSize().height / 2 , btn_next->getPosition().y));

	_emitter->setPosition(Point(btn_next->getPosition().x + btn_next->getContentSize().height / 2 , btn_next->getPosition().y ));
	float X = btn_next->getContentSize().height / 2;
	auto path = MyPathFun();
	starSprite->runAction(path);
	_emitter->runAction(path->clone());
	addChild(batch, 10);
	_emitter->release();
	auto sp = Sprite::create("DataDefence.png");
	sp->setPosition(320,630);
	sp->setScaleX(1.51);
	sp->setScaleY(2.07);
	auto moveby = MoveBy::create(1.5,Vec2(0,50));
	sp->runAction(RepeatForever::create(Sequence::create(moveby,moveby->reverse(), NULL)));
	layer->addChild(sp);
	return true;
}
void StartScene::onEnter(){
	Scene::onEnter();

	//ÒôÐ§
	SimpleAudioEngine::getInstance()->playBackgroundMusic("StartGameBgm.wav");
	auto button = (Button*)(layer->getChildByName("Guide"));
	button->addTouchEventListener([=](Ref* sender,Widget::TouchEventType t){
		if (t ==Widget::TouchEventType::ENDED){
			auto scene = MonsterGuide::createScene();
			Director::getInstance()->pushScene(scene);
		}
	});
	auto button1 = (Button*)(layer->getChildByName("Button_19")); 
	button1->addTouchEventListener([=](Ref*sender,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED){
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
                MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
                return;
            #endif
            
                Director::getInstance()->end();
            
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
            #endif
        
		}
	});
	auto btn_help = (Button*)(layer->getChildByName("Button_15"));
	btn_help->addTouchEventListener([=](Ref*sender ,Widget::TouchEventType t){
		if (t==Widget::TouchEventType::ENDED){
			auto Help_layer = addHelpLayer();
			auto scene = Scene::create();
			scene->addChild(Help_layer);
			auto btn =(Button*)(Help_layer->getChildByName("Back"));
			btn->addTouchEventListener([=](Ref*sender,Widget::TouchEventType t){
				Director::getInstance()->popScene();
			});
			Director::getInstance()->pushScene(scene);
 		}
	});

}
RepeatForever* StartScene::MyPathFun()
{

	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Vec2(420,530);
	bezier1.controlPoint_2 = Vec2(420,495);
	bezier1.endPosition = Vec2(420,460);
	auto bezierBy1 = BezierTo::create(1.5, bezier1);
	auto move1 = MoveTo::create(1,Vec2(220,460)); 
	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Vec2(220,460);
	bezier2.controlPoint_2 = Vec2(220,495);
	bezier2.endPosition = Vec2(220,530);
	auto bezierBy2 = BezierTo::create(0.6f, bezier2);
	auto move2 = MoveTo::create(1,Vec2(420,530));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}

Widget* StartScene::addHelpLayer(){
	auto layer1 = GUIReader::getInstance()->widgetFromJsonFile("NewUi_1/NewUi_1.json");
	return layer1;
}