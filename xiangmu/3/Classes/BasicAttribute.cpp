#include "BasicAttribute.h"
USING_NS_CC;
std::string BasicAttribute::xmlfilename="";
tinyxml2::XMLDocument* BasicAttribute::xmldocument = nullptr;
void BasicAttribute::parseXML(std::string elementname){
	if (xmldocument)
	{
		log("parseXML");
		XMLElement* root=xmldocument->RootElement();
		log("xml get root child element");
		//取怪物或者塔的根节点
		const XMLElement* element = root->FirstChildElement(elementname.c_str());
		if (!element)
		{
			return;
		}
		const XMLElement* att_element=element->FirstChildElement();
		log("xml get first child element");
		while (att_element)
		{
			//取id
			int id = att_element->IntAttribute("ID");

			//取整形属性
//			tmp_attribute_map = new std::map<std::string,int>();
			if (att_element->FindAttribute("ModelID"))
			{
				int modeid = att_element->IntAttribute("ModelID");
				tmp_attribute_intmap["ModelID"] = modeid;
			}
			if (att_element->FindAttribute("Attack"))
			{
				int attack = att_element->IntAttribute("Attack");
				tmp_attribute_intmap["Attack"] = attack;
			}
			if (att_element->FindAttribute("Defence"))
			{
				int defence = att_element->IntAttribute("Defence");
				tmp_attribute_intmap["Defence"] = defence;
			}
			if (att_element->FindAttribute("Hp"))
			{
				int hp = att_element->IntAttribute("Hp");
				tmp_attribute_intmap["Hp"] = hp;
			}
			if (att_element->FindAttribute("Firespeed"))
			{
				int firespeed = att_element->IntAttribute("Firespeed");
				tmp_attribute_intmap["Firespeed"] = firespeed;
			}
			if (att_element->FindAttribute("Movespeed"))
			{
				int movespeed = att_element->IntAttribute("Movespeed");
				tmp_attribute_intmap["Movespeed"] = movespeed;
			}
			if (att_element->FindAttribute("SkillID"))
			{
				int skillid = att_element->IntAttribute("SkillID");
				tmp_attribute_intmap["SkillID"] = skillid;
			}
			if (att_element->FindAttribute("AttackScope"))
			{
				int attackscope = att_element->IntAttribute("AttackScope");
				tmp_attribute_intmap["AttackScope"] = attackscope;
			}
			if (att_element->FindAttribute("BulletSpeed"))
			{
				int bulletspeed = att_element->IntAttribute("BulletSpeed");
				tmp_attribute_intmap["BulletSpeed"] = bulletspeed;
			}
			if (att_element->FindAttribute("Price"))
			{
				int price = att_element->IntAttribute("Price");
				tmp_attribute_intmap["Price"] = price;
			}
			if (att_element->FindAttribute("MonsterID"))
			{
				int price = att_element->IntAttribute("MonsterID");
				tmp_attribute_intmap["MonsterID"] = price;
			}
			if (att_element->FindAttribute("Delaytime"))
			{
				int price = att_element->IntAttribute("Delaytime");
				tmp_attribute_intmap["Delaytime"] = price;
			}
			if (att_element->FindAttribute("Monsternum"))
			{
				int price = att_element->IntAttribute("Monsternum");
				tmp_attribute_intmap["Monsternum"] = price;
			}
			if (att_element->FindAttribute("Lowspeedtime"))
			{
				int lowspeedtime = att_element->IntAttribute("Lowspeedtime");
				tmp_attribute_intmap["Lowspeedtime"] = lowspeedtime;
			}
			if (att_element->FindAttribute("Frozentime"))
			{
				int frozentime = att_element->IntAttribute("Frozentime");
				tmp_attribute_intmap["Frozentime"] = frozentime;
			}
			if (att_element->FindAttribute("Firetime"))
			{
				int firetime = att_element->IntAttribute("Firetime");
				tmp_attribute_intmap["Firetime"] = firetime;
			}
			//将一条记录加入map
			id_intmap->insert(std::pair <int,std::map<std::string,int> >(id,tmp_attribute_intmap));
			tmp_attribute_intmap.clear();
			//取string形属性
			
			if (att_element->FindAttribute("Sprite"))
			{
				std::string sprite = att_element->Attribute("Sprite");
				tmp_attribute_stringmap["Sprite"] = sprite;
			}
			if (att_element->FindAttribute("Runanimate"))
			{
				std::string runanimate = att_element->Attribute("Runanimate");
				tmp_attribute_stringmap["Runanimate"] = runanimate;
			}
			if (att_element->FindAttribute("Dieanimate"))
			{
				std::string dieanimate = att_element->Attribute("Dieanimate");
				tmp_attribute_stringmap["Dieanimate"] = dieanimate;
			}
			if (att_element->FindAttribute("BulletPic"))
			{
				std::string bulletpic = att_element->Attribute("BulletPic");
				tmp_attribute_stringmap["BulletPic"] = bulletpic;
			}
			//将一条记录加入map
			id_stringmap->insert(std::pair <int,std::map<std::string,std::string> >(id,tmp_attribute_stringmap));
			tmp_attribute_stringmap.clear();
			//取下一个节点
			att_element=att_element->NextSiblingElement();
		}
		//读取完毕释放文件
		if (!xmldocument)
		{
			CC_SAFE_DELETE(xmldocument);
		}
	}
}

//打开xml
bool BasicAttribute::openXMLFIle(std::string filename){

	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		log("xml open fail!");
		return false;
	}
	//删除旧文件
	if (!xmldocument)
	{
		CC_SAFE_DELETE(xmldocument);
	}
	xmldocument=new tinyxml2::XMLDocument();
	std::string file=FileUtils::getInstance()->fullPathForFilename(filename);
	log("xml file path:%s",file.c_str());
	Data pfiledata = FileUtils::getInstance()->getDataFromFile(file);
//	log("%s",pFileContent);
	xmldocument->Parse((char*)pfiledata.getBytes(),pfiledata.getSize());
	log("xml open success!");
	return true;
}

void BasicAttribute::setXmlFilename(std::string filename){
	xmlfilename = filename;
	openXMLFIle(xmlfilename);

}