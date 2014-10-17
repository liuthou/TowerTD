#include "uiHeroLayer.h"
#include "DataCacheHero.h"
#include "DataGeares.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool uiHeroLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//获得UI界面
	_uiherolayer = GUIReader::getInstance()->widgetFromJsonFile("hero_1.json");
	_uiherolayer->setPosition(Vec2(0,0));
	this->addChild(_uiherolayer);	
	gearShow();
    attributeValue();
	return true;
}

void uiHeroLayer::attributeValue()
{
	//获得猪脚单例
	DataCacheHero * hero = DataCacheHero::getInstance();
    //获得可视图屏幕大小
	Size vSize = Director::getInstance()->getVisibleSize();
	//取得hp的值，并将其改变
	auto image = _uiherolayer->getChildByName("Image_9");
	auto hpValue = (Text *)image->getChildByName("_hp");
	auto hpString = StringUtils::format("%d",hero->getHpValue());
	hpValue->setText(hpString);
	//获得mp的值，并将其改变
	auto mpValue = (Text *)image->getChildByName("_mp");
	auto mpString = StringUtils::format("%d",hero->getMpValue());
	mpValue->setText(mpString);
	//获得attack的值，并将其改变
	auto attackValue = (Text *)image->getChildByName("_attack");
	auto attackString = StringUtils::format("%d",hero->getAttackValue() + _addAttack);
	attackValue->setText(attackString);
	//获得defense的值，并将其改变
	auto defenseValue = (Text *)image->getChildByName("_hujia");
	auto defenseString = StringUtils::format("%.2f",hero->getDefenseValue() + _addDefence);
	defenseValue->setText(defenseString);
	//获得duck的值，并将其改变
	auto agilityValue = (Text *)image->getChildByName("_duck");
	auto agilityString = StringUtils::format("%0.2f",hero->getAgilityValue() + _addAgility);
	agilityValue->setText(agilityString);
	////获得crit的值，并将其改变
	//auto critValue = (Text *)image->getChildByName("_crit");
	//auto critString = StringUtils::format("%.2f",12);
	//critValue->setText(critString);
	//获得exp的值，并将其改变
	auto expValue = (Text *)image->getChildByName("_exp");
	auto expString = StringUtils::format("%d",hero->getNowExpValue());
	expValue->setText(expString);
	//获得level的值，并将其改变
	auto levelValue = (Text *)image->getChildByName("_lerve");
	auto levelString = StringUtils::format("%d",hero->getLevelValue());
	levelValue->setText(levelString);
	//获得猪脚的Name的值，并将其改变
	auto heroName = (Text *)image->getChildByName("_hero");
	heroName->setText(hero->getName());
	auto introduceValue = (Text *)image->getChildByName("_neirong");
	introduceValue->setText(hero->getIntroduce());
}

void uiHeroLayer::gearShow()
{
	auto image = _uiherolayer->getChildByName("Image_9");
	//获得武器的图片框
	auto weaponImage = (ImageView *)image->getChildByName("hero_wepaon");
	//获取盔甲的图片框
	auto armourImage = (ImageView *)image->getChildByName("hero_armour");
	//获取鞋子的图片框
	auto shoeImage = (ImageView *)image->getChildByName("hero_shoe");
	//获得装备容器单例
	DataGeares * gear = DataGeares::getInstance();
	for(auto x = gear->getDataGeares().begin(); x != gear->getDataGeares().end(); x++)
	{
		if((*x)->getHeroAdorn() == YES)
		{
			if((*x)->getGearType() == WEAPON)
			{
				_addAttack = (*x)->getAttickValue();
				weaponImage->loadTexture((*x)->getPictureName());
			}
			if((*x)->getGearType() == ARMOUR)
			{
				_addDefence = (*x)->getDefenseValue();
				armourImage->loadTexture((*x)->getPictureName());
				log("%f",(*x)->getDefenseValue());
			}
			if((*x)->getGearType() == SHOE)
			{
				_addAgility = (*x)->getAglityValue();
				shoeImage->loadTexture((*x)->getPictureName());
			}
		}
	}
}