#ifndef __BASEENEMY__
#define __BASEENEMY__
#include "Conf.h"
class GameScene;

class BaseEnemy : public cocos2d::Sprite
{

private:
	//初始化属性方法
	void initPro(float coefficient);

	//是否携带道具
	void isSkillsBomb(int sb);

	

protected:

	//子弹速度系数
	float bulletCoefficient;

	int sb;

	GameScene* scene;

	//动画精灵
	Sprite * sp;
	//敌人类型
	CC_SYNTHESIZE(bool, enemyType, EnemyType);

	//视图大小
	Size vSize;
	
	//飞行动画
	virtual void enemyFly() = 0;

	//死亡动画
	virtual ActionInterval * enemyDie() = 0;

	//受伤动画
	virtual void  enemyHurt();

	//死亡方法
	virtual void die();
	
	virtual void removeEnemyNode();

	//发射子弹 定时帧回调
	virtual void addFire(float t);


public:
	//死亡标记
	CC_SYNTHESIZE(bool, isDie, Die);
	
	//初始化，携带道具，等级
	virtual bool initWithSpriteFrameName(std::string fileName, int sb, int level);

	virtual void onEnter();

	virtual void createBullet(std::string fileName);

	virtual void hurt(int attack);

	
	CC_SYNTHESIZE(int, _score, Score);
	CC_SYNTHESIZE(float, _enemySpeed, EnemySpeed);
	CC_SYNTHESIZE(float, _hp, Hp)
};

#endif // __HELLOWORLD_SCENE_H__