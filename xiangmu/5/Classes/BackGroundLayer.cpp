#include "BackgroundLayer.h"
#include "GameData.h"
#include "MapLayer.h"
#include "BaseSprite.h"

BackgroundLayer * BackgroundLayer::create(){
	BackgroundLayer * bgLayer = new BackgroundLayer();
	if (bgLayer && bgLayer->init())
	{
		bgLayer->autorelease();
		return bgLayer;
	}else
	{
		CC_SAFE_DELETE(bgLayer);
		return nullptr;
	}
}

bool BackgroundLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	addFarMountain();
	addFarField();
	addDense();
	addNearField();
	addRoad();
	addSundry();
	addGrass();
	//开启回调
	this->schedule(schedule_selector(BackgroundLayer::farMountainMove));
	this->schedule(schedule_selector(BackgroundLayer::fieldMove));
	this->schedule(schedule_selector(BackgroundLayer::denseMove));
	this->schedule(schedule_selector(BackgroundLayer::roadMove));
	this->schedule(schedule_selector(BackgroundLayer::grassMove));

	//加载地图，并开启回调使地图滚动
	addMap();
	this->schedule(schedule_selector(BackgroundLayer::mapMove));
	
	return true;
}
//添加地图
void BackgroundLayer::addMap(){
	int mapNum = rand() % 3 + 1;
	map1 = MapLayer::create(mapNum);
	map2 = MapLayer::create(mapNum + 1);
	map1->setPositionX(960);
	map2->setPositionX(map1->getPositionX() + 1920);
	this->addChild(map1);
	this->addChild(map2);
}
//更换地图
void BackgroundLayer::changeMap(){
	if (map1->getPositionX() <= -1920)
	{
		int mapNum = rand() % (GAME_MAPS_COUNT - 1) + 1;
		map1->removeFromParentAndCleanup(true);
		map1 = MapLayer::create(mapNum);
		map1->setPositionX(map2->getPositionX() + 1920);
		this->addChild(map1);
	}
	if (map2->getPositionX() <= -1920)
	{
		int mapNum = rand() % (GAME_MAPS_COUNT - 1) + 1;
		map2->removeFromParentAndCleanup(true);
		map2 = MapLayer::create(mapNum);
		map2->setPositionX(map1->getPositionX() + 1920);
		this->addChild(map2);
	}
}
//地图移动
void BackgroundLayer::mapMove(float t){
	map1->setPositionX(map1->getPositionX() - BACKGROUND_SPEED * 2 * t);
	map2->setPositionX(map2->getPositionX() - BACKGROUND_SPEED * 2 * t);
	changeMap();
}

void BackgroundLayer::addFarMountain(){
	farMountain_1 = Sprite::createWithSpriteFrameName(L1_S1_FILENAME);
	farMountain_1->setScaleX(VISIBLE_SIZE.width / farMountain_1->getContentSize().width);
	farMountain_1->setPosition(Vec2(VISIBLE_SIZE/ 2));
	this->addChild(farMountain_1);

	farMountain_2 = Sprite::createWithSpriteFrameName(L1_S2_FILENAME);
	farMountain_2->setScaleX(VISIBLE_SIZE.width / farMountain_2->getContentSize().width);
	farMountain_2->setPosition(Vec2(farMountain_1->getPositionX() + farMountain_2->getBoundingBox().size.width - 2, VISIBLE_SIZE.height / 2));
	this->addChild(farMountain_2);
}

void BackgroundLayer::addFarField(){
	farField_1 = Sprite::createWithSpriteFrameName(L2_S1_FILENAME);
	farField_1->setScaleX(VISIBLE_SIZE.width / farField_1->getContentSize().width);
	farField_1->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 4));
	this->addChild(farField_1);

	farField_2 = Sprite::createWithSpriteFrameName(L2_S2_FILENAME);
	farField_2->setScaleX(VISIBLE_SIZE.width / farField_2->getContentSize().width);
	farField_2->setPosition(Vec2(farField_1->getPositionX() + farField_1->getBoundingBox().size.width, VISIBLE_SIZE.height / 4));
	this->addChild(farField_2);
}

void BackgroundLayer::addDense(){
	dense_1 = Sprite::createWithSpriteFrameName(L3_S1_FILENAME);
	dense_1->setPosition(Vec2(dense_1->getBoundingBox().size.width / 2, VISIBLE_SIZE.height / 3));
	this->addChild(dense_1);

	dense_2 = Sprite::createWithSpriteFrameName(L3_S2_FILENAME);
	dense_2->setPosition(Vec2(dense_1->getPositionX() + dense_1->getBoundingBox().size.width - 2, VISIBLE_SIZE.height / 3));
	this->addChild(dense_2);

	dense_3 = Sprite::createWithSpriteFrameName(L3_S2_FILENAME);
	dense_3->setPosition(Vec2(dense_2->getPositionX() + dense_2->getBoundingBox().size.width - 2, VISIBLE_SIZE.height / 3));
	this->addChild(dense_3);
}

void BackgroundLayer::addNearField(){
	nearField_1 = Sprite::createWithSpriteFrameName(L4_S1_FILENAME);
	nearField_1->setScaleX(VISIBLE_SIZE.width / nearField_1->getContentSize().width);
	nearField_1->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 3));
	this->addChild(nearField_1);

	nearField_2 = Sprite::createWithSpriteFrameName(L4_S2_FILENAME);
	nearField_2->setScaleX(VISIBLE_SIZE.width / nearField_2->getContentSize().width);
	nearField_2->setPosition(Vec2(nearField_1->getPositionX() + nearField_2->getBoundingBox().size.width - 2, VISIBLE_SIZE.height / 3 - 2));
	this->addChild(nearField_2);

	nearField_3 = Sprite::createWithSpriteFrameName(L4_S3_FILENAME);
	nearField_3->setScaleX(VISIBLE_SIZE.width / nearField_3->getContentSize().width);
	nearField_3->setPosition(Vec2(nearField_2->getPositionX() + nearField_3->getBoundingBox().size.width - 2, VISIBLE_SIZE.height / 3 + 55));
	this->addChild(nearField_3);
}

void BackgroundLayer::addRoad(){
	road_1 = Sprite::createWithSpriteFrameName(G_S1_FILENAME);
	road_1->setPosition(Vec2(road_1->getBoundingBox().size.width / 2, road_1->getBoundingBox().size.height / 2));
	this->addChild(road_1);

	road_2 = Sprite::createWithSpriteFrameName(G_S2_FILENAME);
	road_2->setPosition(Vec2(road_1->getPositionX() + road_2->getBoundingBox().size.width - 2, road_2->getBoundingBox().size.height / 2));
	this->addChild(road_2);

	road_3 = Sprite::createWithSpriteFrameName(G_S3_FILENAME);
	road_3->setPosition(Vec2(road_2->getPositionX() + road_3->getBoundingBox().size.width - 2, road_3->getBoundingBox().size.height / 2));
	this->addChild(road_3);
}

void BackgroundLayer::addSundry(){
	//灌木丛 bosk
	for (int i = 1; i <= 4; i++)
	{
		std::string fileName_bosk = StringUtils::format(L5_BN_FILENAME, i);
		Sprite * bosk = Sprite::createWithSpriteFrameName(fileName_bosk);
		bosk->setScale(0.7f);
		if (i < 3)
		{
			bosk->setPosition(Vec2(road_1->getBoundingBox().size.width / 3 * i, road_1->getPositionY() + road_1->getBoundingBox().size.height / 3 + 15));
			road_1->addChild(bosk);
		}else if (i > 3)
		{
			bosk->setPosition(Vec2(road_2->getBoundingBox().size.width / 2, road_2->getPositionY() + road_2->getBoundingBox().size.height / 2));
			road_2->addChild(bosk);
		}else{
			bosk->setPosition(Vec2(road_3->getBoundingBox().size.width / 2, road_3->getPositionY() + road_3->getBoundingBox().size.height / 2));
			road_3->addChild(bosk);
		}
	}
	//路标 roadsign
	for (int i = 1; i <= 3; i++)
	{
		std::string fileName_roadsign = StringUtils::format(L5_SN_FILENAME, i);
		Sprite * roadsign = Sprite::createWithSpriteFrameName(fileName_roadsign);
		roadsign->setScale(0.7f);
		if (i == 1)
		{
			roadsign->setPosition(Vec2(road_1->getBoundingBox().size.width / 2, road_1->getPositionY() + road_1->getBoundingBox().size.height / 2));
			road_1->addChild(roadsign);
		}else if (i == 2)
		{
			roadsign->setPosition(Vec2(road_2->getBoundingBox().size.width / 2, road_2->getPositionY() + road_2->getBoundingBox().size.height + 15));
			road_2->addChild(roadsign);
		}else{
			roadsign->setPosition(Vec2(road_3->getBoundingBox().size.width / 3, road_3->getPositionY() + road_3->getBoundingBox().size.height / 2 + 15));
			road_3->addChild(roadsign);
		}
	}
}

void BackgroundLayer::addGrass(){
	grass_1 = Sprite::createWithSpriteFrameName(L7_S1_FILENAME);
	grass_1->setScaleX(VISIBLE_SIZE.width / grass_1->getContentSize().width);
	grass_1->setPosition(Vec2(grass_1->getBoundingBox().size.width / 2, grass_1->getBoundingBox().size.height / 2 - 12));
	this->addChild(grass_1);

	grass_2 = Sprite::createWithSpriteFrameName(L7_S2_FILENAME);
	grass_2->setScaleX(VISIBLE_SIZE.width / grass_2->getContentSize().width);
	grass_2->setPosition(Vec2(grass_1->getPositionX() + grass_2->getBoundingBox().size.width - 2, grass_2->getBoundingBox().size.height / 2 - 12));
	this->addChild(grass_2);
}

void BackgroundLayer::farMountainMove(float t){
	farMountain_1->setPositionX(farMountain_1->getPositionX() - BACKGROUND_SPEED * 0.05 * t);
	farMountain_2->setPositionX(farMountain_2->getPositionX() - BACKGROUND_SPEED * 0.05 * t);
	if (farMountain_1->getPositionX() + farMountain_1->getBoundingBox().size.width / 2 < 0)
	{
		farMountain_1->setPositionX(farMountain_2->getPositionX() + farMountain_1->getBoundingBox().size.width - 2);
	}
	if (farMountain_2->getPositionX() + farMountain_2->getBoundingBox().size.width / 2 < 0)
	{
		farMountain_2->setPositionX(farMountain_1->getPositionX() + farMountain_2->getBoundingBox().size.width - 2);
	}
}

void BackgroundLayer::fieldMove(float t){
	//远田野
	farField_1->setPositionX(farField_1->getPositionX() - BACKGROUND_SPEED * 0.2 * t);
	farField_2->setPositionX(farField_2->getPositionX() - BACKGROUND_SPEED * 0.2 * t);
	if (farField_1->getPositionX() + farField_1->getBoundingBox().size.width / 2 < 0)
	{
		farField_1->setPositionX(farField_2->getPositionX() + farField_1->getBoundingBox().size.width - 2);
	}
	if (farField_2->getPositionX() + farField_2->getBoundingBox().size.width / 2 < 0)
	{
		farField_2->setPositionX(farField_1->getPositionX() + farField_2->getBoundingBox().size.width - 2);
	}
	//近田野
	nearField_1->setPositionX(nearField_1->getPositionX() - BACKGROUND_SPEED * 0.4 * t);
	nearField_2->setPositionX(nearField_2->getPositionX() - BACKGROUND_SPEED * 0.4 * t);
	nearField_3->setPositionX(nearField_3->getPositionX() - BACKGROUND_SPEED * 0.4 * t);
	if (nearField_1->getPositionX() + nearField_1->getBoundingBox().size.width / 2 < 0)
	{
		nearField_1->setPositionX(nearField_3->getPositionX() + nearField_1->getBoundingBox().size.width - 2);
	}
	if (nearField_2->getPositionX() + nearField_2->getBoundingBox().size.width / 2 < 0)
	{
		nearField_2->setPositionX(nearField_1->getPositionX() + nearField_2->getBoundingBox().size.width - 2);
	}
	if (nearField_3->getPositionX() + nearField_3->getBoundingBox().size.width / 2 < 0)
	{
		nearField_3->setPositionX(nearField_2->getPositionX() + nearField_3->getBoundingBox().size.width - 2);
	}
}

void BackgroundLayer::denseMove(float t){
	dense_1->setPositionX(dense_1->getPositionX() - BACKGROUND_SPEED * 0.5 * t);
	dense_2->setPositionX(dense_2->getPositionX() - BACKGROUND_SPEED * 0.5 * t);
	dense_3->setPositionX(dense_3->getPositionX() - BACKGROUND_SPEED * 0.5 * t);
	if (dense_1->getPositionX() + dense_1->getBoundingBox().size.width / 2 < 0)
	{
		dense_1->setPositionX(dense_3->getPositionX() + dense_1->getBoundingBox().size.width - 2);
	}
	if (dense_2->getPositionX() + dense_2->getBoundingBox().size.width / 2 < 0)
	{
		dense_2->setPositionX(dense_1->getPositionX() + dense_2->getBoundingBox().size.width - 2);
	}
	if (dense_3->getPositionX() + dense_3->getBoundingBox().size.width / 2 < 0)
	{
		dense_3->setPositionX(dense_2->getPositionX() + dense_3->getBoundingBox().size.width - 2);
	}
}

void BackgroundLayer::roadMove(float t){
	road_1->setPositionX(road_1->getPositionX() - BACKGROUND_SPEED * 2 * t);
	road_2->setPositionX(road_2->getPositionX() - BACKGROUND_SPEED * 2 * t);
	road_3->setPositionX(road_3->getPositionX() - BACKGROUND_SPEED * 2 * t);
	if (road_1->getPositionX() + road_1->getBoundingBox().size.width / 2 < 0)
	{
		road_1->setPositionX(road_3->getPositionX() + road_1->getBoundingBox().size.width - 2);
	}
	if (road_2->getPositionX() + road_2->getBoundingBox().size.width / 2 < 0)
	{
		road_2->setPositionX(road_1->getPositionX() + road_2->getBoundingBox().size.width - 2);
	}
	if (road_3->getPositionX() + road_3->getBoundingBox().size.width / 2 < 0)
	{
		road_3->setPositionX(road_2->getPositionX() + road_3->getBoundingBox().size.width - 2);
	}
}

void BackgroundLayer::grassMove(float t){
	grass_1->setPositionX(grass_1->getPositionX() - BACKGROUND_SPEED * 3 * t);
	grass_2->setPositionX(grass_2->getPositionX() - BACKGROUND_SPEED * 3 * t);
	if (grass_1->getPositionX() + grass_1->getBoundingBox().size.width / 2 < 0)
	{
		grass_1->setPositionX(grass_2->getPositionX() + grass_1->getBoundingBox().size.width - 2);
	}
	if (grass_2->getPositionX() + grass_2->getBoundingBox().size.width / 2 < 0)
	{
		grass_2->setPositionX(grass_1->getPositionX() + grass_2->getBoundingBox().size.width - 2);
	}
}