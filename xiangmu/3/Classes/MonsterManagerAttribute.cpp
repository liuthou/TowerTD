#include "MonsterManagerAttribute.h"
#include "MonsterManagerAttributeConfType.h"
MonsterManagerAttribute* MonsterManagerAttribute::monstermanagerattribute=nullptr;
MonsterManagerAttribute* MonsterManagerAttribute::getInstance(){
	if (monstermanagerattribute==nullptr)
	{
		monstermanagerattribute = new MonsterManagerAttribute();
		monstermanagerattribute->openXMLFIle(xmlfilename);
		monstermanagerattribute->parseXML("Waves");
	}
//	CCASSERT(monstermanagerattribute->init(wavesnum),StringUtils::format("couldn't found wave information :%d",wavesnum).c_str());
	return monstermanagerattribute;
}

MonsterManagerAttribute* MonsterManagerAttribute::destoryInstance(){
	CC_SAFE_DELETE(monstermanagerattribute);
	monstermanagerattribute = nullptr;
	return monstermanagerattribute;
}
bool MonsterManagerAttribute::init(int wavesnum){
	this->wavesnum = wavesnum;
	auto it = id_intmap->find(wavesnum);
	if (it!=id_intmap->end())
	{
		tmp_attribute_intmap = it->second;
	}else
	{
		return false;
	}
	auto it1 = id_stringmap->find(wavesnum);
	if (it1!=id_stringmap->end())
	{
		tmp_attribute_stringmap = it1->second;
	}else
	{
		return false;
	}
	return true;
}
int MonsterManagerAttribute::getWavesCount(){
	return id_intmap->size();
}
int MonsterManagerAttribute::getIntAttribute(int wavesnum,MonsterManagerAttributeConfigType type,int defaultvalue){
	CCASSERT(monstermanagerattribute->init(wavesnum),StringUtils::format("couldn't found wave information :%d",wavesnum).c_str());
	if (type==MonsterManagerAttributeConfigType::MonsterManager_MonsterID)
	{
		auto it=tmp_attribute_intmap.find("MonsterID");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterManagerAttributeConfigType::MonsterManager_Delaytime)
	{
		auto it=tmp_attribute_intmap.find("Delaytime");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	if (type==MonsterManagerAttributeConfigType::MonsterManager_Monsternum)
	{
		auto it=tmp_attribute_intmap.find("Monsternum");
		if (it!=tmp_attribute_intmap.end())
		{
			int value=it->second;
			return value;
		}
	}
	return defaultvalue;
}
std::string MonsterManagerAttribute::getStringAttribute(int wavesnum,MonsterManagerAttributeConfigType type,std::string defaultvalue){
	CCASSERT(monstermanagerattribute->init(wavesnum),StringUtils::format("couldn't found wave information :%d",wavesnum).c_str());

	return defaultvalue;
}