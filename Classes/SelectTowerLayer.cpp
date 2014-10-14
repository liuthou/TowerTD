#include "SelectTowerLayer.h"
#include "GameManager.h"
#include "UiLayer.h"

bool SelectTowerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	 
	// show the position for tower
	auto towerPos = Sprite::create("towerPos.png");
	towerPos->setScale(0.7);
	//towerPos->setAnchorPoint(Vec2::ZERO);
	this->addChild(towerPos);

	menu = Menu::create();

	//according to Towers  to create equal num menuItems and the Sprite
	auto instance = GameManager::getInstance();
	int nums = instance->towerSelectVector.size();

	int currmoney = dynamic_cast<UiLayer*>(GameManager::getInstance()->getUiLayer())->getcurmoney();
	
	for (int i = 0; i < nums; i++)
	{
		int tower_count = instance->towerSelectVector.at(i);
		MenuItemImage* towerItem = MenuItemImage::create(StringUtils::format("startUI/tower__%02d.png", tower_count), StringUtils::format("startUI/tower__%02d.png", tower_count), StringUtils::format("startUI/tower__%02dunabled.png", tower_count), [=](Ref*)
		{			
			log("You select the %d", tower_count);
			//to assign the choose value when touch the menuItem
			addTower(tower_count);
			//clear up the contents
			 
			//this->removeAllChildrenWithCleanup(true);
			Layer::removeFromParent();
		});
		//judge this gold 
		switch (tower_count)
		{
		case 1:
			if (currmoney < TOWERONECOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 2:
			if (currmoney < TOWERTWOCOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 3:
			if (currmoney < TOWERTHREECOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 4:
			if (currmoney < TOWERFORECOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 5:
			if (currmoney < TOWERFIVECOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 6:
			if (currmoney < TOWERSIXCOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 7:
			if (currmoney < TOWERSEVENCOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		case 8:
			if (currmoney < TOWEREIGHTCOST)
			{
				towerItem->setEnabled(false);
			}
			break;
		default:
			break;
		}
		
		int pos_x = i * 64;
		int pos_y = +64 * (i / 3 + 0);

		pos_x = pos_x - 3 * 64 * ((i / 3 + 0));

		towerItem->setPosition(pos_x, pos_y);
		menu->addChild(towerItem);
	}
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Vec2(-towerPos->getContentSize().width / 3 * 2, towerPos->getContentSize().height / 3 * 2));
 	this->addChild(menu);

	return true;
}

 