/************************************************************************/
/* 
	1. 所有砖块的    allBricks
	2. 所有子弹的    allBullets
	3. 所有 敌人     allEnemies
	4. 所有的道具    allTools

*/
/************************************************************************/
#ifndef _ALLVECTORS_H
#define _ALLVECTORS_H
#include "cocos2d.h"
#include "EnemyBullet.h"
#include "HeroBullet.h"
#include "BaseTool.h"
#include "BaseEnemy.h"

using namespace cocos2d;

class AllVectors
{
private:
	AllVectors(){
		bg_music_isSelect = false;
		ef_music_isSelect = false;
	}		//构造函数
	AllVectors(const AllVectors * obj){}		//拷贝构造
	AllVectors operator=(const AllVectors * obj){return obj;}		//操作符重载
protected:
	static AllVectors * instance;		//单例对象
	Vector<Sprite *> bricksVector;		//砖块集合
	Vector<HeroBullet *> heroBulletsVector;		//英雄子弹集合
	Vector<EnemyBullet *> enemyBulletsVector;		//敌人子弹集合
	Vector<BaseTool *> toolsVector;			//道具集合
	Vector<Sprite *> groundsVector;			//地板集合
	Vector<BaseEnemy *> enemiesVector;		//

public:
	//获得单例
	static AllVectors * getInstance();
	//获得砖块集合-------
	Vector<Sprite *> getBricksVector();
	//向集合添加对象
	void addBrick(Sprite * brick);
	//从集合删除对象
	void deleteBrick(Sprite * brick);
	//清空集合
	void bricksVectorCleanUp();


	//获得主角子弹集合-------
	Vector<HeroBullet *> getHeroBulletsVector();
	//向集合添加对象
	void addHeroBullet(HeroBullet * bullet);
	//从集合删除对象
	void deleteHeroBullet();
	//清空集合
	void heroBulletsVectorClearUp();


	//获得敌人子弹集合--------
	Vector<EnemyBullet *> getEnemyBulletsVector();
	//向集合添加对象
	void addEnemyBullet(EnemyBullet * bullet);
	//从集合删除对象
	void deleteEnemyBullet();
	//清空集合
	void enemyBulletsVectorClearUp();


	//获得道具集合----------
	Vector<BaseTool *> getToolsVector();
	//向集合添加对象
	void addTool(BaseTool * tool);
	//从集合删除对象
	void deleteTool(BaseTool * tool);
	//清空集合
	void toolsVectorCleanUp();


	//获得敌人集合----------
	Vector<BaseEnemy *> getEnemiesVector();
	//向集合添加对象
	void addEnemy(BaseEnemy * enemy);
	//从集合删除对象
	void deleteEnemy();
	//清空集合
	void enemiesVectorCleanUp();


	//获得地板集合----------
	Vector<Sprite *> getGroundVector();
	//向集合添加对象
	void addGround(Sprite * ground);
	


	//设置 音乐和音效的 变量

	bool bg_music_isSelect;
	bool ef_music_isSelect;

	bool getBgmusic();
	void setBgmusic(bool bg);
	bool getEfmusic();
	void setEfmusic(bool ef);



};
#endif