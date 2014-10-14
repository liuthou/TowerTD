#include "TowerLayer.h"
#include "UpdateLayer.h"
#include "TowerOne.h"
#include "TowerTwo.h"
#include "TowerEight.h"
#include "TowerFive.h"
#include "TowerFour.h"
#include "TowerSeven.h"
#include "TowerSix.h"
#include "TowerThree.h"
#include "GameManager.h"
#include "UiLayer.h"
#include "GameBasic.h"

bool Towerlayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	//¼àÌý´¥Ãþµ½ËþÉÏ¿ÉÒÔÉý¼¶
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan=[=](Touch *t,Event *e){
		checkPoint = this->convertTouchToNodeSpace(t);
		 
			 checkUpdate(checkPoint);
		  
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	 return true;
}

	void Towerlayer::addTower(int towerType, Vec2 buildPos)
	{
		int currmoney = dynamic_cast<UiLayer*>(GameManager::getInstance()->getUiLayer())->getcurmoney();

		if (1 == towerType)
		{	
			if (currmoney < TOWERONECOST)
				return;
			auto towerone = TowerOne::create();
			towerone->setPosition(buildPos);
			this->addChild(towerone);
		}
		else if (2 == towerType)
		{
			//Ëþ¶þ
			if (currmoney < TOWERTWOCOST)
				return;
			auto towertwo = TowerTwo::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		else if (8 == towerType)
		{
			//Ëþ8
			if (currmoney < TOWEREIGHTCOST)
				return;
			auto towertwo = TowerEight::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		else if (3 == towerType)
		{
			//Ëþ3
			if (currmoney < TOWERTHREECOST)
				return;
			auto towertwo = TowerThree::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		else if (4 == towerType)
		{
			//Ëþ4
			if (currmoney < TOWERFORECOST)
				return;
			auto towertwo = TowerFour::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		else if (5 == towerType)
		{
			//Ëþ5
			if (currmoney < TOWERFIVECOST)
				return;
			auto towertwo = TowerFive::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		else if (6 == towerType)
		{
			//Ëþ6
			if (currmoney < TOWERSIXCOST)
				return;
			auto towertwo = TowerSix::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		else if (7 == towerType)
		{
			//Ëþ7
			if (currmoney < TOWERSEVENCOST)
				return;
			auto towertwo = TowerSeven::create();
			towertwo->setPosition(buildPos);
			this->addChild(towertwo);
		}
		 

	}
   

bool Towerlayer::checkIsBuild(Vec2 position)
{

	auto instance = GameManager::getInstance();
	auto towers = instance->towerVector;

	bool isBuild = true;
	for (int i = 0; i < towers.size(); i++)
	{
		Rect towerBox = Rect(towers.at(i)->getPositionX() - 32, towers.at(i)->getPositionY() - 32, 64, 64);
		if (towerBox.containsPoint(position))
		{
			isBuild = false;
			break;
		}
	}  
	return isBuild;
}

void Towerlayer::checkUpdate(Vec2 point)
{
	auto towervector = GameManager::getInstance()->towerVector;
	auto upLayer = dynamic_cast<UpdateLayer*>(this->getChildByTag(100));
	if (upLayer != nullptr)
	{
		upLayer->unshow();
	}
		 for(auto tower = towervector.begin(); tower != towervector.end(); tower++ )
		 {
			Rect towerBox = Rect((*tower)->getPositionX() - 32, (*tower)->getPositionY() - 32, 64, 64);
			if(towerBox.containsPoint(point))
			{
				
				    auto tower1 = (*tower);
				    auto updateLayer = UpdateLayer::create(tower1);
					this->addChild(updateLayer);
					updateLayer->setTag(100);     				
					return;
			}
				
		}
}
