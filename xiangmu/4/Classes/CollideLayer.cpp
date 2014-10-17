#include "CollideLayer.h"
#include "HeroesBullets.h"
#include "Hero_SwordPlay.h"
#include "Elite_Shadow.h"
#include "EnemyBullets.h"
#include "Enemys.h"
#include "GameScene.h"
#include "SkillBullet.h"
#include "Tools.h"
#include "ToolBomb.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool CollideLayer::init(){
	if (!Layer::create())
	{
		return false;
	}
	this->level = 1;
	this->scheduleUpdate();

	return true;
}



//主角和敌人子弹的碰撞
void CollideLayer::heroes_EnemyBullet_Collide(EnemyBullets* ebs, BaseHeroes* hero){

	auto ebsV = ebs->getBullet();

	for (auto it = ebsV.begin(); it != ebsV.end(); it++)
	{
		BaseBullet* bb = *it;
		if (bb->getBoundingBox().intersectsRect(hero->getBox()))
		{
			if (hero->getIsProtect() == true)
			{
				break;
			}
			else
			{
				hero->hurt();
				level--;
				bb->die();
				break;
			}
		}
	}
}

//主角和敌人的碰撞
void CollideLayer::heroes_Enemy_Collide(Enemys* es, BaseHeroes* hero){

	auto esV = es->getEnemyVector();
	
	for (auto it = esV.begin(); it != esV.end(); it++)
	{
		BaseEnemy* be = *it;
		if (be->getBoundingBox().intersectsRect(hero->getBox()))
		{
			if (hero->getIsProtect() == true)
			{
				break;
			}
			else
			{
				hero->hurt();
				level--;
				break;
			}
		}
	}
}


//主角和道具的碰撞
void CollideLayer::heroes_Tool_Collide(Tools* tool, BaseHeroes* hero){
	auto toolV = tool->getToolVector();
	for (auto toolIt = toolV.begin(); toolIt != toolV.end(); toolIt++)
	{
		Tool* tool = *toolIt;
		if (hero->getBox().intersectsRect(tool->getBoundingBox()))
		{
			tool->removeTools();
			SimpleAudioEngine::getInstance()->playEffect("addToolMusic.wav");
			if (typeid(*tool) == typeid(ToolBomb))
			{
				auto center = __NotificationCenter::getInstance();
				center->postNotification("ToolsPeng", this);
			}
			else{
				
				if (level < 3)
				{
					level++;
					auto hero = dynamic_cast<BaseHeroes*>(ShareFunc::getGameScene()->getHeroLayer()->getChildByName("hero"));
					auto pet = dynamic_cast<BasePet*>(ShareFunc::getGameScene()->getHeroLayer()->getChildByName("pet"));
					hero->setBulletLevel(level);
					pet->setPetAttack(level);
				}
				

			}
				
			break;
		}
	}
}
//主角子弹和敌人碰撞
void CollideLayer::heroesBulletCollideQuick(HeroesBullets* hbs, Enemys* es){

	auto hbsV = hbs->getBullets();
	auto esV = es->getEnemyVector();

	for (auto hbIt = hbsV.begin(); hbIt != hbsV.end(); hbIt++)
	{
		for (auto beIt = esV.begin(); beIt != esV.end(); beIt++)
		{
			BaseBullet* bb = *hbIt;
			BaseEnemy* be = *beIt;
			if (be->getEnemyType() == true)
			{
				Elite_Shadow * es = (Elite_Shadow *)be;
				if (es->getFirstCollide() == true)
				{
					if (bb->getBoundingBox().intersectsRect(es->getBoundingBox(1)))
					{
						es->elude();
						bulletType(bb);
						break;
					}
				}
				else if (es->getFirstCollide() == false)
				{
					if (bb->getBoundingBox().intersectsRect(es->getBoundingBox()))
					{
						es->hurt(bb->getAttack());
						bulletType(bb);
						break;
					}
				}
			}
			else if (be->getEnemyType() == false)
			{
				if (bb->getBoundingBox().intersectsRect(be->getBoundingBox()))
				{
					be->hurt(bb->getAttack());
					bulletType(bb);
					break;
				}
			}else
			{
				if (bb->getBoundingBox().intersectsRect(be->getBoundingBox()))
				{
					be->hurt(bb->getAttack());
					bulletType(bb);
					break;
				}
			}
		}
	}
}


void CollideLayer::removeAllObj(HeroesBullets* hbs, EnemyBullets* ebs, Enemys* es, Tools* tool){
	hbs->deleteBullet();
	ebs->deleteBullet();
	es->deleteEnemy();
	tool->deleteTool();
}

void CollideLayer::update(float f){

	auto hbs = HeroesBullets::getInstance();
	auto ebs = EnemyBullets::getInstance();
	auto es = Enemys::getInstance();
	auto tools = Tools::getInstance();


	auto gameScene = dynamic_cast<GameScene*> (Director::getInstance()->getRunningScene());
	auto hero = dynamic_cast<BaseHeroes*>(gameScene->getHeroLayer()->getChildByName("hero"));

	//主角子弹和敌人的碰撞
	heroesBulletCollideQuick(hbs, es);
	
	//主角和敌人子弹的碰撞
	heroes_EnemyBullet_Collide(ebs, hero);

	//主角和敌人的碰撞
	heroes_Enemy_Collide(es,hero);

	heroes_Tool_Collide(tools,hero);

	//清除所有在集合中的对象
	removeAllObj(hbs, ebs, es, tools);
}

void CollideLayer::bulletType(BaseBullet* bb){

	if (typeid(*bb) == typeid(SkillBullet))
	{

		auto sb = dynamic_cast<SkillBullet*>(bb);

		sb->die();

	}else{

		bb->die();

	}

}