#include "GoldandGemLayer.h"
#include "BaseRewards.h"
#include "BaseGemstone.h"
#include "BaseGoldCoin.h"
#include "WhiteGemstone.h"
#include "TokensSprite.h"
#include "DenariusSprite.h"
#include "GoldCoinSprite.h"
#include "PlayGameScene.h"
#include "YellowGemstone.h"
#include "RedGemstone.h"
#include "PurpleGemstone.h"
#include "GreenGemstone.h"
#include "BackgroundLayer.h"
#include "ConfigUtil.h"
#include "time.h"
#include "TokenRect.h"
#include "JumpHelp.h"
bool GoldandGemLayer::init(){
	if (!Layer::init()){
		return false;
	}
	vSize = Director::getInstance()->getVisibleSize();

	m_id_x = 0;
	m_id_y = 0;
	return true;
}

void GoldandGemLayer::onEnter(){
	Layer::onEnter();
	//this->schedule(schedule_selector(GoldandGemLayer::monitorHeight));
	addMeters();
}

void GoldandGemLayer::addMeters(){
	m_height = JumpHelp::getBackgroundLayer()->getFinalLength();
	if (m_height > 900){
		appearCoin();
	}
	if (m_height > 2000){
		coinShape();
	}
}

void GoldandGemLayer::monitorHeight(float t){
	PlayGameScene * pgs = dynamic_cast<PlayGameScene *>(Director::getInstance()->getRunningScene());
	ulayer = pgs->getBackgroundLayer();
	m_height = ulayer->getFinalLength();
	log("%.2f",m_height);
}

void GoldandGemLayer::appearCoin(){
	if (m_height < 900){
		for (int i = 0;i < 3;i++){
			int r = rand() % 101;
			m_id_x =  rand() % 4 + 1;
			m_id_y =  rand() % 4 + 1;
			log("m_id_x = %d,m_id_y = %d",m_id_x,m_id_y);
			if (r < NITHFIVE && r > FIVE){
				this->addChild(TokensSprite::create(FILENAME6, m_id_x, m_id_y));
				}else if(r < FIVE){
					this->addChild(WhiteGemstone::create(FILENAME5, m_id_x, m_id_y));
					log("(gem = %d,gem = %d)", m_id_x, m_id_y);
				}
			}
		}

	if (m_height > 900 && m_height < 6000){
		for (int i = 0;i < 3;i++){
			m_id_x =  rand() % 4 + 1;
			m_id_y =  rand() % 4 + 1;
			int r = rand() % 101;
			if (r < ONEHUNDRED && r > TEN){
				this->addChild(DenariusSprite::create(FILENAME7, m_id_x, m_id_y));
				JUMP_LOG("(coin  = %d, coin = %d)",m_id_x,m_id_y);
			}else if(r < TEN){
				this->addChild(WhiteGemstone::create(FILENAME5, m_id_x, m_id_y));
				JUMP_LOG("(gem = %d,gem = %d)", m_id_x, m_id_y);
			}
		}	
	}

	if (m_height > 6000 && m_height < 50000){
		for (int i = 0; i < 3; i++){
			int r = rand() % 101;
			m_id_x =  rand() % 4 + 1;
			m_id_y =  rand() % 4 + 1;
			if (r < HALF && r > TEN){
				this->addChild(DenariusSprite::create(FILENAME7, m_id_x, m_id_y));
			}else if(r < ONEHUNDRED && r > HALF){
				this->addChild(GoldCoinSprite::create(FILENAME8, m_id_x, m_id_y));
			}else if(r < 10){
				this->addChild(RedGemstone::create("2.png", m_id_x, m_id_y));
			}	
		}
	}


	if (m_height > 50000){
		for (int i = 0; i < 3; i++){
			int r = rand() % 101;
			m_id_x =  rand() % 4 + 1;
			m_id_y =  rand() % 4 + 1;
		if (r < ONEHUNDRED && r > TEN){
				this->addChild(GoldCoinSprite::create(FILENAME8, m_id_x, m_id_y));
		}else if(r < TEN && r > FIVE){
				this->addChild(PurpleGemstone::create(FILENAME4, m_id_x, m_id_y));
		}else if (r < FIVE){
				this->addChild(GreenGemstone::create(FILENAME1, m_id_x, m_id_y));
			}
		}
   }
}

void GoldandGemLayer::coinShape(){
	int k = rand() % 5;
	log("%d",k);
	if (2 == k){
		int t = rand() % 101;
		if (t < 50){
			auto sp = TokenRect::create(FILENAME6);
            this->addChild(sp);
			auto pSize = sp->getContentSize();
			for (int i = vSize.width/3 - pSize.width + pSize.width/2;i < vSize.width * 2/3 - pSize.width + pSize.width/2;){
				for (int j =  vSize.height/3 - pSize.height + pSize.height/2; j < vSize.height * 2/3 - pSize.height + pSize.height/2;){
					auto sp = TokenRect::create(FILENAME6);
					sp->setPosition(i,j);
					this->addChild(sp);
					j += pSize.height;
				}
				i += pSize.width;
			}
		}

		if (t > 50 && t < 80){
			auto sp = TokenRect::create(FILENAME7);
            this->addChild(sp);
			auto pSize = sp->getContentSize();
			for (int i = vSize.width/3 - pSize.width + pSize.width/2;i < vSize.width * 2/3 - pSize.width + pSize.width/2;){
				for (int j =  vSize.height/3 - pSize.height + pSize.height/2; j < vSize.height * 2/3 - pSize.height + pSize.height/2;){
					auto sp = TokenRect::create(FILENAME7);
					sp->setPosition(i,j);
					this->addChild(sp);
					j += pSize.height;
				}
				i += pSize.width;
			}
		}

		if (t > 80 && t < 100){
			auto sp = TokenRect::create(FILENAME8);
            this->addChild(sp);
			auto pSize = sp->getContentSize();
			for (int i = vSize.width/3 - pSize.width + pSize.width/2;i < vSize.width * 2/3 - pSize.width + pSize.width/2;){
				for (int j =  vSize.height/3 - pSize.height + pSize.height/2; j < vSize.height * 2/3 - pSize.height + pSize.height/2;){
					auto sp = TokenRect::create(FILENAME8);
					sp->setPosition(i,j);
					this->addChild(sp);
					j += pSize.height;
				}
				i += pSize.width;
			}
		}
	}
	
}
