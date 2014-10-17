#include "ScoreLayer.h"
#include "Hero.h"
#include "GameScene.h"
#include "HeroLayer.h"
#include "RoleAnimate.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

bool ScoreLayer::init(){
	if (!Layer::init()){
		return false;
	}

	Size vsize = Director::getInstance()->getVisibleSize();

	curScore = 0;
	maxScore = 0;

	this->scheduleUpdate();

	nowScore = Label::createWithSystemFont("0000","Arial",30);
	nowScore->setPosition(Vec2(vsize.width * 0.8,610));
	nowScore->setColor(Color3B(120,120,120));
	this->addChild(nowScore);
	__NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(ScoreLayer::addScore),"addscore",NULL);

	std::vector<std::string>fileNames;
	for (int i = 1;i <= 6;i++){
		std::string filename = StringUtils::format("LivesRenaining%d.png",i);
		fileNames.push_back(filename);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.2,-1);
	lives1 = Sprite::createWithSpriteFrameName("LivesRenaining1.png");
	lives1->setName("live1");
	lives1->setPosition(Vec2(1 * vsize.width * 0.05,610));
	lives1->setScale(2);
	this->addChild(lives1);
	lives1->runAction(ani);

	lives2 = Sprite::createWithSpriteFrameName("LivesRenaining1.png");
	lives2->setName("live2");
	lives2->setPosition(Vec2(2 * vsize.width * 0.05,610));
	lives2->setScale(2);
	this->addChild(lives2);
	lives2->runAction(ani);

	lives3 = Sprite::createWithSpriteFrameName("LivesRenaining1.png");
	lives3->setName("live3");
	lives3->setPosition(Vec2(3 * vsize.width * 0.05,610));
	lives3->setScale(2);
	this->addChild(lives3);
	lives3->runAction(ani);

	lives4 = Sprite::createWithSpriteFrameName("LivesRenaining1.png");
	lives4->setName("live4");
	lives4->setPosition(Vec2(4 * vsize.width * 0.05,610));
	lives4->setScale(2);
	this->addChild(lives4);
	lives4->runAction(ani);


    
    MenuItemImage *menuitem = MenuItemImage::create("set.png","set.png",[=](Ref *obj){
        
		Director::getInstance()->pause();
        cocos2d::ui::Widget *setMenu = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Set/GameOver_1.ExportJson");
        
        this->addChild(setMenu,900);
        
        auto image = (ImageView *)setMenu->getChildByName("Image_3");
        auto con = (Button *)image->getChildByName("continue");
        con->addTouchEventListener([=](Ref*,Widget::TouchEventType){
            setMenu->setVisible(false);
            Director::getInstance()->resume();
        });
       
		 //音乐
		bg_music = AllVectors::getInstance()->getBgmusic();
        auto _yinyue = (CheckBox *)image->getChildByName("bg_music");
		_yinyue->setSelectedState(bg_music);

		_yinyue->addEventListener([=](Ref* obj,CheckBox::EventType t){
			auto e = AllVectors::getInstance()->getBgmusic();
			//SimpleAudioEngine::getInstance()->playBackgroundMusic("DragonNest.mp3",!e);
			AllVectors::getInstance()->setBgmusic(!e);
		});

        //音效
		ef_music = AllVectors::getInstance()->getEfmusic();
        auto _yinxiao = (CheckBox *)image->getChildByName("yinxiao_music");
		_yinxiao->setSelectedState(ef_music);

        _yinxiao->addEventListener([=](Ref* obj,CheckBox::EventType t){
			auto e = AllVectors::getInstance()->getEfmusic();
			AllVectors::getInstance()->setEfmusic(!e);
        });
    });
    Menu *menu = Menu::create(menuitem,NULL);
    menu->setPosition(Vec2(910,610));
    this->addChild(menu,9);
    
	this->schedule(schedule_selector(ScoreLayer::addLivesAmount));

	return true;
}



void ScoreLayer::addScore(Ref * obj){
	BaseTool * tool = dynamic_cast<BaseTool *>(obj);
	if(tool != nullptr){
		curScore = curScore + tool->getM_score();
		nowScore->setString(StringUtils::format("%d",curScore));
	}else{
		curScore = curScore + 1000;
		nowScore->setString(StringUtils::format("%d",curScore));
	}

}
void ScoreLayer::addLivesAmount(float t){
	auto rscene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto herolayer = dynamic_cast<HeroLayer *>(rscene->getHeroLayer());
	auto hero = herolayer->getHero();
	if(hero->getM_hp() >= 400){
		lives4->setVisible(true);
	}else{
		lives4->setVisible(false);
		if(hero->getM_hp() >= 300){
			lives3->setVisible(true);
		}else{
			lives3->setVisible(false);
			if(hero->getM_hp() >= 200){
				lives2->setVisible(true);
			}else{
				lives2->setVisible(false);
				if(hero->getM_hp() >= 100){
					lives1->setVisible(true);
				}else{
					lives1->setVisible(false);
				}
			}
		}
	}
}

void ScoreLayer::update(float t){
	auto e = AllVectors::getInstance()->getBgmusic();
	if (e)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}