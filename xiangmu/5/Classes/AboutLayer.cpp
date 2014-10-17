#include "AboutLayer.h"
#include "GameData.h"
#include "DataXML.h"

bool AboutLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [](Touch* touch, Event* event){   
		return true;   
	};    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	addSprite();
	addMenu(BACK_P_1_FILENAME, BACK_P_2_FILENAME, Vec2(60, VISIBLE_SIZE.height - 60), [=](Ref * sender){
		EFFECT_MUSIC("click.mp3", audioFlag);
		this->removeFromParentAndCleanup(true);
	});
	return true;
}

void AboutLayer::addSprite(){
	auto bgImage = Sprite::create(ABOUT_FILENAME);
	bgImage->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(bgImage);
}

void AboutLayer::addMenu(std::string norName, std::string selName, Vec2 menuPos, std::function<void (Ref *)> menuCallback){
	auto normal = SpriteFrameCache::getInstance()->getSpriteFrameByName(norName);
	auto select = SpriteFrameCache::getInstance()->getSpriteFrameByName(selName);
	auto itemAll = MenuItemImage::create();
	itemAll->setCallback(menuCallback);
	itemAll->setNormalSpriteFrame(normal);
	itemAll->setSelectedSpriteFrame(select);
	auto menu = Menu::create(itemAll,NULL);
	menu->setPosition(menuPos);
	this->addChild(menu);
	
}
