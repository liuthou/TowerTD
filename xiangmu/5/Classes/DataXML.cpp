#include "DataXML.h"

int fileCopy(const char * srcFileName, const char * desFileName){
	//判断---如果可写目录下的文件已存在，则直接return 不再继续copy
	if (FileUtils::getInstance()->isFileExist(desFileName))
	{
		return 0;
	}
	Data date = FileUtils::getInstance()->getDataFromFile(srcFileName);
	//打开文件----wb表示以二进制方式写入
	FILE * fp = fopen(desFileName, "wb");
	//写文件----date.getBytes()返回数据块data的指针，
	// date.getSize()数据块中的元素个数，1表示写date.getSize()*1的量的数据
	fwrite(date.getBytes(), date.getSize(), 1, fp);
	//完成
	fflush(fp);
	//关闭文件
	fclose(fp);
	return 1;
}

DataXML * DataXML::instence = nullptr;

DataXML * DataXML::getInstence() {

	if (!instence)
	{
		instence = new DataXML();
	}

	//获得全路径
	std::string rfileName = FileUtils::getInstance()->fullPathForFilename("mydata.xml");
	//获得可写文件路径
	std::string dfileName = FileUtils::getInstance()->getWritablePath() + "mydata.xml";
	//进行xml文件的拷贝，在fileCopy（）函数中进行判断可写目录下是否存在xml文件
	fileCopy(rfileName.c_str(), dfileName.c_str());

	return instence;
}

int DataXML::getInitialValue(std::string name)  {

	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";
	if (name == "useablebloodbutton" || name == "plus50" || name == "multi2short" || name == "blood_drop")
	{
		return 1;
	}

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	tinyxml2::XMLElement * root1 = root->FirstChildElement(name.c_str());
	if (name == "hp" || name == "maxScore" || name == "sound")
	{
		return root1->IntAttribute(name.c_str());
	}else
	{
		return root1->IntAttribute("isOpen");
	}

}

ValueMap DataXML::getTask() {


	ValueMap taskMap;

	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	root1 = root->FirstChildElement("TASK");
	root2 = root1->FirstChildElement();

	while (root2->BoolAttribute("isFinish"))
	{
		root2 = root2->NextSiblingElement();
		if (root2 == nullptr)
		{
			return taskMap;
		}
	}

	root3 = root2->FirstChildElement();

	while (root3)
	{
		std::string taskName = root3->Attribute("name");
		int number = root3->IntAttribute("number");
		taskMap[taskName] = number;

		root3 = root3->NextSiblingElement();
	}
	

	return taskMap;
}

std::string DataXML::getPictureName(std::string conditionName) {
	
	std::string pictureName;

	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	root1 = root->FirstChildElement("TASK");
	root2 = root1->FirstChildElement();


	while(root2->BoolAttribute("isFinish"))
	{
		root2 = root2->NextSiblingElement();
	}

	root3 = root2->FirstChildElement();
	while(root3) {

		if (root3->Attribute("name") == conditionName)
		{
			pictureName = root3->Attribute("fileName");
			break;
		}

		root3 = root3->NextSiblingElement();
	}

	return pictureName;
}

ValueMap DataXML::getCurTool() {
	ValueMap toolMap;

	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	root1 = root->FirstChildElement();
	root2 = root1->FirstChildElement();


	while (root1)
	{
		std::string name = root1->Attribute("name");

		if (name == "tool" && !root1->IntAttribute("isOpen"))
		{
			toolMap[root1->Attribute("name")] = root1->Attribute("fileName");
			return toolMap;
		}
		root1 = root1->NextSiblingElement();

		if (root1 == nullptr)
		{
			break;
		}
	}
	return toolMap;
}

void DataXML::finishTask() {

	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	root1 = root->FirstChildElement("TASK");
	root2 = root1->FirstChildElement();


 	while (root2)
 	{
 		if (!root2->BoolAttribute("isFinish"))
 		{
 			root2->SetAttribute("isFinish","true");
			doc.SaveFile(filePath.c_str());
 			break;
		}else
		{
			root2 = root2->NextSiblingElement();
		}
 		
 	}
	
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * roott = doc.RootElement();
	auto tool = roott->FirstChildElement();
 	while(tool) {
		std::string name = tool->Attribute("name");
		int i = tool->IntAttribute("isOpen");
 		if (name == "tool" && tool->IntAttribute("isOpen") == 0)
 		{
 			tool->SetAttribute("isOpen",1);
			doc.SaveFile(filePath.c_str());
 			break;
 		}
		tool =tool->NextSiblingElement();
 	}
}

void DataXML::saveData(std::string name, int numValue) {

	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	root = doc.RootElement();
	if (name == "hp" || name == "maxScore" || name == "sound")
	{
		root1 = root->FirstChildElement();
		
		while(root1) {
			std::string nameXML = root1->Attribute("name");
			
			if (nameXML == name)
			{
				root1->SetAttribute(name.c_str(),numValue);
				doc.SaveFile(filePath.c_str());
				break;
			}
			root1 = root1->NextSiblingElement();
		}
		return;
	}

	doc.LoadFile(filePath.c_str());
	root = doc.RootElement();
	root1 = root->FirstChildElement("TASK");
	root2 = root1->FirstChildElement();


	while(root2->BoolAttribute("isFinish"))
	{
		root2 = root2->NextSiblingElement();
	}

	root3 = root2->FirstChildElement();
	while(root3) {

		if (root3->Attribute("name") == name)
		{
			root3->SetAttribute("curnumber",numValue);
			doc.SaveFile(filePath.c_str());
			break;
		}

		root3 = root3->NextSiblingElement();
	}

}

int DataXML::getCurNumber(std::string name) {

	int curNumber;
	std::string filePath = FileUtils::getInstance()->getWritablePath() + "mydata.xml";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	root1 = root->FirstChildElement("TASK");
	root2 = root1->FirstChildElement();


	while(root2->BoolAttribute("isFinish"))
	{
		root2 = root2->NextSiblingElement();
	}

	root3 = root2->FirstChildElement();
	while(root3) {

		if (root3->Attribute("name") == name)
		{
			curNumber = root3->IntAttribute("curnumber");
			break;
		}

		root3 = root3->NextSiblingElement();
	}

	return curNumber;
}
