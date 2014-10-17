#ifndef __CHOSEINFORMATION_H
#define __CHOSEINFORMATION_H
#include "cocos2d.h"
using namespace cocos2d;
class choseInformation
{
private:
	choseInformation(){
		fileNameXml = "over";
		imageName = "bbg_snow_castle.jpg";
	}
	choseInformation (const choseInformation &c){}
	choseInformation operator=(const choseInformation &c){
		return c;
	}
	static choseInformation *instence;
	std::string fileNameXml;
	std::string imageName;
public:
	static choseInformation *getInstence();
	void setFileNameXml(std::string name);
	std::string getFileNameXml();
	void setImageName(std::string name);
	std::string getImageName();
};
#endif