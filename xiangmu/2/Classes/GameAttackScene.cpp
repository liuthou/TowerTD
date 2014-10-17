#include "GameAttackScene.h"
#include "AttackLayer.h"
#include "MainRoleLayer.h"
#include "EnemyLayer.h"
#include "bondingBox.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SkillLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocostudio;
using namespace ui;
bool GameAttackScene::init(){
	if (!Scene::init()) {
		return false;
	}
	ArmatureDataManager::getInstance()->addArmatureFileInfo("EnemyFlyOne/EnemyFlyOne.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("dota/dota.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("EnemyWalkOne/EnemyWalkOne.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("dinosaurEnemy/dinosaurEnemy.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("cowEnemy/cowEnemy.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("snakeEnemy/snakeEnemy.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("OxEnemy/OxEnemy.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/sheep/sheep.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/skill/skill.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Nec/Nec.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("che/che.ExportJson");
	auto attackLayer = AttackLayer::create();
	attackLayer->setName("attackLayer");
	this->addChild(attackLayer);
	
	bondingBox *bond = bondingBox::create();
	this->addChild(bond);
	//mainRole Layer
	MainRoleLayer *mainRoleLayer = MainRoleLayer::create();
	this->addChild(mainRoleLayer);
	//Enemy Layer
	EnemyLayer *enemyLayer = EnemyLayer::create();
	enemyLayer->setName("enemyLayer");
	this->addChild(enemyLayer);
	//

	//
	SkillLayer *skillLayer = SkillLayer::create();
	this->addChild(skillLayer);
	return true;
}
Layer *GameAttackScene::getAttackLayer(){
	return this->getChildByName<Layer *>("attackLayer");
}
Layer *GameAttackScene::getEnemyLayer(){
	return this->getChildByName<Layer *>("enemyLayer");
}
void GameAttackScene::onEnter()
{
	Scene::onEnter();
	auto strFlie = FileUtils::getInstance()->fullPathForFilename("battle_bgm_arena.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(strFlie.c_str(), true);
}
