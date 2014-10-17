#include "BoundingLayer.h"
#include "BaseSprite.h"
#include "Role.h"

bool BoundingLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	addPhysicsEvent();
	return true;
}

void BoundingLayer::addPhysicsEvent(){
	auto event = EventListenerPhysicsContact::create();
	event->onContactBegin = [=](PhysicsContact& contact){
		BaseSprite *spriteA = dynamic_cast<BaseSprite *>(contact.getShapeA()->getBody()->getNode());
		if (spriteA == nullptr)
		{
			return true;
		}
		BaseSprite *spriteB = dynamic_cast<BaseSprite *>(contact.getShapeB()->getBody()->getNode());
		if (spriteB == nullptr)
		{
			return true;
		}
		if (spriteB->getM_type() == "TOOL" )
		{
			BaseTools *spriteB =  dynamic_cast<BaseTools *>(contact.getShapeB()->getBody()->getNode());
			
			spriteB->setVisible(false);
			spriteB->getM_body()->setCategoryBitmask(0);
			std::string toolName = spriteB->getM_name();
			notification(spriteB);
			Role * spriteA = dynamic_cast<Role *>(contact.getShapeA()->getBody()->getNode());
			spriteA->changeState(spriteB->getM_state());
		}else if (spriteA->getM_type() == "TOOL")
		{
			BaseTools *spriteA =  dynamic_cast<BaseTools *>(contact.getShapeA()->getBody()->getNode());
			
			spriteA->setVisible(false);
			spriteA->getM_body()->setCategoryBitmask(0);
			std::string toolName = spriteB->getM_name();
			notification(spriteA);
			Role * spriteB = dynamic_cast<Role *>(contact.getShapeB()->getBody()->getNode());
			spriteB->changeState(spriteA->getM_state());
		}else if(spriteB->getM_type() == "BLOCK")
		{
			BaseBlock *spriteB = dynamic_cast<BaseBlock *>(contact.getShapeB()->getBody()->getNode());
			
			spriteB->getM_body()->setCategoryBitmask(0);
			std::string blockName = spriteB->getM_name();
			notification(spriteB);
			Role * spriteA = dynamic_cast<Role *>(contact.getShapeA()->getBody()->getNode());
			if (blockName == "e_fence")
			{
				spriteA->hurt(spriteB->getM_attack(), true);
			}else
			{
				spriteA->hurt(spriteB->getM_attack(), false);
			}
		}else if(spriteA->getM_type() == "BLOCK")
		{
			BaseBlock *spriteA = dynamic_cast<BaseBlock *>(contact.getShapeA()->getBody()->getNode());
			
			spriteA->getM_body()->setCategoryBitmask(0);
			std::string blockName = spriteA->getM_name();
			notification(spriteA);
			Role * spriteB = dynamic_cast<Role *>(contact.getShapeB()->getBody()->getNode());
			if (blockName == "e_fence")
			{
				spriteB->hurt(spriteA->getM_attack(), true);
			}else
			{
				spriteB->hurt(spriteA->getM_attack(), false);
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event,this);
}

void BoundingLayer::notification(BaseSprite * sprite){
	__NotificationCenter::getInstance()->postNotification("task", sprite);
}