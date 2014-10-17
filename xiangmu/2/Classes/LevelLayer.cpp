

#include "LevelLayer.h"
#include "ChangeLayer.h"
#include "VisibileSize.h"

Layer * LevelLayer::create(std::string level){
	auto layer = new LevelLayer();
	if (layer && layer->init(level)) {
		layer->autorelease();
		return layer;
	}CC_SAFE_DELETE(layer);
	return nullptr;

}

bool LevelLayer::init(std::string level){
	if (!Layer::init()) {
		return false;
	}


	//
	auto levelBG = Sprite::create(level);
	levelBG->setPosition(vSize / 2);
	addChild(levelBG);


	//插入进入下一个场景的按钮
	auto menuitemChange = MenuItemImage::create("Next_a.png", "Next_b.png", CC_CALLBACK_1(LevelLayer::goChange, this));
	auto menuChange = Menu::create(menuitemChange, NULL);
	float mCX = levelBG->getContentSize().width - menuitemChange->getContentSize().width / 2 - 10;
	float mCY = menuitemChange->getContentSize().height / 2 + 10;
	menuChange->setPosition(Vec2(mCX, mCY));
	levelBG->addChild(menuChange);


	return true;
}


void LevelLayer::goChange(Ref * sender){
	auto scene = Scene::create();
	auto changelayer = ChangeLayer::create();
	scene->addChild(changelayer);
	Director::getInstance()->replaceScene(scene);

}
