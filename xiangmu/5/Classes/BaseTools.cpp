#include "BaseTools.h"

BaseTools * BaseTools::create(std::string fileNameStr, int state, std::string m_name) {

	BaseTools * tool = new BaseTools();
	if (tool && tool->init(fileNameStr, state, m_name))
	{
		tool->autorelease();
		return tool;
	}
	CC_SAFE_DELETE(tool);
	return NULL;
}

bool BaseTools::init(std::string fileNameStr, int state, std::string m_name) {
	std::string fileName = StringUtils::format("%s.png",fileNameStr.c_str());
	if (!BaseSprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}
	this->m_type = "TOOL";
	this->m_state = state;
	this->m_name = m_name;
	addPhysicsBody();
	return true;
}

void BaseTools::removeBaseTool(){
	this->removeFromParentAndCleanup(true);
}

void BaseTools::addPhysicsBody(){
	m_body = PhysicsBody::createCircle(this->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	m_body->setDynamic(false);
	m_body->setGravityEnable(false);
	m_body->setCategoryBitmask(1);
	m_body->setCollisionBitmask(0);
	m_body->setContactTestBitmask(1);
	this->setPhysicsBody(m_body);
}