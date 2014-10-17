#ifndef __TOWERATTRIBUTE_H_
#define __TOWERATTRIBUTE_H_
#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "TowerAttributeConfType.h"
#include "BasicAttribute.h"
#include "MonsterAttributeConfType.h"
USING_NS_CC;
using namespace tinyxml2;
class TowerAttribute: public BasicAttribute{
public:
	//取得Tower属性类的单例
	//towerid是塔id
	static TowerAttribute* getInstance(int towerid);
	//删除单例
	static TowerAttribute* destoryInstance();
	//从id_map中查找塔属性的map
	virtual bool init(int towerid);
	//获取塔的数量
	int getTowersCount();
	//type:决定获取哪个属性值,defaultvalue:如果属性中没有这个值,则返回defaultvalue
	int getIntAttribute(TowerAttributeConfType type,int defaultvalue);
	//对ModelAttribute中getStringAttribute的封装,要增加查询的type,需要先修改ModelAttribute中的函数
	//type:决定获取哪个属性值,defaultvalue:如果属性中没有这个值,则返回defaultvalue
	std::string getStringAttribute(TowerAttributeConfType type,std::string defaultvalue);
protected:
	int towerid;
	std::map<std::string,int> tmp_attribute_map;
	static TowerAttribute* towerattribute;
	TowerAttribute(){
	}
};
#endif