#ifndef __COLLIDELAYER_H_
#define __COLLIDELAYER_H_

#include "Conf.h"
class GameScene;
class HeroesBullets;
class Enemys;
class BaseBullet;
class BaseEnemy;
class EnemyBullets;
class BaseHeroes;
class Tools;
class CollideLayer : public cocos2d::Layer
{
private:
	//主角_精英怪碰撞
	//void hero_strengthen
	//主角普通怪碰撞
	void heroesBulletCollideQuick(HeroesBullets* hbs, Enemys* es);
	void bulletType(BaseBullet* bb);
	int level;
protected:
	//敌人和主角的碰撞
	void heroes_Enemy_Collide(Enemys* es, BaseHeroes* hero);
	//敌人子弹和主角的碰撞
	void heroes_EnemyBullet_Collide(EnemyBullets* ebs, BaseHeroes* hero);
	//主角和道具的碰撞
	void heroes_Tool_Collide(Tools* tool, BaseHeroes* hero);
	//删除子弹OR敌人
	void removeAllObj(HeroesBullets* hbs, EnemyBullets* ebs, Enemys* es, Tools* tool);

	virtual void update(float f);
public:


	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CollideLayer);
};

#endif // __HELLOWORLD_SCENE_H__