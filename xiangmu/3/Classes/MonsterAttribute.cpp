#include "MonsterAttribute.h"
USING_NS_CC;
MonsterAttribute* MonsterAttribute::monsterattribute=nullptr;
//每次获取实例时,都传入怪的id
MonsterAttribute* MonsterAttribute::getInstance(int monsterid){
	if (monsterattribute==nullptr)
	{
		monsterattribute=new MonsterAttribute();
		monsterattribute->openXMLFIle(xmlfilename);
		monsterattribute->parseXML("Monsters");
	}
	CCASSERT(monsterattribute->init(monsterid),StringUtils::format("Couldn't found monster id:%d",monsterid).c_str());
	return monsterattribute;
}

MonsterAttribute* MonsterAttribute::destoryInstance(){
	CC_SAFE_DELETE(monsterattribute);
	monsterattribute = nullptr;
	return monsterattribute;
}
//从怪的id查找一个怪的属性map
 bool MonsterAttribute::init(int monsterid){
	 this->monsterid=monsterid;
	 auto it = id_intmap->find(monsterid);
	 if (it!=id_intmap->end())
	 {
		 tmp_attribute_intmap = it->second;
	 }else
	 {
		 return false;
	 }
	 auto it1 = id_stringmap->find(monsterid);
	 if (it1!=id_stringmap->end())
	 {
		 tmp_attribute_stringmap = it1->second;
	 }else
	 {
		 return false;
	 }
	 return true;
}
 //从怪的属性map取int形属性值
int MonsterAttribute::getIntAttribute(MonsterAttributeConfType type,int defaultvalue){
	if (type==MonsterAttributeConfType::Monster_ModelID)
	{
		auto it=tmp_attribute_intmap.find("ModelID");
			if (it!=tmp_attribute_intmap.end())
			{
				int value=it->second;
				return value;
			}
	}
	if (type==MonsterAttributeConfType::Monster_Attack)
	{
		auto it=tmp_attribute_intmap.find("Attack");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_AttackScope)
	{
		auto it=tmp_attribute_intmap.find("AttackScope");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Defence)
	{
		auto it=tmp_attribute_intmap.find("Defence");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_HP)
	{
		auto it=tmp_attribute_intmap.find("Hp");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Firespeed)
	{
		auto it=tmp_attribute_intmap.find("Firespeed");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Movespeed)
	{
		auto it=tmp_attribute_intmap.find("Movespeed");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_SkillID)
	{
		auto it=tmp_attribute_intmap.find("SkillID");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Bullet_FlySpeed)
	{
		auto it=tmp_attribute_intmap.find("BulletSpeed");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Price)
	{
		auto it=tmp_attribute_intmap.find("Price");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	return defaultvalue;
}
std::string MonsterAttribute::getStringAttribute(MonsterAttributeConfType type,std::string defaultvalue){
	if (type==MonsterAttributeConfType::Monster_Sprite)
	{
		auto it = tmp_attribute_stringmap.find("Sprite");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Runanimate)
	{
		auto it = tmp_attribute_stringmap.find("Runanimate");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Dieanimate)
	{
		auto it = tmp_attribute_stringmap.find("Dieanimate");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==MonsterAttributeConfType::Monster_Bullet_Pic)
	{
		auto it = tmp_attribute_stringmap.find("BulletPic");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	return defaultvalue;
}
