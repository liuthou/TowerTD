#ifndef __ENTITYMANAGER_H_
#define __ENTITYMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
class Bullet;
class Enemy;
class Tower;
class HealthData;
class VirctoSprite;
class FormatUtil;
class EntityManager{
private:
    static EntityManager * Instance;
public:
	static EntityManager* getInstance();
	Vector<Tower*> TowerVector;
	Vector<Enemy*> Monster;
	Vector<Bullet*> TowerBullet;
	Vector<Bullet*> MonsterBullet;
	Vector<HealthData*>healthData;
	//怪物子弹攻击塔
	void checkBulletHitTower();
	//塔子弹攻击怪
	void checkBulletHitMonster();
	//怪沿着塔走,不能穿过塔
	//bool couldPass(Entity* monster);
	void BindingChak();
	void removeInvalidTowerEnemy();
	//塔攻击怪
	Sprite* ChakRangeTower(Tower* tower);
	//怪攻击塔
	Sprite* ChakRamgeManager(Enemy* enemy);
	//删除单例
	void reset();
	//删除塔
	//正常文件和胜利精灵的碰撞检测
	bool CheckInsterData(VirctoSprite*vsp);
	//敌人和胜利精灵的碰撞检测
	void CheckEnemyInsterVsp(VirctoSprite*vsp);
	//放塔时判断有没有怪
	//有怪返回true 没有返回false
	bool checkhasEntity(Tower* tower);
	//格式化(炸弹道具)
	void formatData(FormatUtil* formatutil);
	void towerDie();
	CC_SYNTHESIZE(int,monsterkillednum,MonsterKilledNum);
protected:
	EntityManager();
	virtual~EntityManager();
	EntityManager(const EntityManager& manager);
	EntityManager* operator=(const EntityManager& manager);
};
#endif