#include "BackgroundLayer.h"
#include "MainScene.h"
bool BackgroundLayer::init(){
	if (!Layer::init()){
		return false;
	}
	


	return true;
}
void BackgroundLayer::onEnter(){
	Layer::onEnter();
	MainScene* scene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	int nowchapter = scene->getChapternum();
	std::string bgfilename = StringUtils::format("background%d.png",1);
	int tmpnum = nowchapter%3;
	//可以换3个背景(设计好烂啊)
	if (tmpnum==0)
	{
		std::string tmp_filename = StringUtils::format("background%d.png",tmpnum);
		if (FileUtils::getInstance()->isFileExist(tmp_filename))
		{
			bgfilename = tmp_filename;
		}
	}
	if (tmpnum==1)
	{
		std::string tmp_filename = StringUtils::format("background%d.png",tmpnum);
		if (FileUtils::getInstance()->isFileExist(tmp_filename))
		{
			bgfilename = tmp_filename;
		}
	}
	if (tmpnum==2)
	{
		std::string tmp_filename = StringUtils::format("background%d.png",tmpnum);
		if (FileUtils::getInstance()->isFileExist(tmp_filename))
		{
			bgfilename = tmp_filename;
		}
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create(bgfilename);
	bg->setPosition(origin.x+size.width/2,origin.y+size.height/2);
	this->addChild(bg);
}