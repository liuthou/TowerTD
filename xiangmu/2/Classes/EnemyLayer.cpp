#include "EnemyLayer.h"
#include "SelectRole.h"
#include "tinyxml2/tinyxml2.h"
#include "choseInformation.h"
#include "CowEnemy.h"
#include "SnakeEnemy.h"
#include "DinosaurEnemy.h"
#include "OxEnemy.h"
#include "OneOxEnemy.h"
bool EnemyLayer::init()	{
	if(!Layer::init()){
		return false;
	}
	enemyXml = choseInformation::getInstence()->getFileNameXml();
	ReadEnemyXml();
	return true;
}

std::string EnemyLayer::ReadEnemyXml(){
	if(enemyXml == "over"){
		return "over";
	}
	std::string fileXmlWay = FileUtils::getInstance()->getStringFromFile(enemyXml);
	tinyxml2::XMLDocument doc;
	doc.Parse(fileXmlWay.c_str());
	tinyxml2::XMLElement *root = doc.RootElement();
	tinyxml2::XMLElement *FileNameXml = root->FirstChildElement();
	enemyXml = FileNameXml->Attribute("NAME");
	std::string imageName = FileNameXml->Attribute("IMAGE");
	tinyxml2::XMLElement *Enemy = FileNameXml->NextSiblingElement();
	tinyxml2::XMLElement *enemy = Enemy->FirstChildElement();
	while(enemy != nullptr){
		std::string kind = enemy->Attribute("KIND");
		int positionX = enemy->IntAttribute("X");
		int positionY = enemy->IntAttribute("Y");
		std::string FileNameXml = enemy->Attribute("XML");
		if(kind == "walk"){
			enemyWalk = EnemyWalkOne::create(FileNameXml);
			enemyWalk->setPosition(positionX,positionY);
			enemyWalk->setArmaturestatic(moveStatic);
			SelectRole::getInstence()->addArmature(enemyWalk);
			this->addChild(enemyWalk);
		}else if(kind == "fly"){
			enemyFly = EnemyOne::create(FileNameXml);
			enemyFly->setPosition(positionX,positionY);
			enemyFly->setArmaturestatic(moveStatic);
			this->addChild(enemyFly);
			SelectRole::getInstence()->addArmature(enemyFly);
		}else if(kind == "snake"){
			SnakeEnemy *snake = SnakeEnemy::create(FileNameXml);
			snake->setPosition(positionX,positionY);
			snake->setArmaturestatic(moveStatic);
			this->addChild(snake);
			SelectRole::getInstence()->addArmature(snake);
		}else if(kind == "dinosaur"){
			DinosaurEnemy *dinosaur = DinosaurEnemy::create(FileNameXml);
			dinosaur->setPosition(positionX,positionY);
			dinosaur->setArmaturestatic(moveStatic);
			this->addChild(dinosaur);
			SelectRole::getInstence()->addArmature(dinosaur);
		}else if(kind == "cow"){
			CowEnemy *cow = CowEnemy::create(FileNameXml);
			cow->setPosition(positionX,positionY);
			cow->setArmaturestatic(moveStatic);
			this->addChild(cow);
			SelectRole::getInstence()->addArmature(cow);
		}else if(kind == "ox"){

			OxEnemy *ox = OxEnemy::create(FileNameXml);
			ox->setPosition(positionX,positionY);
			ox->setArmaturestatic(moveStatic);
			this->addChild(ox);
			SelectRole::getInstence()->addArmature(ox);
		}else{

			OneOxEnemy *oneox = OneOxEnemy::create(FileNameXml);
			oneox->setPosition(positionX,positionY);
			oneox->setArmaturestatic(moveStatic);
			this->addChild(oneox);
			SelectRole::getInstence()->addArmature(oneox);
		}
		enemy = enemy->NextSiblingElement();
	}
	return imageName;
}