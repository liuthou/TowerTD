#ifndef __DATAXML__H
#define __DATAXML__H
#include "cocos2d.h"
#include <tinyxml2/tinyxml2.h>
USING_NS_CC;

//拷文件 将xml源文件拷到可写目录-------参数：源文件名，目的文件名
int fileCopy(const char * srcFileName, const char * desFileName);

class DataXML
{
public:
	static DataXML * getInstence();

	//获得初始数据
	int getInitialValue(std::string name);

	//得到任务
	ValueMap getTask();

	//得到所需图片名
	std::string getPictureName(std::string conditionName);
	
	//达到当前需要解锁的道具
	ValueMap getCurTool();

	//得到任务的完成情况，即当前数量
	int getCurNumber(std::string name);

	//完成任务，修改isfinish,并解锁道具
	void finishTask();

	//保存游戏数据
	void saveData(std::string name, int numValue);

private:
	DataXML(){}
	DataXML(const DataXML & dataXML){}
	DataXML operator=(const DataXML & dataXML){return dataXML;}

private:
	static DataXML * instence;
	tinyxml2::XMLElement * root;
	tinyxml2::XMLElement * root1;
	tinyxml2::XMLElement * root2;
	tinyxml2::XMLElement * root3;
};

#endif