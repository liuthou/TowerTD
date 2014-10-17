#include "GameScene.h"
#include "TowerSelect.h"
#include "MapLayer.h"
#include "StageLayer.h"
#include "UiLayer.h"
#include "SuperSkillLayer.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace cocostudio;

bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}
	//pre
    //add stage to gamescene
	auto stageLayer = StageLayer::create();
	stageLayer->setName("stage");
	this->addChild(stageLayer);
	//add uilayer to gamescene
	auto superlayer = SuperSkillLayer::create();
	this->addChild(superlayer);
	auto uiLayer = UiLayer::create();
	uiLayer->setName("ui");
	this->addChild(uiLayer);
	
	
	auto delay = DelayTime::create(0.2);
	auto call = CallFunc::create([&](){this->addChild(TowerSelect::create());});
	this->runAction(Sequence::create(delay,call,nullptr));
	return true;
}