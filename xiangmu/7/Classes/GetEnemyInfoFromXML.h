#ifndef __GETENEMYINFOFROMXML_H_
#define __GETENEMYINFOFROMXML_H_

#include "cocos2d.h"
#include <tinyxml2/tinyxml2.h>
using namespace cocos2d;
using namespace tinyxml2;

class GetEnemyInfoFromXML{
private:
	GetEnemyInfoFromXML(const GetEnemyInfoFromXML &instance){}
	GetEnemyInfoFromXML(){}
	GetEnemyInfoFromXML operator=(const GetEnemyInfoFromXML &instance){return instance;}
public:
	static GetEnemyInfoFromXML *getinstance();
	static GetEnemyInfoFromXML *instance;

	void loadXML();
	tinyxml2::XMLElement *Stage;
	std::string ID;

	//===================================================–°πÌµƒ–≈œ¢===============================================
	//¥Ê¥¢°¢ªÒ»° –°πÌµƒ√˚◊÷
	std::string enemyName;
	std::vector<std::string> allEnemyName;
	std::vector<std::string> getAllenemyName();

	//ªÒ»°æ´¡È¿‡–Õ int
	int enemyType;
	std::vector<int> allEnemyType;
	std::vector<int> getAllEnemyType();

	//ªÒ»°ÀŸ∂»
	int enemySpeed;
	std::vector<int> allEnemySpeed;
	std::vector<int> getAllEnemySpeed();

	//ªÒ»°Œª÷√–≈œ¢
	Vec2 enemyPosition;
	std::vector<Vec2> allEnemyPosition;
	std::vector<Vec2> getAllEnemyPosition();

	//–°πÌ∏’ÃÂ¥Û–°
	Size enemyBody;
	std::vector<Size> allEnemyBody;
	std::vector<Size> getAllEnemyBody();

	//ªÒ»°AI
	int enemyAI;
	std::vector<int> allEnemyAI;
	std::vector<int> getAllEnemyAI();

	//…æ≥˝
	void clean();

	void reloadXML();

};

#endif
