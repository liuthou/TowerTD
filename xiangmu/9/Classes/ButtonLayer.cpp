#include "ButtonLayer.h"
#include "uiRiskLayer.h"
#include "uiHeroLayer.h"
#include "uiSkillLayer.h"
#include "DelegetLayer.h"
#include "uiEquipLayer.h"
#include "AboutLayer.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
bool ButtonLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	vSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("UIbackground.jpg");
	bg->setPosition(Vec2(vSize.width / 2, vSize.height / 2));
	bg->setOpacity(200);
	addChild(bg, -1);
	auto delegetlayer = DelegetLayer::create();
	this->addChild(delegetlayer, 1);
	auto menuItem1 = MenuItemImage::create("IC1860.png", "IC1862.png", [=](Ref *sender)
	{
		auto riskLayer = uiRiskLayer::create();
		riskLayer->setPosition(Vec2(-600, 0));
		delegetlayer->removeAllChildrenWithCleanup(true);
		riskLayer->runAction(MoveTo::create(0.5, Vec2(0, 0)));
		delegetlayer->addChild(riskLayer);
        SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
	});
	auto menuItem2 = MenuItemImage::create("IC3322.png", "IC3320.png", [=](Ref *sender)
	{
		auto heroLayer = uiHeroLayer::create();
		heroLayer->setPosition(Vec2(-600, 0));
		delegetlayer->removeAllChildrenWithCleanup(true);
		heroLayer->runAction(MoveTo::create(0.5, Vec2(0, 0)));
		delegetlayer->addChild(heroLayer);
        SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
	});
	auto menuItem3 = MenuItemImage::create("IC1507.png", "IC1531.png", [=](Ref *sender)
	{
		auto skillLayer = uiSkillLayer::create();
		skillLayer->setPosition(Vec2(-600, 0));
		delegetlayer->removeAllChildrenWithCleanup(true);
		skillLayer->runAction(MoveTo::create(0.5, Vec2(0, 0)));
		delegetlayer->addChild(skillLayer);
        SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
	});
	auto menuItem4 = MenuItemImage::create("IC0046.png", "IC0045.png", [=](Ref *sender)
	{
		auto equipLayer = uiEquipLayer::create();
		equipLayer->setPosition(Vec2(-600, 0));
		delegetlayer->removeAllChildrenWithCleanup(true);
		equipLayer->runAction(MoveTo::create(0.5, Vec2(0, 0)));
		delegetlayer->addChild(equipLayer);
        SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
	});
	auto menuItem5 = MenuItemImage::create("about.png", "about_selected.png", [=](Ref *sender)
        {
                auto aboutLayer = AboutLayer::create();
                delegetlayer->addChild(aboutLayer,201);
            SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
        });
	auto menu = Menu::create(menuItem1, menuItem2, menuItem3, menuItem4, menuItem5, NULL);
	menu->alignItemsVerticallyWithPadding(60);
	menu->setPosition(Vec2(8 * vSize.width / 9, 3*vSize.height / 7));
	this->addChild(menu, 100);
	return true;
}


