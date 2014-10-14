#include "GameOverLayer.h"
#include "GameScene.h"
#include "StartScene.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool GameOverLayer::init(){
	if (!Layer::init()){
		return false;
	}
	SimpleAudioEngine::getInstance()->playEffect("gameover.ai");
	auto bg = Sprite::create("gameover.png");
	bg->setPosition(330, -100);
	auto fadein = FadeIn::create(1.0f);
	auto delay = DelayTime::create(1.0f);
	auto moveto = MoveTo::create(1.0f, Vec2(330, 450));
	auto callback = CallFunc::create([=](){

		MenuItemFont* resumitem = MenuItemFont::create("reStart", ([](Ref*){
			BulletManager::getInstance()->cleanAll();
			EnemyManager::getInstance()->cleanAll();
			Director::getInstance()->replaceScene(GameScene::create());
		}));
		MenuItemFont* backitem = MenuItemFont::create("backMain", ([](Ref*){
			BulletManager::getInstance()->cleanAll();
			EnemyManager::getInstance()->cleanAll();
			Director::getInstance()->replaceScene(StartScene::create());		
		}));
		Menu* menu = Menu::create(resumitem, backitem, nullptr);
		menu->alignItemsVertically();
		menu->setPosition(330, 200);
		this->addChild(menu);
		
	});

	bg->runAction(Sequence::create(fadein,/* delay,*/ moveto,callback, nullptr));
	//bg->setVisible(false);
	this->addChild(bg);

	return true;
}
