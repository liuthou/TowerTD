#ifndef HPLOADINGBAR_H
#define HPLOADINGBAR_H

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Person.h"
#include "tinyxml2/tinyxml2.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class HpLoadingbar :public Layer
{
public:
	static HpLoadingbar * create(Person * persom);
	LoadingBar * loadingBarMp;
	void setMploadingBar(int i );
	LoadingBar * getMpLoadingBar();
protected:
	float hp;
	Person * person1;
	LoadingBar * loadingBar;
	LoadingBar * loadingBarHp;
	tinyxml2::XMLDocument doc;
	virtual bool init(Person * person);
	void update(float t);
	void onEnter();
private:
};
#endif