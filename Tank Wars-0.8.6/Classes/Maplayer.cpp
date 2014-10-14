#include "MapLayer.h"


bool MapLayer::init(){
	if (!Layer::init()){
		return false;
	}
	count =4;
	
	

	//地图的载入
	map = TMXTiledMap::create("map.tmx");


	//做好的地图中的背景层
	bgLayer = map->getLayer("bg");
	bgLayer->setZOrder(-1);
	//bgLayer->setNormalizedPosition(Vec2(0.2, 0));
	bossLayer = map->getLayer("boss");
	bossLayer->setVisible(false);
	//偏差
	offX =/*Director::getInstance()->getVisibleSize().width*0.2 -64*/0;
		
	this->addChild(map);

	//对象层获取
	object = map->getObjectGroup("obj");
	//初始化坐标点
	initPointsVector(offX);
// 	log("%d", checkNodeBreak(Vec2(100, 500)));
// 	log("%d", checkNodeBreak(Vec2(100, 100)));
// 	auto sp = Sprite::createWithSpriteFrameName("p1.png");
// 	sp->setPosition(pointsVector.at(0)->getPosition());
// 	this->addChild(sp);
// 	auto sp1 = Sprite::createWithSpriteFrameName("p1.png");
// 	sp1->setPosition(pointsVector.at(1)->getPosition());
// 	this->addChild(sp1);
// 	auto sp2 = Sprite::createWithSpriteFrameName("p1.png");
// 	sp2->setPosition(pointsVector.at(2)->getPosition());
// 	this->addChild(sp2);
// 	auto sp3 = Sprite::createWithSpriteFrameName("p1.png");
// 	sp3->setPosition(pointsVector.at(3)->getPosition());
// 	this->addChild(sp3);
	//
// 	auto sp1 = Sprite::createWithSpriteFrameName("p1.png");
// 	sp1->setPosition(pointsVector.at(1)->getPosition());
// 	this->addChild(sp1);
// 	auto sp2 = Sprite::createWithSpriteFrameName("p1.png");
// 	sp2->setPosition(pointsVector.at(2)->getPosition());
// 	this->addChild(sp2);
// 	auto sp3 = Sprite::createWithSpriteFrameName("p1.png");
// 	sp3->setPosition(pointsVector.at(3)->getPosition());
// 	this->addChild(sp3);
	return true;
}
//获取坐标点
void MapLayer::initPointsVector(float offX){
	Node* runOfPoint = nullptr;

	//1
	int count = 1;
	ValueMap point;
	
	//2
	while (count<5)
	{
		point = object->getObject(std::to_string(count));
	
		//3
		auto x = point.at("x").asFloat();
		auto y = point.at("y").asFloat();
		//4
		runOfPoint = Node::create();
		runOfPoint->setPosition(Vec2(x + offX , y));
		this->pointsVector.pushBack(runOfPoint);
		//point = object->getObject(std::to_string(count));
		count++;
		
	runOfPoint = nullptr;
	}
}
//返回坐标点0~3
Vec2 MapLayer::getState(int i){
	Vec2 point = pointsVector.at(i)->getPosition();
	return point;
}
//坐标的转换
//坐标
Vec2 MapLayer::converTotileCoord(Vec2 position){
	int x = (position.x - offX) / map->getContentSize().width*map->getMapSize().width;
	int y = map->getMapSize().height - position.y / map->getContentSize().height*map->getMapSize().height;
	return Vec2(x, y);
}
// Vec2 MapLayer::converToMatrixCoord(Vec2 position){
// 	int x = (position.x + offX) / map->getContentSize().width*map->getMapSize().width;
// 	int y = position.y / map->getContentSize().height*map->getMapSize().height;
// 	return Vec2(x, y);
// }

//检查是否有东西
bool MapLayer::checkIsNode(Vec2 position){

	Vec2 towerCoord = converTotileCoord(Vec2(position.x,position.y));//地图坐标
	//Vec2 matrixCoord = converToMatrixCoord(position);//数组位置
	if (towerCoord.x>=40||towerCoord.x<0)
	{
		return false;
	}
	if (towerCoord.y>=40||towerCoord.y<0)
	{
		return false;
	}
	int gid = bgLayer->getTileGIDAt(towerCoord);//得到gid
	//得到了该图块的GID可以通过属性判断是否可以用子弹打包
	if (!gid || gid == 5 || gid == 6 || gid == 19 || gid == 20){
		return false;
	}return true;
}


//检查是否可以破坏
bool MapLayer::checkNodeBreak(Vec2 position){
	Vec2 towerCoord = converTotileCoord(position);//地图坐标
	//Vec2 matrixCoord = converToMatrixCoord(position);//数组位置
	int gid = bgLayer->getTileGIDAt(towerCoord);//得到gid
	//得到了该图块的GID可以通过属性判断是否可以用子弹打包
	
	auto titleTemp =  (map->getPropertiesForGID(gid).asValueMap());

	bool BreakValue;
	
	BreakValue = titleTemp.at("canBreak").asBool();
	return BreakValue;

}
bool MapLayer::checkNodeWrite(Vec2 position)//检查是否为水{
{
	Vec2 towerCoord = converTotileCoord(position);//地图坐标
	//Vec2 matrixCoord = converToMatrixCoord(position);//数组位置
	int gid = bgLayer->getTileGIDAt(towerCoord);//得到gid
	if (gid == 7 || gid == 8 || gid == 21 || gid == 22){
		return true;
	}
	return false;
}
// 将该点的精灵移出, 因为受到子弹攻击
bool MapLayer::breakNode(Vec2 position){
	if (checkIsNode(position)&&checkNodeBreak(position)&&!checkNodeWrite(position)){
	
	Vec2 towerCoord = converTotileCoord(position + Vec2(0,0));//地图坐标
	 
	auto sptoBreak = bgLayer->tileAt(towerCoord);
	if (bgLayer->getTileGIDAt(towerCoord) == 11 || bgLayer->getTileGIDAt(towerCoord) == 12 || bgLayer->getTileGIDAt(towerCoord) == 25 || bgLayer->getTileGIDAt(towerCoord) == 26){
		count--;
	}
	if (sptoBreak){
		sptoBreak->removeFromParentAndCleanup(true);
		
	}
	 
	}
	return true;
}
//检查是否失败,就是基地有没有被打爆
bool MapLayer::isDefeated(){
	if (count==0){
		return true;
	}
	return false;
}void MapLayer::failed()//失败调用的方法
{
	bossLayer->setVisible(true);
}