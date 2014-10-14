#include "SelectLayer.h"
#include "GameScene.h"
#include "GameManager.h"
#include "LoadingLayer.h"
#include "StartScene.h"
#include "GameBasic.h"
Scene * SelectLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectLayer::create();
	scene->addChild(layer);
	return scene;
}
bool SelectLayer::init(){
	if(!Layer::init()){
		return false;
	}
	


	size = Director::getInstance()->getVisibleSize();

	// ±³¾°
	auto bg = Sprite::create("selectBG.jpg");
	bg->setScale(1.5);
	bg->setPosition(size / 2);
	this->addChild(bg);
	//·µ»Ø°´Å¥
	auto backItem = MenuItemImage::create("back2.png", "back1.png", [=](Ref*)
	{
		Director::getInstance()->replaceScene(StartScene::createScene());
	});
	auto backSp = Sprite::create("back3.png");
	backSp->setNormalizedPosition(Vec2(0.5, 0.5));
	backItem->addChild(backSp);
	backItem->setPosition(size.width/6,size.height/6);
	auto backMenu = Menu::create(backItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	this->addChild(backMenu);
	int levelNum = 24;
	int levelPages = 3; 
	int buttonNum = 1; 
	layerNum = 1;
	 

	 layer = Layer::create();
	layerPos = layer->getPosition();
	this->addChild(layer);

	//add pages for choose 
	for (int i = 0; i < levelPages; i++)
	{
		auto page = Sprite::create("selectLevelBg.png");
		page->setPosition(Vec2(size.width/2+size.width*(i), size.height/2));
		page->setScale(0.9);

		auto menu = Menu::create(); 
		auto sp = Sprite::create("card_1.png"); 
		int row = page->getContentSize().height / sp->getContentSize().height;
		int col = page->getContentSize().width / sp->getContentSize().width;
		
		levelPages = levelNum / (row * col) ;

		//add buttons of every `
		//add menus for choose  nums= row*col of a page
		int k = 0; 
		while (k<row)
		{
			if (buttonNum>levelNum)
			{
				break;
			}
			int j = 0;
			while (j<col)
			{ 
				if (buttonNum>levelNum)
				{
					break;
				}
				auto item = MenuItemImage::create("card_1.png", "card_2.png", "card_3.png", [=](Ref*)
				{   
					GameManager::getInstance()->selectStage(buttonNum);
					
					Director::getInstance()->replaceScene(LoadingLayer::createScene());
					log("you select the %d level",buttonNum);
				});
				int curNum = UserDefault::getInstance()->getIntegerForKey("curNum");
				if (buttonNum <= (curNum + 1))
				{
					auto labelNum = Label::createWithTTF(std::to_string(buttonNum), "fonts/Marker Felt.ttf", 50);
					labelNum->setScale(2);
					labelNum->setTextColor(Color4B::RED);
					labelNum->setPosition(item->getContentSize() / 2);

					item->addChild(labelNum);
				}
				else
				{
					item->setEnabled(false);
				}
			
			
				item->setPosition(Vec2(sp->getContentSize().width*(j), sp->getContentSize().height*(row - k - 1)));
				item->setAnchorPoint(Vec2::ZERO);
				item->setContentSize(item->getContentSize() * 0.7);
				menu->addChild(item); 
				buttonNum++;	
				j++;
			}
			k++;
		}
		menu->setPosition(Vec2(50, 50));
		page->addChild(menu);
		layer->addChild(page); 
	}

	// control the page for moving
	auto listerer = EventListenerTouchOneByOne::create();

	listerer->onTouchBegan = [=](Touch* pTouch, Event* pEvent)
	{
		return true;
	};
	listerer->onTouchMoved = [=](Touch* pTouch, Event* pEvent)
	{
		layer->runAction(MoveBy::create(0.1f, Vec2(pTouch->getDelta().x, 0)));
	};
	listerer->onTouchEnded = [=](Touch* pTouch, Event* pEvent)
	{
		if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > size.width / 3 )
		 {
			if (layer->getPositionX() > layerPos.x && layerNum > 1)
			{
				layerPos.x = (layerPos.x + size.width);
				layerNum--;
			}
			else if (layer->getPositionX() < layerPos.x && layerNum < levelPages)
			{
				layerPos.x = (layerPos.x - size.width);
				layerNum++;
			}		 
		}
		layer->stopAllActions();
		layer->runAction(MoveTo::create((layer->getPosition().getDistance(layerPos)/size.width * 0.5f), layerPos));
		changeToggle();
	}; 

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listerer, this);

	// save current page num
	Menu* menu = Menu::create();
	for (int i = 1; i <= levelPages; i++)
	{
		auto item_select = MenuItemImage::create("r1.png", "r1.png");
		auto item_unselect = MenuItemImage::create("r2.png", "r2.png");
		auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SelectLayer::pageChange, this), item_select, item_unselect, nullptr);		 
			toggles.pushBack(toggle);
			if (i != 1)
			{
				toggle->setSelectedIndex(1);
			}		
		toggle->setName(std::to_string(i));
		toggle->setTag(i);
		menu->addChild(toggle);
	}
	menu->alignItemsHorizontally();
	menu->setPosition(Vec2(size.width / 2, size.height / 10));
	this->addChild(menu);
	return true;
}
void SelectLayer::pageChange(Ref* pSender)
{
	auto toggle = dynamic_cast<MenuItemToggle*>(pSender);
	toggle->setSelectedIndex(0);
	int num = toggle->getTag();
	changeToggle();
	if (num != (layerNum))
	{
		
		layerPos.x = (layerPos.x - size.width*(toggle->getTag() - layerNum));
		layer->stopAllActions();
		layer->runAction(MoveTo::create((layer->getPosition().getDistance(layerPos) / size.width * 0.5f), layerPos));
		layerNum = num;
		changeToggle();
	} 
}
void SelectLayer::changeToggle()
{
	
	auto toggle = toggles.at(layerNum - 1);
	toggle->setSelectedIndex(0);
	for (int i = 0; i < toggles.size(); i++)
	{
		if (toggle != toggles.at(i))
		{
			toggles.at(i)->setSelectedIndex(1);
		}
	}
}
