#include "MonsterSoldier.h"
#include "tinyxml2/tinyxml2.h"
#include "AnimateClass.h"
using namespace tinyxml2;

MonsterSoldier *MonsterSoldier::create(std::string filename)
{
	auto soldier = new MonsterSoldier();
	if (soldier &&soldier->init(filename)){
		soldier->autorelease();
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}
bool MonsterSoldier::init(std::string filename)
{
	auto fileName = FileUtils::getInstance()->fullPathForFilename(filename);
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	XMLElement *  root = xmlDoc.RootElement();
	XMLElement *  xmlbg1 = root->FirstChildElement("Sprite2");
	const char * name = xmlbg1->Attribute("name");
	xmlname = StringUtils::format("%s", name);
	int id = xmlbg1->IntAttribute("ID");
	int hp = xmlbg1->IntAttribute("hp");
	float speed = xmlbg1->IntAttribute("speed");
	int exp = xmlbg1->IntAttribute("exp");
	int attack = xmlbg1->IntAttribute("attack");
	float y = xmlbg1->FloatAttribute("Y");
	if (!MonsterBase::initWithSpriteFrameName(name, hp, attack, id, speed, exp))
	{
		return false;
	}
	float x = CCRANDOM_0_1() * 1500 + 480;
	this->setPosition(x, y);
	return true;
}

