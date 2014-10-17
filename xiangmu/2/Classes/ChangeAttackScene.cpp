
#include "ChangeAttackScene.h"
#include "ChangeAttackBGLayer.h"
#include "AttackMapLayer.h"

bool ChangeAttackScene::init(){
	if (!Scene::init()) {
		return false;
	}
	//1,±³¾°²ã
	auto changeAttackBG = ChangeAttackBGLayer::create();
	addChild(changeAttackBG);

	//2,µØÍ¼²ã
	auto attackMap = AttackMapLayer::create();
	addChild(attackMap);


	return true;
}