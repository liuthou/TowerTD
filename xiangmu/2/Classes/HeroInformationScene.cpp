
#include "HeroInformationScene.h"
#include "HeroInformationSceneBG.h"
#include "HeroInformationMenuLayer.h"

bool HeroInformationScene::init(){
	if (!Scene::create()) {
		return false;
	}
	// background layer
	auto bgLayer = HeroInformationSceneBG::create();
	this->addChild(bgLayer);

	//menu layer
	auto menuLayer = HeroInformationMenuLayer::create();
	this->addChild(menuLayer);



	return true;
}