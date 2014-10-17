#ifndef __UIHEROLAYER_H
#define __UIHEROLAYER_H

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace cocos2d;

class uiHeroLayer:public Layer
{
private:
	void attributeValue();
	void gearShow();
public:	
	virtual bool init();
	CREATE_FUNC(uiHeroLayer);
	uiHeroLayer():_addAgility(0),_addAttack(0),_addDefence(0){}
private:
	int _addAgility;
	int _addAttack;
	double _addDefence;
	Widget * _uiherolayer;
};

#endif