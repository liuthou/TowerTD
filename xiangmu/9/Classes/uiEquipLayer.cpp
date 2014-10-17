#include "uiEquipLayer.h"
#include "sqlite3.h"
#include "DataCacheHero.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool uiEquipLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile("EquipUi_2.json");
	this->addChild(uiLayer);
	image = (ImageView *)uiLayer->getChildByName("Image");
	auto but1 = (Button *)image->getChildByName("Button_weapon");
	auto but2 = (Button *)image->getChildByName("Button_clothes");
	auto but3 = (Button *)image->getChildByName("Button_shoes");

	scroll1 = (ScrollView *)uiLayer->getChildByName("ScrollView_equip1");
	scroll2 = (ScrollView *)uiLayer->getChildByName("ScrollView_equip2");
	scroll3 = (ScrollView *)uiLayer->getChildByName("ScrollView_equip3");
    scroll1->setVisible(true);
    scroll2->setVisible(false);
    scroll3->setVisible(false);
	but1->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
        SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
		scroll1->setVisible(true);
		scroll2->setVisible(false);
		scroll3->setVisible(false);
		}
	});
	but2->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
            SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
			scroll1->setVisible(false);
			scroll2->setVisible(true);
			scroll3->setVisible(false);
		}
	});
	but3->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
            SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
			scroll1->setVisible(false);
			scroll2->setVisible(false);
			scroll3->setVisible(true);
		}
	});
	_dataGeares = DataGeares::getInstance();
	weaponLayer();
	armourLayer();
	shoeLayer();
	spValueShow();
	return true;
}

void uiEquipLayer::spValueShow()
{
	DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
	auto label_sp = (Text *)image->getChildByName("Label_sp");
	auto sp = StringUtils::format("%d",dataCacheHero->getSpValue());
	label_sp->setText(sp);
}

void uiEquipLayer::weaponLayer()
{
	auto x = _dataGeares->getDataGeares().begin();
	for(int i = 1; i < 13 && x != _dataGeares->getDataGeares().end(); x++)
	{
		auto imageString = StringUtils::format("Image_%d", i);
		auto equipString = StringUtils::format("Image_equip%d", i);
		auto gradeString = StringUtils::format("Label_grade%d", i);
		auto nameString = StringUtils::format("Label_name%d", i);
		auto attackString = StringUtils::format("Label_attack%d", i);
		//Button_up
		auto checkBoxString = StringUtils::format("Button%d", i);
		auto upButtonString = StringUtils::format("Button_up%d", i);
		//武器滚动层
 		auto image1 = (ImageView *)scroll1->getChildByName(imageString);
 		auto Image_equip1 = (ImageView *)image1->getChildByName(equipString);
 		auto label_grade1 = (Text *)image1->getChildByName(gradeString);
 		auto label_name1 = (Text *)image1->getChildByName(nameString);
 		auto  label_attack1 = (Text *)image1->getChildByName(attackString);
		auto checkBox_1 = (Button *)image1->getChildByName(checkBoxString);
		auto checkBox_2 = (Button *)image1->getChildByName(upButtonString);
		while ((*x)->getHeroHave() != HAVE && (*x)->getGearType() != WEAPON)
		{
			x++;
		}
		if((*x)->getHeroHave() == HAVE && (*x)->getGearType() == WEAPON)
		{
			Image_equip1->loadTexture((*x)->getPictureName());//传图片
			label_name1->setText((*x)->getName());//名字
			weaponAttackShow((*x), label_attack1, label_grade1);
			 		//复选框
			checkBox_1->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
 				if (t == Widget::TouchEventType::ENDED)
 				{
                    SimpleAudioEngine::getInstance()->playEffect("select equip.mp3");
					for(auto y = _dataGeares->getDataGeares().begin(); y != _dataGeares->getDataGeares().end(); y++)
					{
						if((*y)->getHeroAdorn() == YES && (*y)->getGearType() == WEAPON)
						{
							(*y)->setHeroAdorn(NO);
						}
					}
					(*x)->setHeroAdorn(YES);
 				}
 		    });
			checkBox_2->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
 				if (t == Widget::TouchEventType::ENDED)
 				{
                    SimpleAudioEngine::getInstance()->playEffect("select equip.mp3");
					DataCacheHero * dataCacheHero = DataCacheHero :: getInstance();
					if(dataCacheHero->getSpValue() >= (*x)->getGearUserSp())
					{
						dataCacheHero->setSpValue(dataCacheHero->getSpValue() - (*x)->getGearUserSp());
						(*x)->setAttickValue((*x)->getAttickValue() * (1 + (*x)->getAdditionValue()));
						(*x)->setQuality((*x)->getQuality() + 1);
						weaponAttackShow((*x), label_attack1, label_grade1);
						spValueShow();
					}
 				}
 		    });
			i++;
		}
	}
}

void uiEquipLayer::weaponSp()
{

}

void uiEquipLayer::weaponAttackShow(DataCacheGear * dataCacheGear, Text * label_attack1,Text * label_grade1)
{
	auto grade = StringUtils::format("%d",dataCacheGear->getQuality());
	label_grade1->setText(grade);//品质
	auto attackValue = StringUtils::format("Attack %d", dataCacheGear->getAttickValue());
	label_attack1->setText(attackValue);//攻击力
}

void uiEquipLayer::armourLayer()
{
	auto x = _dataGeares->getDataGeares().begin();
	for(int i = 1; i < 13 && x != _dataGeares->getDataGeares().end();x++)
	{
		auto imageString = StringUtils::format("Image_%d", i);
		auto equipString = StringUtils::format("Image_equip%d", i);
		auto gradeString = StringUtils::format("Label_grade%d", i);
		auto nameString = StringUtils::format("Label_name%d", i);
		auto attackString = StringUtils::format("Label_attack%d", i);
		auto checkBoxString = StringUtils::format("Button%d", i);
		auto upButtonString = StringUtils::format("Button_up%d", i);
		//衣服滚动层
 		auto image1 = (ImageView *)scroll2->getChildByName(imageString);
 		auto Image_equip1 = (ImageView *)image1->getChildByName(equipString);
 		auto label_grade1 = (Text *)image1->getChildByName(gradeString);
 		auto label_name1 = (Text *)image1->getChildByName(nameString);
 		auto  label_attack1 = (Text *)image1->getChildByName(attackString);
		auto checkBox_1 = (Button *)image1->getChildByName(checkBoxString);
		auto checkBox_2 = (Button *)image1->getChildByName(upButtonString);
		while ((*x)->getHeroHave() != HAVE && (*x)->getGearType() != ARMOUR)
		{
			x++;
		}
		if((*x)->getHeroHave() == HAVE && (*x)->getGearType() == ARMOUR)
		{
			Image_equip1->loadTexture((*x)->getPictureName());//传图片
			label_name1->setText((*x)->getName());//名字
			armourDefenceShow((*x), label_attack1, label_grade1);
			//复选框
			checkBox_1->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
 				if (t == Widget::TouchEventType::ENDED)
 				{
                    SimpleAudioEngine::getInstance()->playEffect("select equip.mp3");
                     for(auto y = _dataGeares->getDataGeares().begin(); y != _dataGeares->getDataGeares().end(); y++)
					{
						if((*y)->getHeroAdorn() == YES && (*y)->getGearType() == ARMOUR)
						{
							(*y)->setHeroAdorn(NO);
						}
					}
					(*x)->setHeroAdorn(YES);
 				}
 		    });
			checkBox_2->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
 				if (t == Widget::TouchEventType::ENDED)
 				{
                    SimpleAudioEngine::getInstance()->playEffect("select equip.mp3");
					DataCacheHero * dataCacheHero = DataCacheHero :: getInstance();
					if(dataCacheHero->getSpValue() >= (*x)->getGearUserSp())
					{
						dataCacheHero->setSpValue(dataCacheHero->getSpValue() - (*x)->getGearUserSp());
						(*x)->setDefenseValue((*x)->getDefenseValue() * (1 + (*x)->getAdditionValue()));
						(*x)->setQuality((*x)->getQuality() + 1);
						armourDefenceShow((*x), label_attack1, label_grade1);
						spValueShow();
					}
 				}
 		    });
			i++;
		}
	}
}

void uiEquipLayer::armourSp()
{

}

void uiEquipLayer::armourDefenceShow(DataCacheGear * dataCacheGear, Text * label_attack1,Text * label_grade1)
{
	auto grade = StringUtils::format("%d",dataCacheGear->getQuality());
	label_grade1->setText(grade);//品质
	auto attackValue = StringUtils::format("Defense %.2f",dataCacheGear->getDefenseValue());
	label_attack1->setText(attackValue);//防御力
}

void uiEquipLayer::shoeLayer()
{
	auto x = _dataGeares->getDataGeares().begin();
	for(int i = 1; i < 13 && x != _dataGeares->getDataGeares().end();x++)
	{
		auto imageString = StringUtils::format("Image_%d", i);
		auto equipString = StringUtils::format("Image_equip%d", i);
		auto gradeString = StringUtils::format("Label_grade%d", i);
		auto nameString = StringUtils::format("Label_name%d", i);
		auto attackString = StringUtils::format("Label_attack%d", i);
		auto checkBoxString = StringUtils::format("Button%d", i);
		auto upButtonString = StringUtils::format("Button_up%d", i);
		//鞋子滚动层
 		auto image1 = (ImageView *)scroll3->getChildByName(imageString);
 		auto Image_equip1 = (ImageView *)image1->getChildByName(equipString);
 		auto label_grade1 = (Text *)image1->getChildByName(gradeString);
 		auto label_name1 = (Text *)image1->getChildByName(nameString);
 		auto  label_attack1 = (Text *)image1->getChildByName(attackString);
		auto checkBox_1 = (Button *)image1->getChildByName(checkBoxString);
		auto checkBox_2 = (Button *)image1->getChildByName(upButtonString);
		while ((*x)->getHeroHave() != HAVE && (*x)->getGearType() != SHOE)
		{
			x++;
		}
		if((*x)->getHeroHave() == HAVE && (*x)->getGearType() == SHOE)
		{
			Image_equip1->loadTexture((*x)->getPictureName());//传图片
			label_name1->setText((*x)->getName());//名字
			shoeDefenceShow(*x, label_attack1, label_grade1);
			//复选框
			checkBox_1->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
 				if (t == Widget::TouchEventType::ENDED)
 				{
                      SimpleAudioEngine::getInstance()->playEffect("select equip.mp3");
                      for(auto y = _dataGeares->getDataGeares().begin(); y != _dataGeares->getDataGeares().end(); y++)
					{
						if((*y)->getHeroAdorn() == YES && (*y)->getGearType() == SHOE)
						{
							(*y)->setHeroAdorn(NO);
						}
					}
					(*x)->setHeroAdorn(YES);
 				}
 		    });
			checkBox_2->addTouchEventListener([=](Ref * f, Widget::TouchEventType t){   
 				if (t == Widget::TouchEventType::ENDED)
 				{
                    SimpleAudioEngine::getInstance()->playEffect("select equip.mp3");
					DataCacheHero * dataCacheHero = DataCacheHero :: getInstance();
					if(dataCacheHero->getSpValue() >= (*x)->getGearUserSp())
					{
						dataCacheHero->setSpValue(dataCacheHero->getSpValue() - (*x)->getGearUserSp());
						(*x)->setAglityValue((*x)->getAglityValue() * (1 + (*x)->getAdditionValue()));
						(*x)->setQuality((*x)->getQuality() + 1);
						shoeDefenceShow((*x), label_attack1, label_grade1);
						spValueShow();
					}
 				}
 		    });
			i++;
		}
	}
}

void uiEquipLayer::shoeSp()
{

}

void uiEquipLayer::shoeDefenceShow(DataCacheGear * dataCacheGear, Text * label_attack1,Text * label_grade1)
{
	auto grade = StringUtils::format("%d",dataCacheGear->getQuality());
	label_grade1->setText(grade);//品质
	auto attackValue = StringUtils::format("Aglity %0.2f", dataCacheGear->getAglityValue());
	label_attack1->setText(attackValue);//敏捷
}

uiEquipLayer::~uiEquipLayer()
{
 

}