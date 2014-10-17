#include "MenuLayer.h"
#include "MainScene.h"
#include "TouchLayer.h"
#include "SelectScene.h"
#include "StartScene.h"
#include "EntityManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;
bool MemuLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	//菜单背景
	Sprite *sp = Sprite::create("background2.png");
	sp->setPosition(size/2);
	sp->setScaleY(0.5);
	this->addChild(sp);
	//MenuItemImage*itemimage = MenuItemImage::create("light_skill.png","light_skill.png",CC_CALLBACK_1(MemuLayer::onItem,this));
	//itemimage->setPositionY(-100);
	//itemimage->setName("itemimage");
	//MenuItemImage*itemimage2 = MenuItemImage::create("qianlei.png","qianlei.png",CC_CALLBACK_1(MemuLayer::onItem,this));
	//itemimage2->setName("itemimage2");
	//Menu *mu = Menu::create(itemimage,itemimage2,NULL);
	//this->addChild(mu);
	////////////////////////////////////////////////////////////////
	Widget * uilayer = GUIReader::getInstance()->widgetFromJsonFile("MenuButton/Tank.json");
	this->addChild(uilayer);
	Button* uibnt = (Button *)uilayer->getChildByName("Button_24");
	uibnt->setPosition(Vec2(size.width/2,size.height/2+50));
	uibnt->addTouchEventListener([=](Ref*,Widget::TouchEventType touchtype){
		if (touchtype==Widget::TouchEventType::ENDED)
		{

		   Director::getInstance()->resume();
		   EntityManager::getInstance()->reset();
		   Director::getInstance()->popScene();
		}
	});
	Button* uibnt2 = (Button*)uilayer->getChildByName("Button_34");
	uibnt2->setPosition(Vec2(size.width/2,size.height/2-50));
	uibnt2->addTouchEventListener([=](Ref*,Widget::TouchEventType touchtype){
		if (touchtype==Widget::TouchEventType::ENDED)
		{
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
	return true;
}
//void MemuLayer::onItem(Ref * sender){
//	auto im  = dynamic_cast<MenuItemImage*>(sender);
//	//退出游戏游戏
//	if (im->getName()=="itemimage")
//	{
//		log("itemimage");
//		/*Director::getInstance()->resume();
//		MainScene *sne = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
//		auto layer = dynamic_cast<TouchLayer *>(sne->getChildByName("touchlayer"));
//		sne->removeChildByName("layer");
//		layer->setTouchStop(false);
//		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();*/
//		Director::getInstance()->end();
//	}
//	//重新开始游戏 调用mainscene清除所有层再重新生成
//	if (im->getName()=="itemimage2")
//	{
//		auto selectscene = SelectScene::create();
//		Director::getInstance()->replaceScene(selectscene);
//		log("itemimage2");
//	}
//}