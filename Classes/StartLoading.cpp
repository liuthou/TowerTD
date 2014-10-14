#include "StartLoading.h"
#include "LoadingLayer.h"
#include "GameManager.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace ui;
using namespace cocostudio;
std::string plistRes[] ={
	"SkillThunders.plist",
	"otherskill.plist",
	"hurt.plist",
	"superskills.plist",
	"towerup.plist",
	""
} ;
std::string armatureRes[] = {
	"Project Animation/Project Animation.ExportJson",
	""
};
std::string audioRes[] = {
	"Music/btnOver.mp3",
	"Music/attack11.mp3",
	"Music/attack21.mp3",
	"Music/attack31.mp3",
	"Music/die1.mp3",
	"Music/die2.mp3",
	"Music/die3.mp3",
	"Music/die4.mp3",
	"Music/closeDoor.mp3",
	"Music/explode21.mp3",
	"Music/dengerious.mp3",
	"Music/dengerious.mp3",
	"Music/OM_ATK.mp3",
	"Music/MED_ATK.mp3",
	"Music/LINA_ATK3.mp3",
	"Music/wind.mp3",
	"musics/getgold.wav",
	""
};
Scene *StartLoading::createScene()
{
	auto scene = Scene::create();
	auto layer = StartLoading::create();
	scene->addChild(layer);
	return scene;
}
bool StartLoading::init(){
	if(!Layer::init()){
		return false;
	}
	addSprite();
	armCount = 0;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/battle1.mp3");
	UserDefault::getInstance()->setBoolForKey("tower_1",true);
	for (int count = 0;audioRes[count] != "";count++)
	{
		SimpleAudioEngine::getInstance()->preloadEffect(audioRes[count].c_str());
	}
	for (int count = 0;plistRes[count] != "";count++)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistRes[count]);
	}
	for (;armatureRes[armCount] != "";armCount++)
	{
		ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(armatureRes[armCount],this,schedule_selector(StartLoading::loadingArm));
	}
	
	return true;
}
void StartLoading::addSprite()
{
	auto loading = Sprite::create("startloading.png");
	this->addChild(loading);
	loading->setPosition(Vec2(640,400));
	loading->setScale(1.5);
	/*auto loadingBar = Sprite::create("loading_Base_chs-hd.png");
	this->addChild(loadingBar);*/
}
void StartLoading::loadingArm(float t)
{   
	
	if (armatureRes[armCount] == "")
	{
		
		Director::getInstance()->replaceScene(StartScene::createScene());	
		//Director::getInstance()->replaceScene(Scene::create());
	}
	armCount++;
}