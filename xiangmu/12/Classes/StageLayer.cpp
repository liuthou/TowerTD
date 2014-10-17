#include "StageLayer.h"
#include "SelectTowerLayer.h"
#include "MapLayer.h"
#include "SelectTowerLayer.h"
#include "TowerLayer.h"
#include "EnemyLayer.h"
#include "SuperSkillLayer.h"

bool StageLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//get winSize and origin

	isBulidTime = true;

	// where to build
	buildPos = Vec2::ZERO;
	// the tower type

	// the origin of layer

	auto winSize = Director::getInstance()->getVisibleSize();
	m_origin = Vec2(Vec2::ZERO);

	this->setAnchorPoint(m_origin);
	auto maplayer = MapLayer::create();
	maplayer->setName("map");

	this->addChild(maplayer);
	this->setContentSize(maplayer->getContentSize());

	auto towerlayer = Towerlayer::create();
	this->addChild(towerlayer);
	towerlayer->setName("tower");

	auto enemyLayer = Enemylayer::create();
	this->addChild(enemyLayer);
	enemyLayer->setName("enemy");

	/*
	achieve the scale and move for stagelayer
	*/
	//1. create a event listener
	auto listeners = EventListenerTouchAllAtOnce::create();

	//2. achieve the listener monitor 

	m_origin = Vec2(Vec2::ZERO);


	listeners->onTouchesMoved = [=](const std::vector<Touch*>& pTouchs, Event* pEvent)
	{

		if (pTouchs.size() > 1)
		{
			//1. get there two pTouchs
			auto point1 = pTouchs[0]->getLocation();
			auto point2 = pTouchs[1]->getLocation();

			//2. get distance of the two points
			auto currDistance = point1.distance(point2);

			//3. get previous distance of the two points
			auto preDistance = pTouchs[0]->getPreviousLocation().distance(pTouchs[1]->getPreviousLocation());

		// 缩放前的位置边界设置
			auto cur_pos = this->getPosition();
			auto cur_size = this->getBoundingBox().size;
		//缩放后的位置 边界
			auto scal_size = cur_size*(currDistance / preDistance);
			if (cur_pos.x+scal_size.width<winSize.width||cur_pos.x>0||cur_pos.y>0||cur_pos.y+scal_size.height<winSize.height)
			{
				currDistance = preDistance;
			}
		

			//4. again set scale
			auto scale = this->getScale()*(currDistance / preDistance);
			auto minScale = 720.0f / 1024.0f;
			scale = MIN(1.5, MAX(minScale, scale));
			this->setScale(scale);
		

		}
		else
		if (pTouchs.size() == 1)
		{
			//only one point
			auto touch = pTouchs[0];

			//1. get Delta
			auto diff = touch->getDelta();
			//2. get currposition
			auto currentPos = this->getPosition();
			//3.get right pos
			auto pos = currentPos + diff;
			//4.get current contentsize
			auto currSzie = this->getBoundingBox().size;

			//5.control its boundary
			pos.x = MIN(pos.x, currSzie.width*this->getAnchorPoint().x);
			pos.x = MAX(pos.x, -currSzie.width + winSize.width + currSzie.width*this->getAnchorPoint().x);

			pos.y = MIN(pos.y, currSzie.height*this->getAnchorPoint().y);
			pos.y = MAX(pos.y, -currSzie.height + winSize.height + currSzie.height*this->getAnchorPoint().y);

			//reset this position
			this->setPosition(pos);

			//update origin
			if (pos.x >= currSzie.width*this->getAnchorPoint().x || pos.x <= -currSzie.width + winSize.width + currSzie.width*this->getAnchorPoint().x)
			{
				diff.x = 0;
			}
			if (pos.y >= currSzie.height*this->getAnchorPoint().y || pos.y <= -currSzie.height + winSize.height + currSzie.height*this->getAnchorPoint().y)
			{
				diff.y = 0;
			}
			m_origin += diff;
		}

	};

	listeners->onTouchesEnded = [=](const std::vector<Touch*>& pTouchs, Event* pEvent)
	{

		if (pTouchs[0]->getStartLocation().getDistance(pTouchs[0]->getLocation()) > 5)
		{
			return;
		}

		//delete the layer
		if (this->getChildByName("select"))
		{
			this->removeChildByName("select");

			return;
		}
		if (isBulidTime == false)
		{
			isBulidTime = true;
			return;
		}
		//chect this poistion is or not to create the tower
		if (!towerlayer->checkIsBuild(this->convertTouchToNodeSpace(pTouchs[0])))
		{

			return;
		}
		if (!maplayer->isCanBulid(this->convertTouchToNodeSpace(pTouchs[0])))

		{
			initCanBuild(maplayer->getAllCanBuild());
			return;
		}

		//create the selectLayer to select tower

		auto selectlayer = SelectTowerLayer::create();
		Vec2 posiotion = this->convertTouchToNodeSpace(pTouchs[0]);
		posiotion = Vec2((int)posiotion.x / 64, (int)posiotion.y / 64) * 64;

		posiotion = maplayer->getMapPos(posiotion);
		//get the position
		selectlayer->setPosition(posiotion);

		buildPos = (posiotion);
		selectlayer->setName("select");
		selectlayer->addTower = [=](int towerType)
		{
			addTower(towerType);
		};
		this->addChild(selectlayer);

	};
	//3.add listener to Event dispatcher
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listeners,this);

	return true;
}

// build tower
void StageLayer::addTower(int towerType)
{
	isBulidTime = false;
	auto towerlayer = dynamic_cast<Towerlayer*>(this->getChildByName("tower"));

	towerlayer->addTower(towerType, buildPos);

}


void StageLayer::initCanBuild(std::vector<Vec2> points)
{
	auto mapLayer = dynamic_cast<MapLayer*>(this->getChildByName("map"));
	auto towerlayer = dynamic_cast<Towerlayer*>(this->getChildByName("tower"));
	for (int i = 0; i < points.size(); i++)
	{

		Vec2 position = points.at(i);

		if (!towerlayer->checkIsBuild(position))
		{
			continue;
		}

		position = mapLayer->getMapPos(Vec2(position.x, position.y - 64));
		auto towerPos = Sprite::create("towerPos.png");
		towerPos->setScale(0.7);
		towerPos->setPosition(position);
		this->addChild(towerPos);
		auto blink = Blink::create(1.0f, 3);
		auto remove = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, towerPos));
		towerPos->runAction(Sequence::create(blink, remove, nullptr));
	}

}

