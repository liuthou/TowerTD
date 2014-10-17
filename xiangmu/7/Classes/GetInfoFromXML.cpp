#include "GetInfoFromXML.h"

GetInfoFromXML *GetInfoFromXML::instance = nullptr;

GetInfoFromXML *GetInfoFromXML::getinstance(){
	if(instance ==nullptr){
		instance = new GetInfoFromXML();
	
		instance->loadXML();
	}
	return instance;
}

void GetInfoFromXML::reloadXML(){
	loadXML();
}

void GetInfoFromXML::loadXML(){
	//可视区的大小



	Size visSize = Director::getInstance()->getVisibleSize();

//=======================================获取mapconfig.xml文件中的地图信息========================================
	
    int value = UserDefault::getInstance()->getIntegerForKey("ID",1);
	//找到文件
	auto xmlFileName = FileUtils::getInstance()->getStringFromFile("mapconfig.xml");//得到文件的位置  
	//log("%s",xmlFileName.c_str());//验证是否正确

	tinyxml2::XMLDocument doc;						//创建解析器
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
	
	mapName = con;									//将要返回的 地图的名字

	name = name->NextSiblingElement();

	while (name!=nullptr){
		//获取属性节点(位置)
		auto gro_posx = name->Attribute("gro_posx");
		auto gro_posy = name->Attribute("gro_posy");
		auto gro_width = name->Attribute("gro_width");
		//转换 
		float _one = atof(gro_posx);
		float _two = atof(gro_posy);
		float _three = atof(gro_width);

		bordPos = Vec2(_one,_two);   //将要返回的 地板的坐标
		bordsVector.push_back(bordPos);//存放进集合
		mapWidth = _three;			//将要返回的 地板的宽度
		allWidth.push_back(mapWidth);
		log("%d",allWidth.size());
		name = name->NextSiblingElement();

	}

}

std::vector<Vec2> GetInfoFromXML::getBordVector(){
	return bordsVector;
}

std::vector<float> GetInfoFromXML::getAllWidth(){
	return allWidth;
}

void GetInfoFromXML::clean(){
	allWidth.clear();
	bordsVector.clear();

}
