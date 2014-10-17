#include "BaseBlock.h"
#include "GameData.h"
#include "PhysicsHelper.h"

bool BaseBlock::init(std::string fileNameStr, float attack, std::string m_name, Vec2 blockPos){
	std::string m_fileName = StringUtils::format("%s.png", fileNameStr.c_str());
	if (!BaseSprite::initWithSpriteFrameName(m_fileName))
	{
		return false;
	}
	this->m_type = "BLOCK";
	this->m_name = m_name;
	this->m_attack = attack * BLOCK_ATTACK;
	addPhysicsBody();
	//如果是飞刀，则运行动画
	if (m_name == "knife")
	{
		addKnifeAction();
	}
	//如果是铁链，运行动画
	if (m_name == "chainhook")
	{
		addChainhookAction(blockPos);
	}
	return true;
}

void BaseBlock::addKnifeAction()
{
	auto moveLeft = MoveBy::create(2, Vec2(-584, 0));
	auto rotate = RotateBy::create(2, -720);
	this->runAction(RepeatForever::create(Spawn::create(moveLeft, rotate, NULL)));
}


void BaseBlock::addPhysicsBody(){
	std::string fileName = StringUtils::format("%s.plist",m_name.c_str());
	std::vector<std::vector<Vec2>> vertexts = PhysicsHelper::getInstance()->getPhysicsShapeByName(fileName.c_str());
	m_body = PhysicsBody::create();
	for (std::vector<Vec2> shapeVex : vertexts) {
		auto shape = PhysicsShapePolygon::create(shapeVex.data(), shapeVex.size());
		m_body->addShape(shape);
	}
	// auto body = PhysicsBody::createBox(this->getContentSize());
	m_body->setGravityEnable(false);
	m_body->setDynamic(false);
	m_body->setCategoryBitmask(1);
	m_body->setCollisionBitmask(0);
	m_body->setContactTestBitmask(1);
	this->setPhysicsBody(m_body);
}

BaseBlock * BaseBlock::create(std::string fileNameStr, float attack, std::string m_name, Vec2 blockPos){
	BaseBlock * block = new BaseBlock();
	if (block && block->init(fileNameStr, attack, m_name, blockPos))
	{
		block->autorelease();
		return block;
	}
	CC_SAFE_DELETE(block);
	return nullptr;
}

void BaseBlock::addChainhookAction(Vec2 blockPos)
{
	float moveTime = CCRANDOM_0_1() * 4 + 1;
 	auto moveUp = MoveTo::create(moveTime, Vec2(blockPos.x, 600));
 	auto moveDown = MoveTo::create(moveTime, Vec2(blockPos.x, 400));
 	this->runAction(RepeatForever::create(Sequence::create(moveUp, moveDown, NULL)));
}

