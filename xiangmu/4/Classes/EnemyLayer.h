#ifndef __ENEMYLAYER__
#define __ENEMYLAYER__

#include "cocos2d.h"
class BaseEnemy;
//敌人移动速度
#define ENEMYSPEED 20
#define SMARTSPEED 50
class FirstBoss;

class EnemyLayer : public cocos2d::Layer
{
private:

	int Level;

	int isSkillsBomb;
	//创建普通敌人
	void createCommon(int isSkillsBomb);
	//创建精英敌人
	void createElite(int isSkillsBomb);
	//给boss出现计时
	int bossTime;
	FirstBoss *boss;
	static bool haveboss;

	//怪物系统升级
	void upLevel(Ref *);
protected:
	
	//创建敌人
	void createEnemy();
	//定时帧回调函数
	void addEnemy(float t);
	int contrlNum;
	cocos2d::Size vSize;
	virtual void onEnter();

	//创建普通敌人
	void createCommon_BlueGlost(int r);
	//创建精英敌人
	void createElite_Shadow(int r);
	void restartTime(Ref *);
public:
	~EnemyLayer();
	virtual bool init();

	CREATE_FUNC(EnemyLayer);
};

#endif // __HELLOWORLD_SCENE_H__