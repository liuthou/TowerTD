#include "TowerAttribute.h"
#include "ModelAttribute.h"
#include "TowerAttributeConfType.h"
USING_NS_CC;
TowerAttribute* TowerAttribute::towerattribute=nullptr;
//每次获取实例时,都传入塔的id
TowerAttribute* TowerAttribute::getInstance(int towerid){
	if (towerattribute==nullptr)
	{
		towerattribute=new TowerAttribute();
		towerattribute->openXMLFIle(xmlfilename);
		towerattribute->parseXML("Towers");
	}
	CCASSERT(towerattribute->init(towerid),StringUtils::format("Couldn't found tower id:%d",towerid).c_str());
	return towerattribute;
}

TowerAttribute* TowerAttribute::destoryInstance(){
	CC_SAFE_DELETE(towerattribute);
	towerattribute = nullptr;
	return towerattribute;
}

//从塔的id查找一个塔的属性map
bool TowerAttribute::init(int towerid){
	this->towerid=towerid;
	auto it = id_intmap->find(towerid);
	if (it!=id_intmap->end())
	{
		tmp_attribute_intmap = it->second;
	}else
	{
		return false;
	}
	auto it1 = id_stringmap->find(towerid);
	if (it1!=id_stringmap->end())
	{
		tmp_attribute_stringmap = it1->second;
	}else
	{
		return false;
	}
	return true;
}

int TowerAttribute::getTowersCount(){
	return id_intmap->size();
}

//从塔的属性map取属性值
int TowerAttribute::getIntAttribute(TowerAttributeConfType type,int defaultvalue){
	if (type==TowerAttributeConfType::Tower_ModelID)
	{
		auto it=tmp_attribute_intmap.find("ModelID");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Attack)
	{
		auto it=tmp_attribute_intmap.find("Attack");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_AttackScope)
	{
		auto it=tmp_attribute_intmap.find("AttackScope");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Defence)
	{
		auto it=tmp_attribute_intmap.find("Defence");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_HP)
	{
		auto it=tmp_attribute_intmap.find("Hp");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Firespeed)
	{
		auto it=tmp_attribute_intmap.find("Firespeed");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Movespeed)
	{
		auto it=tmp_attribute_intmap.find("Movespeed");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Lowspeedtime)
	{
		auto it=tmp_attribute_intmap.find("Lowspeedtime");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Frozentime)
	{
		auto it=tmp_attribute_intmap.find("Frozentime");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Firetime)
	{
		auto it=tmp_attribute_intmap.find("Firetime");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_SkillID)
	{
		auto it=tmp_attribute_intmap.find("SkillID");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Bullet_FlySpeed)
	{
		auto it=tmp_attribute_intmap.find("BulletSpeed");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==TowerAttributeConfType::Tower_Price)
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


std::string TowerAttribute::getStringAttribute(TowerAttributeConfType type,std::string defaultvalue){
	if (type==TowerAttributeConfType::Tower_Sprite)
	{
		auto it = tmp_attribute_stringmap.find("Sprite");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==TowerAttributeConfType::Tower_Runanimate)
	{
		auto it = tmp_attribute_stringmap.find("Runanimate");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==TowerAttributeConfType::Tower_Dieanimate)
	{
		auto it = tmp_attribute_stringmap.find("Dieanimate");
		if (it != tmp_attribute_stringmap.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==TowerAttributeConfType::Tower_Bullet_Pic)
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
