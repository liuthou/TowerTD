#include "GameLayer.h"
#include "BaseLayer.h"
#include "MainPlane.h"
#include "Enemy.h"
#include "Prop.h"
using namespace CocosDenshion;
bool GameLayer::init(){
	if (!BaseLayer::init())
	{
		return false;
	}
	initBg();
	initMainPlane();

	return true;
}

void GameLayer::update(float t){
	m_bg1->setPositionY(m_bg1->getPositionY() - BG_MOVE_SPEED * t);
	m_bg2->setPositionY(m_bg2->getPositionY() - BG_MOVE_SPEED * t);
	if (m_bg1->getPositionY() + m_bjHight <= 0)
	{
		m_bg1->setPositionY(m_bg2->getPositionY()+m_bjHight - 5);
	}
	if (m_bg2->getPositionY() + m_bjHight <= 0)
	{
		m_bg2->setPositionY(m_bg1->getPositionY()+m_bjHight - 5);
	}
}

//��ʼ��Ϸ
void GameLayer::start(){
	this->setVisible(true);
	startBg();
	startEnemy();
	startProp();
}

void GameLayer::stop(){

	this->setVisible(false);
	endEnemy();
	endMainPlane();
	endProp();
}

//������Ϸ���
void GameLayer::reset(){

	m_mainPlane->reset();
	auto children = this->getChildren();
	auto index = children.getIndex(m_mainPlane);
	for (int i=0; i<children.size(); i++) {
		if (index != i) {
			children.at(i)->removeFromParentAndCleanup(true);
		}
	}
}

//�������
void GameLayer::startProp(){
	this->schedule(schedule_selector(GameLayer::newProp), PROP_CREATE_FRIQUENCE_TIME, kRepeatForever, PROP_START_DELAY);
}

void GameLayer::startEnemy(){
	this->schedule(schedule_selector(GameLayer::newEnemy), ENEMY_CREATE_FRIQUENCE_TIME, kRepeatForever, ENEMY_START_DELAY);
}

void GameLayer::startMainPlane(){
	// �ظ�ԭʼλ��
	m_mainPlane->setPosition(m_mainPlane->getOriginalPos());	
	m_mainPlane->stopAllActions();
	m_mainPlane->runAction(m_mainPlane->getMoveAction()->clone());
}

void GameLayer::startBg(){
	this->scheduleUpdate();
}

void GameLayer::endEnemy() {
	this->unschedule(schedule_selector(GameLayer::newEnemy));
}

void GameLayer::endMainPlane() {
	
	m_mainPlane->stopActionByTag(MAIN_PLANE_ANI_TAG);
}

void GameLayer::endProp() {
	this->unschedule(schedule_selector(GameLayer::newProp));
}

void GameLayer::endBg() {
	this->unscheduleUpdate();
}

void GameLayer::initMainPlane() {
	m_mainPlane = MainPlane::create();
	m_mainPlane->setPosition(VSIZE.width/2, PLAYER_SIZE.height/2 + 100);
	m_mainPlane->setContentSize(PLAYER_SIZE);
	m_mainPlane->setTag(PLAYER_TAG);
	m_mainPlane->setScale(0.7);
	this->addChild(m_mainPlane);
}

void GameLayer::initBg() {
	//����1
	m_bg1 = Sprite::create("background1.png");
	m_bg1->setAnchorPoint(Vec2(0,0));

	//�õ�����1����ײ��ĸ߶ȡ�
	m_bjHight = m_bg1->getBoundingBox().size.height;
	m_bg1->setPosition(-10,0);
	this->addChild(m_bg1);

	//����2
	m_bg2 = Sprite::create("background2.png");
	m_bg2->setAnchorPoint(Vec2(0,0));
	m_bg2->setPosition(-10,m_bjHight-5);
	this->addChild(m_bg2);
}

void GameLayer::newEnemy(float t) {
	auto enemy = Enemy::create();
	Size ec_szie = enemy->getContentSize();
	enemy->setScale(0.7);
	enemy->setPosition(rand()%(int)(VSIZE.width - ec_szie.width) + ec_szie.width/2, VSIZE.height + ec_szie.height/2);
	this->addChild(enemy);

	enemy->setTag(ENEMY_TAG);
	enemy->move();
}

void GameLayer::newProp(float t) {
	auto prop = Prop::create();
	Vec2 pos;
	pos.x = rand()%(int)(VSIZE.width - PROP_SIZE.width) + PROP_SIZE.width/2;
	pos.y = VSIZE.height + PROP_SIZE.height/2;
	prop->setPosition(pos);
	prop->setScale(0.7);
	this->addChild(prop);
	auto move = MoveBy::create(CCRANDOM_0_1() + PROP_MOVE_TIME, Vec2(0, -(VSIZE.height + PROP_SIZE.height)));
	auto cal = CallFunc::create([=](){
		prop->removeFromParentAndCleanup(true);
	});
	prop->runAction(Sequence::create(move, cal, NULL));
	prop->setTag(PROP_TAG);
}
