
#ifndef __Dota_Legend__HeroInformationMenuLayer__
#define __Dota_Legend__HeroInformationMenuLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class HeroInformationMenuLayer : public Layer {
protected:
	//属性,图鉴,技能 开关
	void toggleButton(Ref * sender);

	//图鉴内容开关
	void fieldGuideInformati(Ref *sender);

	//返回菜单
	void Return(Ref * sender);

	//增加菜单背景
	void addMenu();

	//菜单背景
	Sprite * menuBG;

	//三个开关
	MenuItemToggle * characterToggle;
	MenuItemToggle * illustratedHhandbookToggle;
	MenuItemToggle * skillToggle;

	//三个层的加入函数
	void addCharacter();

	void addIllustratedHandbook();

	void addSkill();

	//三个弹出层
	//属性
	Sprite * character;

	//图鉴
	Menu * illustratedHhandbook;

	//技能
	Sprite * skill;


public:
	virtual bool init();
	CREATE_FUNC(HeroInformationMenuLayer);
};
#endif /* defined(__Dota_Legend__HeroInformationMenuLayer__) */
