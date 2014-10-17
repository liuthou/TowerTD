#ifndef __DATACACHEGEAR_R_
#define __DATACACHEGEAR_R_

#include "cocos2d.h"
#include "string.h"
using namespace cocos2d;

enum
{
	DONTHAVE,
    HAVE,
	NO,
	YES,
	WEAPON,
	ARMOUR,
	SHOE 
};

class DataCacheGear : public Ref
{
private:
	char * _name;
	char * _picture;
public:
	//存放数据库中的装备的数据
	//装备的ID
	CC_SYNTHESIZE(int, _id, Id);
	//装备的伤害值
	CC_SYNTHESIZE(int, _attickValue, AttickValue);
	//装备的防御力
	CC_SYNTHESIZE(double, _defenseValue, DefenseValue);
	//装备的敏捷
	CC_SYNTHESIZE(double, _aglityValue, AglityValue);
	//装备的类型
	CC_SYNTHESIZE(int, _gearType, GearType);
	//装备的等级
	CC_SYNTHESIZE(int, _quality, Quality);
	//装备升一级属性的加成
	CC_SYNTHESIZE(double, _additionValue, AdditionValue);
	//装备所消耗的sp
	CC_SYNTHESIZE(int, _gearUserSp, GearUserSp);
	//英雄是否拥有
	CC_SYNTHESIZE(int, _heroHave, HeroHave);
	//英雄是否佩戴
	CC_SYNTHESIZE(int, _heroAdorn, HeroAdorn);
	//英雄拥有的数量
	CC_SYNTHESIZE(int, _haveNumber, HaveNumber);
	//获取装备的名字
	void setName(char * name)
	{
	    _name = new char();
		strcpy(_name,name);
	}
	char * getName()
	{
	   return _name;
	}
	//获取装备的图片名字
	void setPictureName(char * name)
	{
		_picture = new char();
		strcpy(_picture,name);
	}
	char * getPictureName()
	{
		return _picture;
	}
	virtual bool init();
	CREATE_FUNC(DataCacheGear);
	DataCacheGear(){}
	~DataCacheGear()
	{
	    delete [] _name;
		delete [] _picture;
	}
};

#endif