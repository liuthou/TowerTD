#include "LogicLayer.h"
#include "StartScene.h"
#include "AllVectors.h"
#include "GameScene.h"
#include "BaseTool.h"
#include "GetInfoFromXML.h"
#include "EnemyLayer.h"
#include "MapLayer.h"
#include "GetInfoFromXML.h"
#include "GetEnemyInfoFromXML.h"
#include "BossThree.h"
#include "BossFour.h"
#include "BossTwo.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace ui;
using namespace cocostudio;


bool LogicLayer::init(){
	if (!Layer::init()){
		return false;
	}
	this->schedule(schedule_selector(LogicLayer::update),0.3,-1,2);
	return true;
}


void LogicLayer::turnToNextScene(float t){
	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto mapLayer = scene->getMapLayer();
	auto heroLayer = scene->getHeroLayer();
	auto enemyLayer = scene->getEnemyLayer();
	auto hero = heroLayer->getChildByName("hero");
	auto controllelayer = scene->getControlLayer();

	auto allEnemys = AllVectors::getInstance()->getEnemiesVector();
	auto allTools = AllVectors::getInstance()->getToolsVector();

	if (allEnemys.size() == 0 && allTools.size() == 0){

		auto controler = dynamic_cast<ControlLayer *>(scene->getControlLayer());

		auto i = UserDefault::getInstance()->getIntegerForKey("ID");
		
		this->unschedule(schedule_selector(LogicLayer::turnToNextScene));
		auto disapear = FadeOut::create(2);
		auto cf1 = CallFunc::create([=](){
			hero->setPosition(100,78);
			mapLayer->finishAmt();
		});
		auto seq1 = Sequence::create(disapear,cf1,NULL);
		hero->runAction(seq1);

		auto no = RotateBy::create(4,0);
		auto cf = CallFunc::create([=](){
			this->schedule(schedule_selector(LogicLayer::turnToNextScene),5);
			auto fOut = FadeIn::create(0.5);
			auto bAmt = RoleAnimate::getinstance()->createAmt("heroBorn_%02d.png",12,0.1,1);
			auto spa1 = Spawn::create(fOut,bAmt,NULL);
			hero->runAction(spa1);

			mapLayer->removeAllChildrenWithCleanup(true);
			
			GetInfoFromXML::getinstance()->clean();
			GetEnemyInfoFromXML::getinstance()->clean();

			auto level = UserDefault::getInstance()->getIntegerForKey("ID");

			int nextLevel = level+1;
			if (nextLevel == 16)
			{
				this->unschedule(schedule_selector(LogicLayer::turnToNextScene));
				auto scorelayer = dynamic_cast<ScoreLayer *>(scene->getScoreLayer());
				scorelayer->removeFromParentAndCleanup(true);
				mapLayer->removeAllChildrenWithCleanup(true);
				enemyLayer->removeAllChildrenWithCleanup(true);
				heroLayer->removeAllChildrenWithCleanup(true);
				controllelayer->removeAllChildrenWithCleanup(true);
				GetInfoFromXML::getinstance()->clean();
				GetEnemyInfoFromXML::getinstance()->clean();


				Widget *win = GUIReader::getInstance()->widgetFromJsonFile("Win_1/Win_1.ExportJson");
				this->addChild(win,900);

				auto image = (ImageView *)win->getChildByName("bg");
				auto back = (Button *)image->getChildByName("Button_4");
				back->addTouchEventListener([=](Ref* obj,Widget::TouchEventType t){
					StartScene *scen = StartScene::create();
					Director::getInstance()->replaceScene(scen);
					unscheduleAllSelectors();
					this->stopAllActions();
					UserDefault::getInstance()->setIntegerForKey("ID",1);
				});

				return;
			}

			UserDefault::getInstance()->setIntegerForKey("ID",nextLevel);

			mapLayer->scheduleOnce(schedule_selector(MapLayer::add),0.1);

			GetInfoFromXML::getinstance()->reloadXML();
			GetEnemyInfoFromXML::getinstance()->reloadXML();
			enemyLayer->scheduleOnce(schedule_selector(EnemyLayer::addEnemy),2);
			//
			
			//controler->setIsPost(true);


			enemyLayer->reload();
		

		});
		auto seq = Sequence::create(no,cf,NULL);
		this->runAction(seq);
	}

}


//英雄和道具的碰撞
void LogicLayer::heroPKtool(float t){
	GameScene * rScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	HeroLayer * layer = dynamic_cast<HeroLayer *>(rScene->getHeroLayer());
	auto ho = layer->getHero();
	auto toolVector = AllVectors::getInstance()->getToolsVector();
	
	for (auto tool = toolVector.begin();tool!= toolVector.end();tool++ ){
		if (ho->getBoundingBox().containsPoint((*tool)->getPosition())){
			auto e = AllVectors::getInstance()->getEfmusic();
			if (!e)
			{
				SimpleAudioEngine::getInstance()->playEffect("eattool.wav");
			}
			Label * lable = Label::create("Speed Up!","Verdana",20);
			lable->setPosition((*tool)->getPositionX(),(*tool)->getPositionY() + 50);
			this->addChild(lable);
			if ((*tool)->getM_type() == ADDSPEED){
				if (ho->getM_state() != 2){
					ho->setM_state(2);
					lable->setString("Speed Up !");
				}
			}else if ((*tool)->getM_type() == ADDBLOOD){
				if (ho->getM_hp() <= 300){
					ho->setM_hp(ho->getM_hp() + 100);
					lable->setString("1UP !");
				}
			}else if ((*tool)->getM_type() == ADDRANGE){
				if (ho->getM_isRangeUp() == false){
					ho->setM_isRangeUp(true);
					lable->setString("Range Up !");
				}
			}else if ((*tool)->getM_type() == ADDATTACK){
				if (ho->getM_isFireUp() == false){
					ho->setM_isFireUp(true);
					lable->setString("Fire Up !");
				}
			}else if ((*tool)->getM_type() == ADDSCORE){
				lable->setString(StringUtils::format("%d",(*tool)->getM_score()));
				__NotificationCenter::getInstance()->postNotification("addscore",(*tool));
			}else{
				lable->setString(StringUtils::format("%d",(*tool)->getM_score()));
				__NotificationCenter::getInstance()->postNotification("addscore",(*tool));
			}
			(*tool)->remove();
			auto tMove = MoveBy::create(1,Vec2(0,30));
			auto cf = CallFunc::create([=](){lable->removeFromParentAndCleanup(true);});
			auto sequ = Sequence::create(tMove,cf,NULL);
			lable->runAction(sequ);
		}	
	}
}



//
void LogicLayer::heroBulletPKenemy(float t){
	//
	auto heroBulletVector = AllVectors::getInstance()->getHeroBulletsVector();
	auto enemyVector = AllVectors::getInstance()->getEnemiesVector();
	
	for (auto herobullet = heroBulletVector.begin();herobullet!= heroBulletVector.end();herobullet++ ){
		for (auto enemy = enemyVector.begin();enemy!=enemyVector.end();enemy++){
			if ((*herobullet)->getBoundingBox().intersectsRect((*enemy)->getBoundingBox())){	
				(*enemy)->bulletHit();
				(*herobullet)->die();
				break;
			}
		}
	}

	deleteAllObject();

}

void LogicLayer::update(float t){
	auto all = AllVectors::getInstance()->getEnemiesVector();
	auto tools = AllVectors::getInstance()->getToolsVector();
	if (all.size() == 0 && tools.size()== 0)
	{
		auto rscene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
		auto controllayer = dynamic_cast<ControlLayer*>(rscene->getControlLayer());
		controllayer->setIsPost(false);
		
		auto  cf = CCCallFunc::create([=](){
			controllayer->setIsPost(true);
		});

		this->runAction(Sequence::create(DelayTime::create(4),cf,NULL));
	}
}

void LogicLayer::deleteAllObject(){
	AllVectors::getInstance()->deleteEnemy();
	AllVectors::getInstance()->deleteHeroBullet();
	AllVectors::getInstance()->deleteEnemyBullet();
}

void LogicLayer::heroPKenemyBullets(float t){
	//获取主角
	auto runScene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	//获取主角层
	auto heroLayer = dynamic_cast<HeroLayer *>(runScene->getChildByName("herolayer"));
	//h获取主角
	auto hero = dynamic_cast<Hero *>(heroLayer->getChildByName("hero"));

	//获取所有的 敌人的子弹
	auto allEnemyBullets = AllVectors::getInstance()->getEnemyBulletsVector();
	for (auto enemybullet = allEnemyBullets.begin(); enemybullet!=allEnemyBullets.end(); enemybullet++) {
		if ((*enemybullet)->getBoundingBox().intersectsRect(hero->getBoundingBox())) {
			(*enemybullet)->die();
			hero->hurt();
		}
	}


}

//enemy Bullets  PK  hero Bullets
void LogicLayer::heroBulletsPKenemysBullets(float t){
	//获取所有的 敌人的子弹
	auto allEnemyBullets = AllVectors::getInstance()->getEnemyBulletsVector();
	//获取所有的英雄的子弹
	auto allHeroBullets = AllVectors::getInstance()->getHeroBulletsVector();

	for (auto enemybullet = allEnemyBullets.begin();enemybullet!=allEnemyBullets.end();enemybullet++){
		for (auto herobullet = allHeroBullets.begin();herobullet!=allHeroBullets.end();herobullet++){
			if ((*enemybullet)->getBoundingBox().intersectsRect((*herobullet)->getBoundingBox())){
				(*herobullet)->die();
				(*enemybullet)->die();
				break;
			}
		}
	}

	deleteAllObject();

}


void LogicLayer::onEnter(){
	Layer::onEnter();


	

	schedule(schedule_selector(LogicLayer::heroBulletPKenemy));
	schedule(schedule_selector(LogicLayer::heroPKtool));
	schedule(schedule_selector(LogicLayer::turnToNextScene),6);
	schedule(schedule_selector(LogicLayer::heroBulletsPKenemysBullets));
	schedule(schedule_selector(LogicLayer::heroPKenemyBullets));

	auto rscene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	//auto enemylayer = rscene->getEnemyLayer();
	auto herolayer = dynamic_cast<HeroLayer *>(rscene->getHeroLayer());
	auto hero = herolayer->getHero();

	auto contanctListen = EventListenerPhysicsContact::create();
	contanctListen->onContactBegin = [=](PhysicsContact & contanct){
		auto bodyA = (Sprite*)(contanct.getShapeA()->getBody()->getNode());//??Ω∏??≈????≤∏’??????????‘”??????Ω??????÷??A
		auto bodyB = (Sprite*)(contanct.getShapeB()->getBody()->getNode());//??Ω∏??????≈????≤∏’??????‘”??Ω??????÷??B

		int tagA = bodyA->getTag();
		int tagB = bodyB->getTag();
		if(tagA == 2000){
			auto hero = (Hero*)bodyA;
			hero->hurt();
		}
		if(tagB == 2000){
			auto hero = (Hero*)bodyB;
			hero->hurt();
		}
		if(tagA == 1000 && (tagB == 1002 || tagB == 1003 || tagB == 1004)){
			bodyB->getPhysicsBody()->setRotationEnable(true);
			bodyB->getPhysicsBody()->getShape(0)->setRestitution(true);
			BaseEnemy * enemy = (BaseEnemy *)bodyB;
			enemy->m_subscructStateTime = 10;
			//std::vector<std::string>fileNames;
			/*for (int i = 1;i <= 6;i++){
				std::string fileName = StringUtils::format("enemyExpoode_0%d.png",i);
				fileNames.push_back(fileName);
			}*/
			//auto dieAni = RoleAnimate::getinstance()->createAnimate(fileNames,0.07,1);
			auto cf = CCCallFunc::create([=](){
				BaseTool *base = BaseTool::create(bodyB->getPosition());
				this->addChild(base);
				enemy->die();
				//bodyB->removeFromParentAndCleanup(true);
			}); 
			/*auto cf1 = CCCallFunc::create([=](){
				enemy->setIsDie(true);
			});*/
			bodyB->runAction(cf);
			//AllVectors::getInstance()->deleteEnemy();
			if(hero->getM_RollDirection() == 1){
				bodyA->getPhysicsBody()->setVelocity(Vec2(1800,0));
			}else{
				bodyA->getPhysicsBody()->setVelocity(Vec2(-1800,0));
			}
		}
		if(tagB == 1000 && (tagA == 1002 || tagA == 1003 || tagA == 1004)){
			bodyA->getPhysicsBody()->setRotationEnable(true);
			bodyA->getPhysicsBody()->getShape(0)->setRestitution(1);
			BaseEnemy * enemy = (BaseEnemy *)bodyA;
			enemy->m_subscructStateTime = 10;
			
			auto cf = CCCallFunc::create([=](){
				BaseTool *base = BaseTool::create(bodyA->getPosition());
				this->addChild(base);
				enemy->die();
			}); 
			bodyA->runAction(cf);
			if(hero->getM_RollDirection() == 1){
				bodyB->getPhysicsBody()->setVelocity(Vec2(1800,0));
			}else{
				bodyB->getPhysicsBody()->setVelocity(Vec2(-1800,0));
			}
		}
		if(tagA == 1000 && tagB == 2003){
			auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
			auto enemylayer = dynamic_cast<EnemyLayer *>(scene->getEnemyLayer());
			enemylayer->setRollTime(3);

		}
		if(tagB == 1000 && tagA == 2003){
			auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
			auto enemylayer = dynamic_cast<EnemyLayer *>(scene->getEnemyLayer());
			enemylayer->setRollTime(3);
		}
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contanctListen,this);
}