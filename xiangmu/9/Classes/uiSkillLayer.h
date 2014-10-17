#ifndef  __UISKILLLAYER_H
#define  __UISKILLLAYER_H

#include "T_uiSkillLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class DataCacheSkill;

class uiSkillLayer :public Layer
{
private:
	ImageView * _imageView;
public:	
	virtual bool init();
	CREATE_FUNC(uiSkillLayer);
private:
	void spValueShow();
	void attackValueShow(DataCacheSkill * dataSkill, Text * skillLabel);
	void skillSp(int i, DataCacheSkill * dataSkill, Button *button);
	void addSkillSp(int i, DataCacheSkill * dataSkill, Button *button,  Text * skillLabel);
};

#endif