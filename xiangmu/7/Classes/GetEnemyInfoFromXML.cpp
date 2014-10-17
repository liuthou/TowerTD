#include "GetEnemyInfoFromXML.h"

GetEnemyInfoFromXML *GetEnemyInfoFromXML::instance = nullptr;

GetEnemyInfoFromXML *GetEnemyInfoFromXML::getinstance(){
	if(instance ==nullptr){
		instance = new GetEnemyInfoFromXML();
		instance->loadXML();
	}
	return instance;
}

void GetEnemyInfoFromXML::loadXML(){
	//可视区的大小
	Size visSize = Director::getInstance()->getVisibleSize();

//=======================================获取mapconfig.xml文件中的地图信息========================================
	
	int value = UserDefault::getInstance()->getIntegerForKey("ID",1);
	//找到文件
	auto xmlFileName = FileUtils::getInstance()->getStringFromFile("enemyconfig.xml");//得到文件的位置  
	//log("%s",xmlFileName.c_str());//验证是否正确

	tinyxml2::XMLDocument doc;							//创建解析器
	doc.Parse(xmlFileName.c_str());					//将文件盒解析器。。 
	XMLElement *root = doc.RootElement();				//获取根节点
	XMLElement *stage = root->FirstChildElement();
	while (stage!=nullptr){
		auto id = stage->Attribute("ID");
		int _id = atof(id);
		if (_id == value){
			ID = id;
			Stage = stage;
			break;
		}
		stage = stage->NextSiblingElement();
	}
	XMLElement *name = Stage->FirstChildElement();		//获取名字节点
	auto content = name->GetText();						//获取名字节点的内容
	std::string con = StringUtils::format("%s",content);
	
	name = name->NextSiblingElement();

	while (name!=nullptr){
		
		//获取属性节点(位置)
		auto _enemyname = name->Attribute("enemyname");
		auto _enemytype = name->Attribute("enemytype");
		auto _enemyspeed = name->Attribute("enemyspeed");
		auto _enemyposition_x = name->Attribute("enemyposition_x");
		auto _enemyposition_y = name->Attribute("enemyposition_y");
		auto _enemybody_x = name->Attribute("enemybody_x");
		auto _enemybody_y = name->Attribute("enemybody_y");
		auto _enemyAI = name->Attribute("enemyAI");

		//============================================在XML中获取的信息需要转换 ========================================
		auto enemX = atof(_enemyposition_x);
		auto enemY = atof(_enemyposition_y);
		auto posX = atof(_enemybody_x);
		auto posY = atof(_enemybody_y);
		auto enemAI = atof(_enemyAI);
		enemyName = _enemyname;
		enemyType = atof(_enemytype);
		enemySpeed = atof(_enemyspeed);
		//===============================================需要返回的 信息===============================================
		enemyPosition = Vec2(enemX,enemY);  //每个位置信息  放在 集合中
		allEnemyPosition.push_back(enemyPosition);

		enemyBody = Size(posX,posY);		//每个人的body大小   放在集合中
		allEnemyBody.push_back(enemyBody);

		allEnemyName.push_back(enemyName);		//每个人的名字  放在集合中

		allEnemyType.push_back(enemyType);		//每个人的类型   放在集合中

		allEnemySpeed.push_back(enemySpeed);		//每个人的 速度  放在集合中

		allEnemyAI.push_back(enemAI);

		name = name->NextSiblingElement();

	}

}


//返回小鬼的名字的集合
std::vector<std::string> GetEnemyInfoFromXML::getAllenemyName(){
	return allEnemyName;
}

//返回获取精灵类型的集合
std::vector<int> GetEnemyInfoFromXML::getAllEnemyType(){
	return allEnemyType;
}

//获取速度的集合
std::vector<int> GetEnemyInfoFromXML::getAllEnemySpeed(){
	return allEnemySpeed;
}

//获取位置信息的集合
std::vector<Vec2> GetEnemyInfoFromXML::getAllEnemyPosition(){
	return allEnemyPosition;
}

//小鬼刚体大小的集合
std::vector<Size> GetEnemyInfoFromXML::getAllEnemyBody(){
	return allEnemyBody;
}

//小鬼AI的集合
std::vector<int> GetEnemyInfoFromXML::getAllEnemyAI(){
	return allEnemyAI;
}

void GetEnemyInfoFromXML::clean(){
	allEnemyBody.clear();
	allEnemyPosition.clear();
	allEnemySpeed.clear();
	allEnemyType.clear();

}

void GetEnemyInfoFromXML::reloadXML(){
	loadXML();
}