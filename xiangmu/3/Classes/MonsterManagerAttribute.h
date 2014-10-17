#ifndef __MONSTERMANAGERATTRIBUTE_H_
#define __MONSTERMANAGERATTRIBUTE_H_
#include "cocos2d.h"
#include "BasicAttribute.h"
#include "MonsterManagerAttributeConfType.h"
USING_NS_CC;
class MonsterManagerAttribute:public BasicAttribute{
public:
	static MonsterManagerAttribute* getInstance();
	//删除单例
	static MonsterManagerAttribute* destoryInstance();
	virtual bool init(int wavesnum);
	int getWavesCount();
	//type:决定获取哪个属性值,defaultvalue:如果属性中没有这个值,则返回defaultvalue
	int getIntAttribute(int wavesnum,MonsterManagerAttributeConfigType type,int defaultvalue);
	//对ModelAttribute中getStringAttribute的封装,要增加查询的type,需要先修改ModelAttribute中的函数
	//type:决定获取哪个属性值,defaultvalue:如果属性中没有这个值,则返回defaultvalue
	std::string getStringAttribute(int wavesnum,MonsterManagerAttributeConfigType type,std::string defaultvalue);
protected:
	static MonsterManagerAttribute* monstermanagerattribute;
	int wavesnum;
};
#endif