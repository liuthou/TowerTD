#include "MonsterBoss.h"
#include "tinyxml2/tinyxml2.h"
#include "AnimateClass.h"
using namespace tinyxml2;
MonsterBoss *MonsterBoss::create(std::string filename)
{
	auto boss = new MonsterBoss();
	if (boss &&boss->init(filename)){
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return nullptr;
}
bool MonsterBoss::init(std::string filename)
{
	//读取xml的数据
	auto fileName = FileUtils::getInstance()->fullPathForFilename(filename);
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	XMLElement *  root = xmlDoc.RootElement();
	XMLElement *  xmlbg1 = root->FirstChildElement("Sprite3");
	const char * name = xmlbg1->Attribute("name");
	xmlname = StringUtils::format("%s", name);
	int hp = xmlbg1->IntAttribute("hp");
	int id = xmlbg1->IntAttribute("ID");
	float speed = xmlbg1->IntAttribute("speed");
	int exp = xmlbg1->IntAttribute("exp");
	int attack = xmlbg1->IntAttribute("attack");
	//float x = xmlbg1->FloatAttribute("X");
	float y = xmlbg1->FloatAttribute("Y");
	if (!MonsterBase::initWithSpriteFrameName(name, hp, attack, id, speed, exp))
	{
		return false;
	}
	float x = CCRANDOM_0_1() * 960+800;
	this->setPosition(x, y+this->getContentSize().height/4);
	return true;
}

