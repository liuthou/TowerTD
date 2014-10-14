#include "StartScene.h"
#include "GameScene.h"
#include "AudioRes.h"
bool StartScene::init(){
	if (!Scene::init()){
		return false;
	}
	//添加坦克世界的图片
	AudioInit();
	auto title = Sprite::create("BattleCity.png");
	title->setNormalizedPosition(Vec2(0.5, 0.6));
	this->addChild(title);
	//添加开始游戏的按钮
	auto item = MenuItemFont::create("StartGame", [](Ref*){
		Director::getInstance()->replaceScene(GameScene::create());
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(0, 0);
	item->setNormalizedPosition(Vec2(0.5,0.2));
	this->addChild(menu);
	return true;
}
