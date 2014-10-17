#include "Edge.h"

bool Edge::init(){
	if (!Node::init())
	{
		return false;

	}
	//获取可视区域的大小
	Size visSize = Director::getInstance()->getVisibleSize();
	//创建
	setPhysicsBody(PhysicsBody::createEdgeBox(Size(visSize.width,visSize.height)));
	//设置可以参与碰撞
	getPhysicsBody()->setContactTestBitmask(1);
	//设置大小
	setContentSize(visSize);
	//this->getPhysicsBody()->getShape(0)->setRestitution(100);
	this->getPhysicsBody()->setCategoryBitmask(1);
	this->getPhysicsBody()->setCollisionBitmask(1);
	this->getPhysicsBody()->setContactTestBitmask(1);


	return true;


}