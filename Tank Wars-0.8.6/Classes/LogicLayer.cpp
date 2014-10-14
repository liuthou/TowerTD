#include "LogicLayer.h"
#include "MapLayer.h"
#include "GameScene.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "GameOverLayer.h"
bool LogicLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
   
	//坦克HP
	this->scheduleUpdate();
	//暂停按键
	 Label *l =Label::createWithBMFont("fonts/futura-48.fnt","Pause/Resume");
	 l->setPosition(Vec2(850,610));
	 l->setScale(0.2f);
	auto sp1 =Sprite::create("stop1.png");
	auto sp2 =Sprite::create("stop2.png");
	auto item =MenuItemSprite::create(sp1,sp2,[=](Ref *){
		if(Director::getInstance()->isPaused())
		{
        Director::getInstance()->resume();
        }
		else
		{
			Director::getInstance()->pause();
		}
	});
	auto menu =Menu::create(item,NULL);
	menu->setPosition(Vec2(610,400));
	menu->setScale(0.5f);
	this->addChild(menu);
	this->addChild(l);
	return true;
}
void LogicLayer::TankTestBound()
{  //坦克间碰撞
	auto scene =dynamic_cast<GameScene *> (Director::getInstance()->getRunningScene());
	auto tank = (BaseTank*)scene->getTanklayer()->getChildByName("tank");
	if (tank == nullptr)
	{
		return;
	}//判定Tank是否为空

	Vector<BaseTank *> vc = EnemyManager::getInstance()->getEnemyManger();
	for (auto iter = vc.begin();iter!=vc.end();iter++)
	{
		auto enemy = *iter;
		if (tank->getNextFrameBoundingBox().intersectsRect(enemy->getBoundingBox()))
		{
			tank->setisStop(true);
		}
		if (enemy->getNextFrameBoundingBox().intersectsRect(tank->getBoundingBox()))
		{
			enemy->setisStop(true);
		}
	}

}
void LogicLayer::BulletTestBound()
{
	bulletEvsT();
	bulletvsBarrer();
	bulletVsTank();
	bulletVsEnemy();
}
void LogicLayer::bulletEvsT()
{   //敌军子弹和己方子弹的碰撞
	auto enemybu = BulletManager::getInstance()->getEnemyBulletManger();
	auto tankbu = BulletManager::getInstance()->getTankBulletManager();
	for (auto eiter = enemybu.begin();eiter!=enemybu.end();eiter++)
	{   auto enemybullet = *eiter;
		for (auto titer = tankbu.begin();titer!=tankbu.end();titer++)
		{   auto tankbullet = *titer;
			if (enemybullet->getBoundingBox().intersectsRect(tankbullet->getBoundingBox()))
			{
				//设置所有子弹消失状态
				tankbullet->remove();
				enemybullet->remove();
			}
		}
	}
}
void LogicLayer::bulletvsBarrer()
{   
	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto map = dynamic_cast<MapLayer *>(scene->getChildByName("map"));
	/*auto sp = this->getChildByTag(1);
	auto t = map->checkIsNode(sp->getPosition());
	log("%d",t);*/
	//子弹和障碍
	auto tankbu = BulletManager::getInstance()->getTankBulletManager();
	auto enemybu = BulletManager::getInstance()->getEnemyBulletManger();
	/*auto tank = (BaseTank*)scene->getTanklayer()->getChildByName("tank");*/
	for (auto titer = tankbu.begin();titer!=tankbu.end();titer++)
	{    auto bu = (*titer);
	if (map->checkIsNode(bu->getPosition()) && !map->checkNodeWrite(bu->getPosition()))
		{
			if (map->checkNodeBreak(bu->getPosition()))
			{
				this->boundingBox(bu->getPosition());
			}
			bu->remove();
		}
	}
	for (auto titer = enemybu.begin();titer!=enemybu.end();titer++)
	{    auto bu = (*titer);
	if (map->checkIsNode(bu->getPosition()))
	{
		if (map->checkNodeBreak(bu->getPosition()))
		{
			this->boundingBox(bu->getPosition());
			
		}
		bu->remove();
	}
	}
}

void LogicLayer::bulletVsEnemy()
{
	auto tankbu = BulletManager::getInstance()->getTankBulletManager();
	auto enemy = EnemyManager::getInstance()->getEnemyManger();
	for(auto titer = tankbu.begin();titer!=tankbu.end();titer++)
	{  auto tankbullet = *titer;
	   for (auto eiter = enemy.begin();eiter!=enemy.end();eiter++)
	   {   
		   auto enemy = *eiter;
		   if (enemy->getBoundingBox().intersectsRect(tankbullet->getBoundingBox())&&!enemy->getISdie())
		   {
			   //设置消失状态
			   tankbullet->remove();
			   enemy->hurt(tankbullet->getATTACK());
		   }
	   }
	}
}
void LogicLayer::bulletVsTank()
{
	auto enemybu = BulletManager::getInstance()->getEnemyBulletManger();
	auto scene =dynamic_cast<GameScene *> (Director::getInstance()->getRunningScene());
	auto tank =(BaseTank *) scene->getTanklayer()->getChildByName("tank");
	
	if (tank==nullptr)
	{
		return;
	}
	tank->retain();
	for (auto eiter = enemybu.begin();eiter!=enemybu.end();eiter++)
	{   auto bullet = *eiter;
		if (tank->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
		{
			//tank掉血 gameover
			tank->hurt(bullet->getATTACK());
			bullet->remove();
			
		}
	}
	tank->release();
}
void LogicLayer::update(float t)
{   //清理失效物件
	TankTestBound();
	BulletTestBound();
	checkisDefeated();
	BulletManager::getInstance()->removeAllBullets();
	EnemyManager::getInstance()->removeAllenemys();
}
void LogicLayer::checkisDefeated()
{  
	auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto map = dynamic_cast<MapLayer *>(scene->getChildByName("map"));
	auto tank = (BaseTank*)scene->getTanklayer()->getChildByName("tank");
	if (map->isDefeated()||tank==nullptr)
	{
		map->failed();
		this->addChild(GameOverLayer::create());
		this->unscheduleAllSelectors();		
	}
}
void LogicLayer::boundingBox(Vec2 position)//子弹的碰撞 与地图的墙壁 同时四个点
{
	auto scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto layer = dynamic_cast<MapLayer*>(scene->getMaplayer());
	
	auto point1 = Vec2(position.x - 6, position.y - 6);
	
		layer->breakNode(point1);
	
	auto point2 = Vec2(position.x - 6, position.y + 6);
	
		layer->breakNode(point2);
	
	auto point3 = Vec2(position.x + 6, position.y + 6);
	
		layer->breakNode(point3);
	
	auto point4 = Vec2(position.x + 6, position.y - 6);
	
		layer->breakNode(point4); 
	 
}//change by liu tianhou 9.3 