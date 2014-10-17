#include "Enemy.h"
#include "PhysicsHelper.h"
#include "AssetManager.h"
#include "MainPlane.h"
#include "ScoreLayer.h"
#include "ResultScene.h"

Enemy::Enemy() {
	textures[0] = "cn";
	textures[1] = "usa";
	textures[2] = "rsa";
	textures[3] = "koran";
}

bool Enemy::init() {
	int i = rand() % 4;	
	auto texture = AssetManager::getInstance()->getTextureManager()->getEnemyTexture(textures[i]);
	if (!BaseAirObject::initWithTexture(texture)) 
	{
		return false;
	}
	this->setContentSize(texture->getContentSize());
	initPhysicsBody(i);
	return true;
}

void Enemy::initPhysicsBody(int index) {
	auto vertexes = PhysicsHelper::getInstance()->getPhysicsShapeByName(StringUtils::format("%s.plist", textures[index]).c_str());
	auto body = PhysicsBody::create();
	for (auto shapeVex : vertexes) {
		auto shape = PhysicsShapePolygon::create(shapeVex.data(), shapeVex.size());
		body->addShape(shape);
	}

	body->setGravityEnable(false);
	body->setDynamic(false);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);
}

void Enemy::effectWhileCollision(Ref *obj) {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	auto scoreLyr = (ScoreLayer *)obj;
	auto s = ResultScene::createScene(scoreLyr->getScore());
	auto scene = TransitionCrossFade::create(0.5f, s);
	Director::getInstance()->replaceScene(scene);
}

void Enemy::move() {
	auto mov = MoveBy::create(VSIZE.height / ENEMY_MOVE_SPEED, Vec2(0, - (VSIZE.height + this->getContentSize().height)));
	auto cal = CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create(mov, cal, NULL));
}