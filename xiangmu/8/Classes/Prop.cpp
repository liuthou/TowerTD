#include "Prop.h"
#include "MainPlane.h"
#include "PhysicsHelper.h"

bool Prop::init(){
	if (!BaseAirObject::initWithFile("propBanShou.png")) 
	{ 
		return false;
	}
	auto vertexes = PhysicsHelper::getInstance()->getPhysicsShapeByName("propBanShou.plist");
	auto body = PhysicsBody::create();
	for (auto shapeVex : vertexes) {
		auto shape = PhysicsShapePolygon::create(shapeVex.data(), shapeVex.size());
		body->addShape(shape);
	}
	
	body->setGravityEnable(false);
	body->setDynamic(false);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);

	return true;
}

void Prop::effectWhileCollision(Ref *obj){
	auto plane = (MainPlane *)obj;
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->playEffect(CLIK_MUSIC);
	plane->eatProp(this);
	this->removeFromParentAndCleanup(true);
}