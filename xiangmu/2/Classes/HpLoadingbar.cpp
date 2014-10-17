#include "Hploadingbar.h"
#include "SFRole.h"

HpLoadingbar * HpLoadingbar::create(Person * person)
{
	auto hploadingbar = new HpLoadingbar();
	if (hploadingbar&&hploadingbar->init(person))
	{
		hploadingbar->autorelease();
		return hploadingbar;
	}
	CC_SAFE_DELETE(hploadingbar);
	return nullptr;
}
bool HpLoadingbar::init(Person * person)
{
	if (!Layer::init())
	{
		return false;
	}
	auto fileName = FileUtils::getInstance()->getStringFromFile("Person.xml");
    doc.Parse(fileName.c_str()) ;
	hp = doc.RootElement()->FirstChildElement()->IntAttribute("HP");
	person1 = person;
	auto uiLayer = GUIReader::getInstance()->widgetFromJsonFile("LoadingBar_1/LoadingBar_1.ExportJson");
	loadingBarMp = (LoadingBar *)uiLayer->getChildByTag(7);
	loadingBarHp = (LoadingBar *)uiLayer->getChildByTag(5);
	loadingBarHp->setPercent(0);
	loadingBarMp->setPercent(0);
	this->addChild(uiLayer);
	this->scheduleUpdate();
	return true;
}
void HpLoadingbar::update(float t)
{
	
	loadingBarMp->setPercent(loadingBarMp->getPercent() + t * 3);
	auto sf = (SFRole*)person1;
	sf->setMp(loadingBarMp->getPercent());
	if ((hp - person1->getHp()) >hp)
	{
		__NotificationCenter::getInstance()->postNotification("t");
		loadingBarHp->setPercent(99);
		return;
	}
	loadingBarHp->setPercent(((hp - person1->getHp()) * 100 / hp));
	__NotificationCenter::getInstance()->postNotification("f");

}
void HpLoadingbar::onEnter()
{
	Layer::onEnter();

}
void HpLoadingbar::setMploadingBar(int i)
{
	loadingBarMp->setPercent(i);
}
LoadingBar * HpLoadingbar::getMpLoadingBar()
{
	return loadingBarMp;
}
