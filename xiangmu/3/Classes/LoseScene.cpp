#include "LoseScene.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
bool LoseScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	flashsprite = Scale9Sprite::create("lose1.png");
	flashsprite->setContentSize(Size(size.width*4,flashsprite->getContentSize().height));
	flashsprite->setPosition(origin.x+size.width/2,origin.y+size.height/2);
	doubleclick = false;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* event){
		if (doubleclick == true)
		{
			Director::getInstance()->popScene();
		}else
		{
			doubleclick = true;
			this->scheduleOnce(schedule_selector(LoseScene::changeClick),1);
		}
		
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	bg = Sprite::create("losescene.png");
	bg->setPosition(origin.x+size.width/2,origin.y+size.height/2);
	bg->setVisible(false);
	this->addChild(bg);
	this->addChild(flashsprite);
	return true;
}

void LoseScene::onEnter(){
	Layer::onEnter();
	auto mscale = ScaleTo::create(0.3,0,1,1);
	//Ê§°ÜÒôĞ§
	SimpleAudioEngine::getInstance()->playEffect("lose.wav");
	flashsprite->runAction(Sequence::create(mscale,DelayTime::create(0.1),CallFunc::create(CC_CALLBACK_0(LoseScene::showBg,this)),NULL));
}
void LoseScene::showBg(){
	bg->setVisible(true);
}
void LoseScene::clearCaches(){
//	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
//	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void LoseScene::changeClick(float dt){
	doubleclick = false;
}

Scene* LoseScene::createScene(){
	auto scene = Scene::create();
	auto layer = LoseScene::create();
	scene->addChild(layer);
	return scene;
}