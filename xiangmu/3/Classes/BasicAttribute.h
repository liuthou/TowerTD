/**

* 类名：BasicAttribute

* 作者：陈川

* 日期：

* 作用 : 解析xml,将xml记录解析为map,并在子类中从map中读取属性
			如果要在xml文件中添加属性字段,需要在parseXML()与子类的getXXXAttribute
			中增加相应的解析与查找代码。

**/ 
#ifndef __BASICATTRIBUTE_H_
#define __BASICATTRIBUTE_H_
#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
USING_NS_CC;
using namespace tinyxml2;
class BasicAttribute{
public:
	//设置当前关卡需要解析的xml文件
	static void setXmlFilename(std::string xmlfilename);

	virtual void reset(){
		id_intmap->clear();
		id_stringmap->clear();
	}
protected:
	static bool openXMLFIle(std::string filename);
	//解析xml
	virtual void parseXML(std::string elementname);
	
protected:
	static std::string xmlfilename;
	static tinyxml2::XMLDocument *xmldocument;
	//整形变量相关
	std::map<std::string,int> tmp_attribute_intmap;
	//解析xml后,一个怪物id对应一个键值对
	std::map<int,std::map<std::string,int> > *id_intmap;
	//string变量相关
	std::map<std::string,std::string> tmp_attribute_stringmap;
	std::map<int,std::map<std::string,std::string> > *id_stringmap;

	BasicAttribute(){
		xmldocument=nullptr;
		id_intmap=new std::map<int,std::map<std::string,int> >();
		id_stringmap=new std::map<int,std::map<std::string,std::string> >();
	}
	virtual~BasicAttribute(){
		CC_SAFE_DELETE(id_intmap);
		CC_SAFE_DELETE(id_stringmap);
		CC_SAFE_DELETE(xmldocument);
	}
};
#endif