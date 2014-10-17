

#include "LevelScene.h"
#include "LevelLayer.h"
#include "ChangeAttackBGLayer.h"

bool LevelScene::init(){
	if (!Scene::init()) {
		return false;
	}
	//±³¾°
	auto backGround = ChangeAttackBGLayer::create();
	addChild(backGround);

	//´°¿Ú
	//    auto levelLayer = LevelLayer::create();
	//    addChild(levelLayer);


	return true;
}