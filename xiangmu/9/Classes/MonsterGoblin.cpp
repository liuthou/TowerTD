 #include "MonsterGoblin.h"
#include "tinyxml2/tinyxml2.h"
#include "AnimateClass.h"
using namespace tinyxml2;
MonsterGoblin *MonsterGoblin::create(std::string filename)
{
	auto goblin = new MonsterGoblin();
	if (goblin &&goblin->init(filename)){
		goblin->autorelease();
		return goblin;
	}
	CC_SAFE_DELETE(goblin);
	return nullptr;
}
bool MonsterGoblin::init(std::string filename)
{
	auto fileName = FileUtils::getInstance()->fullPathForFilename(filename);
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	XMLElement *  root = xmlDoc.RootElement();
	XMLElement *  xmlbg1 = root->FirstChildElement();
	const char * name = xmlbg1->Attribute("name");
	xmlname = StringUtils::format("%s", name);
	int hp = xmlbg1->IntAttribute("hp");
	int id = xmlbg1->IntAttribute("ID");
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
