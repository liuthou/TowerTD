#include "loading.h"
#include "tinyxml2/tinyxml2.h"
#include "GameMainScene.h"
#include "HeroMacro.h"
#include "T_GameMainScene.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
using namespace tinyxml2;

Scene* Loading::createScene(std::string xmlName){
	auto scene = Scene::create();
	auto layer = Loading::create(xmlName);
	scene->addChild(layer);
	return scene;
}

Loading * Loading::create(std::string xmlName){
	auto loa = new Loading();
	if (loa && loa->init(xmlName))
	{
		loa->autorelease();
		return loa;
	}
	CC_SAFE_DELETE(loa);
	return nullptr;
}
bool Loading::init(std::string xmlName){
	if (!Layer::init())
	{
		return false;
	}
	vSize = Director::getInstance()->getVisibleSize();
	_xmlName = xmlName;
    log("%s", _xmlName.c_str());
	_IsOk = false;
	_count = 0;
	loading = LabelTTF::create("loading....","Arial",20); 
	loading->setPosition(vSize.width - loading->getContentSize().width,loading->getContentSize().height);
	this->addChild(loading);
	addCat();
	addPlist();
	schedule(schedule_selector(Loading::update));
	return true;
}
void Loading::onEnter()
{
	Layer::onEnter();
	/*SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Att04.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("firework.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Gameover.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("ground.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("heroHurt.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("monsterHurt.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("skillOne.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Tornado.wav");*/
	//SimpleAudioEngine::getInstance()->preloadEffect("");
}
void Loading::addPlist(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(HERO_PICTURE_PLIST);	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SWORD_SKILL_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SHAN_DIAN_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bigSkill.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bigSkillButton.plist");
	auto xPlist = FileUtils::getInstance()->fullPathForFilename(_xmlName);
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(xPlist.c_str());
	tinyxml2::XMLElement *root = xmlDoc.RootElement();
	for (int i = 1;i < 4;i++)
	{
		auto path = StringUtils::format("Sprite%d",i);
        tinyxml2::XMLElement *sprite1 = root->FirstChildElement(path.c_str());
		std::string plist = sprite1->Attribute("plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist.c_str());
		_count++;
	}
}

void Loading::addCat(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loading.plist");//plist
	auto cat = Sprite::createWithSpriteFrameName("loading_01.png");
	cat->setPosition(vSize.width - cat->getContentSize().width,
		cat->getContentSize().height);
	this->addChild(cat);
	auto ani = Animation::create();
	for (int i = 1;i < 7;i++)
	{
		auto path = StringUtils::format("loading_0%d.png",i);
		SpriteFrame * spFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
		ani->addSpriteFrame(spFrame);
	}
	ani->setLoops(-1);
	ani->setDelayPerUnit(0.1f);
	auto a = Animate::create(ani);
	cat->runAction(a);
}

void Loading::update(float t){
	if (_count == 3)
	{
		Director::getInstance()->replaceScene(GameMainScene::create(_xmlName));
	}
}