#include "EnemyAILayer.h"
#include "AllVectors.h"
#include "GameScene.h"

bool EnemyAILayer::init(){
	if (!Layer::init()){
		return false;
	}



	return true;
}
void EnemyAILayer::onEnter(){
	Layer::onEnter();
	this->schedule(schedule_selector(EnemyAILayer::AIOne));
	this->schedule(schedule_selector(EnemyAILayer::AITwo));
	this->schedule(schedule_selector(EnemyAILayer::AIEight));
	this->schedule(schedule_selector(EnemyAILayer::AIThree));
	this->schedule(schedule_selector(EnemyAILayer::AIFive));
	this->schedule(schedule_selector(EnemyAILayer::AISix));
	this->schedule(schedule_selector(EnemyAILayer::AISeven));
	this->schedule(schedule_selector(EnemyAILayer::AIFour));
}

void EnemyAILayer::AIOne(float t){
	//��ȡС��ļ���
	auto ev =  AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");
	//�������е� С��
	for (auto it = ev.begin(); it != ev.end(); it++){
		if (abs((*it)->getPositionY() - hero->getPositionY()) < 20 && (*it)->getM_AI() == 1){
			if ((*it)->getPositionX() - hero->getPositionX() > 0){
				float nowSpeed = abs((*it)->getPositionX() - hero->getPositionX());
				if (nowSpeed > 200){
					(*it)->setM_speed(200);
				}else{
					(*it)->setM_speed(nowSpeed);
				}
				(*it)->m_direction = 3;
			}else{
				(*it)->setM_speed(abs((*it)->getPositionX() - hero->getPositionX()) / 2);
				(*it)->m_direction = 4;			
			}
		}
	}
}

void EnemyAILayer::AITwo(float t){
	//��ȡС��ļ���
	auto ev =  AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");

	//�������е� С��
	for (auto it = ev.begin(); it != ev.end(); it++){
		if (abs((*it)->getPositionY() - hero->getPositionY()) < 20 && abs((*it)->getPositionX() - hero->getPositionX()) < 300 && (*it)->getM_isSkillReady() == true && (*it)->getM_AI() == 2){
			if ((*it)->getPositionX() - hero->getPositionX() > 0){
				(*it)->m_direction = 3;
				(*it)->mySkill();
				(*it)->setM_isSkillReady(false);	
			}else{
				(*it)->m_direction = 4;
				(*it)->mySkill();
				(*it)->setM_isSkillReady(false);
			}
		}
	}
}

void EnemyAILayer::AIThree(float t){
	//��ȡС��ļ���
	auto ev =  AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");
	//�������е� С��
	for (auto it = ev.begin(); it != ev.end(); it++){
		if (abs((*it)->getPositionX() - hero->getPositionX()) < 20 && hero->getPositionY() - (*it)->getPositionY() > 0 && (*it)->isJump == false && (*it)->getM_AI() == 3){
			(*it)->isJump = true;
			(*it)->jump();
		}
		//��� ��ǰС��� X  - ���ǵ� X  < 200 
		if (abs((*it)->getPositionX() - hero->getPositionX()) < 250 && abs((*it)->getPositionY() - hero->getPositionY()) < 20 && (*it)->getM_AI() == 3){
			if ((*it)->getPositionX() - hero->getPositionX() > 0){//��� С���� ���� �Ҳ�
				(*it)->m_direction = 3;//����С��ķ�������
			}else{
				(*it)->m_direction = 4;
			}
		}
	}
}

void EnemyAILayer::AIFour(float t){
	auto ae = AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");

	for (auto it = ae.begin();it != ae.end();it++){
		if (abs((*it)->getPositionY() - hero->getPositionY()) < 30 && (*it)->getM_isSkilled() == false && (*it)->getM_AI() == 4){
			if((*it)->getPositionX() - hero->getPositionX() > 0){
				(*it)->m_direction = 3;
				(*it)->mySkill1();
				(*it)->setM_isSkilled(true);
			}else
			{
				(*it)->m_direction = 4;
				(*it)->mySkill1();
				(*it)->setM_isSkilled(true);
			}
		}
	}
}

void EnemyAILayer::AIFive(float t){

	auto ev =  AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");

	for (auto it = ev.begin(); it != ev.end(); it++){
		if (abs((*it)->getPositionX() - hero->getPositionX()) < 20 && hero->getPositionY() - (*it)->getPositionY() > 0 && (*it)->isJump == false && (*it)->getM_state() == 0 && (*it)->getM_AI() == 5 ){
			(*it)->isJump = true;
			(*it)->jump();
		}
	}
}

void EnemyAILayer::AISix(float t){
	auto ev =  AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");

	for (auto it = ev.begin(); it != ev.end(); it++){
		//如果 当前小鬼的 X  - 主角的 X  < 200 
		if (abs((*it)->getPositionX() - hero->getPositionX()) < 250 && abs((*it)->getPositionY() - hero->getPositionY()) < 20 && (*it)->getM_AI() == 6){
			if ((*it)->getPositionX() - hero->getPositionX() > 0){//如果 小鬼在 主角 右侧
				(*it)->m_direction = 3;//设置小鬼的方向向左
			}else{
				(*it)->m_direction = 4;
			}
			if (abs((*it)->getPositionX() - hero->getPositionX()) < 55 && (*it)->getM_isSkilled() == false){
				(*it)->setM_isSkilled(true);
				(*it)->mySkill2();
			}
		}
	}
}

void EnemyAILayer::AISeven(float t){
	auto ae = AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");

	for (auto it = ae.begin();it != ae.end();it++){
		if (abs((*it)->getPositionY() - hero->getPositionY()) < 30 && (*it)->getM_AI() == 7){
			if((*it)->getPositionX() - hero->getPositionX() > 0){
				(*it)->m_direction = 3;

			}else{
				(*it)->m_direction = 4;
			}
			if (abs((*it)->getPositionX() - hero->getPositionX()) < 55 && (*it)->getM_isSkilled() == false){
				(*it)->setM_isSkilled(true);
				(*it)->mySkill2();
			}
		}
	}
}

void EnemyAILayer::AIEight(float t){
	auto ev =  AllVectors::getInstance()->getEnemiesVector();
	auto runningScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto heroLayer = runningScene->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");

	//�������е� С��
	for (auto it = ev.begin(); it != ev.end(); it++){
		if (abs((*it)->getPositionY() - hero->getPositionY()) < 20 && abs((*it)->getPositionX() - hero->getPositionX()) < 55 && (*it)->getM_isSkilled() == false && (*it)->getM_AI() == 8){
			if ((*it)->getPositionX() - hero->getPositionX() > 0){
				(*it)->setM_isSkilled(true);
				(*it)->m_direction = 3;
				(*it)->mySkill2();		
			}else{
				(*it)->setM_isSkilled(true);
				(*it)->m_direction = 4;
				(*it)->mySkill2();
			}
		}
	}
}