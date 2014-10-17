 //
//  EnemyLayer.cpp
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//
#include "EnemyLayer.h"
#include "EnemySprite.h"
#include "IceSprite.h"
#include "BinderRoleStone.h"
#include "ColoudSprite.h"
#include "BackgroundLayer.h"
#include "JumpHelp.h"
#include "LineSprite.h"
#define FIRSTOUTTIME 0
#define FIRSTOUTTOOLS 0.8
#define FIRSTTIME 0
#define FIRSTDIETOOLPERCENT 3
#define FIRSTNOTDIETOOLPERCENT 20
#define FIRSTLEVELT 20
#define ENDDIETOOLPERCENT 10
#define ENDNOTDIETOOLPERCENT 50
#define ENDOUTTOOLTIME 0.2
bool EnemyLayer::init(){
	if (!Layer::init()){
		return false;
	}
	vSize = Director::getInstance()->getVisibleSize();
	/*
	 *累计时间
	 */
	outTimeSum = 0;
	/*
	 *输出道具的时间
	 */
	outTools = 0.8;
	/*
	 *时间初值为0；
	 */
	t = 0;
	/*
	 *死亡道具出现的概率
	 */
	dieTool = 2;
	/*
	 *非死亡道具出现的概率
	 */
	notDieTool = 20;
	/*
	 *20秒一个级别，下个级别时间乘2
	 */
	levelt = 20;
	m_Toolsnumber = 0;
	return true;
}

void EnemyLayer::onEnter(){
	Layer::onEnter();
	this->schedule(schedule_selector(EnemyLayer::addTime),1);
	this->scheduleUpdate();
}
void EnemyLayer::addTime(float t){
	this->t++;
	//键入下一级别
	if (this->t > levelt){
		nextLevel();
	}
}
void EnemyLayer::nextLevel(){
	levelt *= 2;
	if (notDieTool < 50){
		notDieTool += 1;
	}
	if (dieTool < 15){
		dieTool++;
	}	
	if (outTools >= 0.2){
		outTools -= 0.1;
	}

}
void EnemyLayer::update(float t){
	outTimeSum += t;
	if (outTimeSum > outTools){
		go();
		outTimeSum = 0;
	}

}
void EnemyLayer::go(){
	if (m_Toolsnumber <= 5){
		int r = rand() % 101;
		if (r < dieTool){
			m_Toolsnumber++;
			int m_t = rand() % 2 + 1;
			if (1 == m_t){
				auto line = LineSprite::create(FILENAMEDOU);
				int i = rand() % 2 + 1;
				if (1 == i){
					line->setPosition(Vec2(vSize.width/4,vSize.height/2));
				}else{
					line->setPosition(Vec2(vSize.width * 3/4,vSize.height/2));
				}
				this->addChild(line);
			}else{
				BinderRoleStone * sp_stone = BinderRoleStone::create();
				sp_stone->setPosition(Vec2(rand()%625,960));
				this->addChild(sp_stone);
			}
		}

		else{
			r = rand() % 101; 
			if (r < notDieTool){
				m_Toolsnumber++;
				int m_t = rand() % 4 + 1;
				if (1 == m_t){
					for (int i = 1;i < 4; i++){
						auto ice = IceSprite::create(FILENAMEICE,i);
						ice->setPosition(Vec2(pSize.width/2,vSize.height*3/4));
						this->addChild(ice);
						log("%d",i);
					}
				}else if (2 == m_t){
					for (int i = 4;i < 7; i++){
						auto ice = IceSprite::create(FILENAMEICE,i);
						ice->setPosition(Vec2(vSize.width,vSize.height*3/4));
						this->addChild(ice);
						log("%d",i);
					}
				}else if(3 == m_t){
					auto poo = EnemySprite::create(FILENAMESHIT);
					pSize = poo->getContentSize();
					poo->setPosition(Vec2(vSize.width/2,vSize.height));
					this->addChild(poo);
				}else if(4 == m_t){
					auto coloud =ColoudSprite::create(FILENAMECLOUD,1);
					coloud->setPosition(Vec2(pSize.width/2,vSize.height));
					this->addChild(coloud);
				}
			}

		}
	}
	else{
		
		return;
	}
	
}

