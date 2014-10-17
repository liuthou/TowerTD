/*
从XML文件中读取怪物属性的类,用于初始化怪物.
怪物属性请从MonsterAttributeConfType.h中查找
*/

#ifndef __MONSTERATTRIBUTE_H_
#define __MONSTERATTRIBUTE_H_
#include "cocos2d.h"
#include "BasicAttribute.h"
#include "tinyxml2/tinyxml2.h"
#include "MonsterAttributeConfType.h"
#include "ModelAttribute.h"
USING_NS_CC;
class MonsterAttribute:public BasicAttribute{
public:
	//取得Monster属性类的单例
	//monsterid是怪物id
	static MonsterAttribute* getInstance(int monsterid);
	//删除单例
	static MonsterAttribute* destoryInstance();
	//获取相应的属性值
	//type:决定获取哪个属性值,defaultvalue:如果属性中没有这个值,则返回defaultvalue
	int getIntAttribute(MonsterAttributeConfType type,int defaultvalue);
	//对ModelAttribute中getStringAttribute的封装,要增加查询的type,需要先修改ModelAttribute中的函数
	//type:决定获取哪个属性值,defaultvalue:如果属性中没有这个值,则返回defaultvalue
	std::string getStringAttribute(MonsterAttributeConfType type,std::string defaultvalue);
protected:
	//从id_map中查找怪物属性的map
	virtual bool init(int monsterid);
	MonsterAttribute(){
	}
protected:
	int monsterid;
	static MonsterAttribute* monsterattribute;

};
#endif