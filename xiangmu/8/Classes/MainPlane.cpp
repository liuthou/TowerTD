#include "MainPlane.h"
#include "Prop.h"
#include "AssetManager.h"
#include "ScoreLayer.h"
bool MainPlane::init(){
	if (!Sprite::init()) {
		return false;
	}

	m_normalState = false;
	m_move = Animate::create(AssetManager::getInstance()->getAnimationManager()->getHeroAnimation("normal"));
	m_move->setTag(MAIN_PLANE_ANI_TAG);
	m_move->retain();
	this->runAction(m_move);

	registerMainPlaneFuncs();	// register functions of movement

	initPhysicsBody();

	return true;
}

//�ɻ������ƶ����״̬���������෴�ķ����ƶ�
void MainPlane::moveUp(){
	auto desirePosY = this->getPositionY() + (m_normalState?1:-1) * PLAYER_MOVE_STEP;
	if (desirePosY < VSIZE.height-PLAYER_SIZE.height/2 && 
		desirePosY > PLAYER_SIZE.height/2) {
			this->setPositionY(desirePosY);
	}
}

//�ɻ������ƶ����״̬���������෴�ķ����ƶ�
void MainPlane::moveLeft(){
	auto desirePosX = this->getPositionX() + (m_normalState?-1:1) * PLAYER_MOVE_STEP;
	if (desirePosX < VSIZE.width - PLAYER_SIZE.width/2 && 
		desirePosX > PLAYER_SIZE.width/2) {
			this->setPositionX(desirePosX);
	}
}

//�ɻ������ƶ����״̬���������෴�ķ����ƶ�
void MainPlane::moveDown(){
	auto desirePosY = this->getPositionY() + (m_normalState?-1:1) * PLAYER_MOVE_STEP;
	if (desirePosY < VSIZE.height-PLAYER_SIZE.height/2 && 
		desirePosY > PLAYER_SIZE.height/2) {
			this->setPositionY(desirePosY);
	}
}

//�ɻ������ƶ����״̬���������෴�ķ����ƶ�
void MainPlane::moveRight(){
	auto desirePosX = this->getPositionX() + (m_normalState?1:-1) * PLAYER_MOVE_STEP;
	if (desirePosX < VSIZE.width - PLAYER_SIZE.width/2 && 
		desirePosX > PLAYER_SIZE.width/2) {
			this->setPositionX(desirePosX);
	}
}

//����Ե���
void MainPlane::eatProp(Prop *prop){
	this->setNormalState(true);
	this->stopAllActions();
	this->runAction(m_move);
	m_delay = DelayTime::create(PROP_EFFETIVE_TIME);
	auto cf = CallFunc::create([=](){
		this->m_normalState = false;
	});
	this->runAction(Sequence::create(m_delay,cf,NULL));

	auto layer = (ScoreLayer *)Director::getInstance()->getRunningScene()->getChildByName(SCORELAYERNAME);
	layer->countTime(PROP_EFFETIVE_TIME);
}

//������������
void MainPlane::die(){
	
}

void MainPlane::registerMainPlaneFuncs(){
	// listen PLAYER_MOVE for handling
	auto lisDirection = EventListenerCustom::create(PLAYER_MOVE, [=](EventCustom* e){
		auto direction = (MovementDirection *)e->getUserData();
		if (direction != NULL) {
			switch (*direction)
			{
			case MovementDirection::UP :{
				this->moveUp();
			} break;
			case MovementDirection::DOWN :{
				this->moveDown();
			} break;
			case MovementDirection::LEFT :{
				this->moveLeft();
			} break;
			case MovementDirection::RIGHT :{
				this->moveRight();
			} break;
			default:
				break;
			}
			delete direction;
		}		
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lisDirection, this);
}

void MainPlane::onEnter() {
	Sprite::onEnter();
	m_originalPos = this->getPosition();
}

void MainPlane::reset() {
	this->setNormalState(false);
	this->setPosition(m_originalPos);
}

void MainPlane::initPhysicsBody() {
	auto body = PhysicsBody::createBox(PLAYER_SIZE);
	body->setContactTestBitmask(1);
	body->setGravityEnable(false);
	body->setDynamic(true);
	this->setPhysicsBody(body);
}
