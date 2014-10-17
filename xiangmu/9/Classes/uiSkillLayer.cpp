#include "uiSkillLayer.h"
#include "DataCacheHero.h"
#include "Skilles.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool uiSkillLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//技能数据容器
	Skilles * skilles = Skilles::getInstance();
	//技能的数据显示
	Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile(EXPORTJSON);
	_imageView = (ImageView *)uiLayer->getChildByName("Image_18");
	this->addChild(uiLayer);
	auto scrollview = (ScrollView *)uiLayer->getChildByName(CHILDNAME);
	int i = 1;
	for(auto x = skilles->getSkilles().begin(); x != skilles->getSkilles().end(); x++, i++)
	{
		auto skillPictureName = StringUtils::format(IMAGE_, i);
		
		auto skillButton = StringUtils::format("Button_%d", i);
		auto skillImage = (ImageView *)scrollview->getChildByName(skillPictureName);
		auto skillAttack = StringUtils::format(SKILL, i);
		auto skillLabel = (Text *)skillImage->getChildByName(skillAttack);
		attackValueShow(*x, skillLabel);
	   	Button * button = (Button *)skillImage->getChildByName(skillButton);
		button->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
			if (t == Widget::TouchEventType::ENDED)
 			{
               SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
			   addSkillSp(i, *x, button, skillLabel);
			}
		});
		skillSp(i, *x, button);
	}    
	spValueShow();
	return true;
}

void uiSkillLayer::addSkillSp(int i, DataCacheSkill * dataSkill, Button *button,  Text * skillLabel)
{
	DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
	if(dataCacheHero->getSpValue() >= dataSkill->getSkillUserSp())
	{
		dataSkill->setAttickValue(dataSkill->getAttickValue() * (1 + dataSkill->getSkillAddition()));
        dataSkill->setConsumeMp(dataSkill->getConsumeMp() * (1 + dataSkill->getSkillAddition()));
		dataCacheHero->setSpValue(dataCacheHero->getSpValue() - dataSkill->getSkillUserSp());
		dataSkill->setSkillUserSp(dataSkill->getSkillUserSp() + 1);
		skillSp(i, dataSkill,button);
		attackValueShow(dataSkill, skillLabel);
		spValueShow();
	}
}

void uiSkillLayer::skillSp(int i, DataCacheSkill * dataSkill, Button *button)
{
	auto skillButton = StringUtils::format("Label_%d", i);
	auto spText = (Text *)button->getChildByName(skillButton);
	auto userSpString = StringUtils::format("%d", dataSkill->getSkillUserSp());
	spText->setText(userSpString);
}

void uiSkillLayer::spValueShow()
{
	DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
	auto spValue = (Text *)_imageView->getChildByName("Label_sp");
	auto sp = StringUtils::format("%d",dataCacheHero->getSpValue());
	spValue->setText(sp);
}

void uiSkillLayer::attackValueShow(DataCacheSkill * dataSkill,  Text * skillLabel)
{
	auto skillAttackValue = StringUtils::format("%d",dataSkill->getAttickValue());
	skillLabel->setString(skillAttackValue);
}