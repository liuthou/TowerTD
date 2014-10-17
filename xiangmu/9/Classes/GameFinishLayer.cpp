#include "GameFinishLayer.h"
#include "DataCacheHero.h"
#include "StartScene.h"
#include "GameMainScene.h"
#include "HeroLayer.h"
#include "HeroBase.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool GameFinishLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	//Ω´÷ÌΩ≈ ˝æ›–¥»ÎµΩ ˝æ›ª∫¥Ê÷–
	auto vSize = Director::getInstance()->getVisibleSize();
	Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile("Finish_1.json");
	uiLayer->setPosition(Vec2(0, vSize.height));
	auto move = MoveBy::create(0.8, Vec2(0, -vSize.height));
	auto jump = JumpBy::create(0.4, Vec2(0, 0), vSize.height/16, 2);
	auto layerRun = Sequence::create(move, jump, NULL);
	this->addChild(uiLayer);
	//’Ω∂∑ §¿˚Õº∆¨
	auto imageWin= uiLayer->getChildByName("Image_5");
	auto bink = Blink::create(40,50);
	this->runAction(layerRun);
	imageWin->runAction(bink);
	//∑µªÿ∞¥≈•
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//暂停播放
	SimpleAudioEngine::getInstance()->playEffect("firework.wav");
	auto buttonBack = (Button*)uiLayer->getChildByName("Button_3");
	buttonBack->addTouchEventListener([=](Ref * sender, Widget::TouchEventType touch)
	{
		if (touch == Widget::TouchEventType::ENDED)
		{
			auto move2 = MoveBy::create(0.1, Vec2(0, -vSize.height / 16));
			auto move3 = MoveBy::create(0.7, Vec2(0, vSize.height + vSize.height / 16));
			this->runAction(Sequence::create(move2, move3, NULL));
			auto scene = StartScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
	//÷ÿÕÊ∞¥≈•
	auto buttonRestart = (Button *)uiLayer->getChildByName("Button_2");
	buttonRestart->addTouchEventListener([=](Ref * sender, Widget::TouchEventType touch)
	{
		if (touch == Widget::TouchEventType::ENDED)
		{
			auto move2 = MoveBy::create(0.1, Vec2(0, -vSize.height / 16));
			auto move3 = MoveBy::create(0.7, Vec2(0, vSize.height + vSize.height / 16));
			this->runAction(Sequence::create(move2, move3, NULL));
			auto scene = StartScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
	GameMainScene * gameScene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	HeroLayer * heroLayer = dynamic_cast<HeroLayer *>(gameScene->getHeroLayer());
	_heroBase = dynamic_cast<HeroBase *>(heroLayer->getChildByTag(100));
	//∑÷ ˝
	auto labelMark = (Text *)uiLayer->getChildByName("Label_11");
	string expString = StringUtils::format("%d", _heroBase->getTakeExpValue());
	labelMark->setText(expString);
	//∆¿∑÷
	auto imageGrade = uiLayer->getChildByName("Image_6");
	heroWriteInDataCache();
	return true;
}

void GameFinishLayer::heroWriteInDataCache()
{
	DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
	dataCacheHero->setAgilityValue(_heroBase->getAgilityValue());
	dataCacheHero->setAttackValue(_heroBase->getAttackBaseValue());
	dataCacheHero->setDefenseValue(_heroBase->getDefenseValue());
	dataCacheHero->setHpValue(_heroBase->getAllHp());
	dataCacheHero->setMpValue(_heroBase->getAllMp());
	dataCacheHero->setLevelValue(_heroBase->getLevelValue());
	dataCacheHero->setExpValue(_heroBase->getExpValue());
	dataCacheHero->setNowExpValue(_heroBase->getNowExpValue());
	dataCacheHero->setNeedExpValue(_heroBase->getNeedExpValue());
	dataCacheHero->setSpValue(_heroBase->getSpValue());
}