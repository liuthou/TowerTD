/**

* 类名：MonsterManager

* 作者：陈川

* 日期：

* 作用 : 一波一波的出现怪物,现在的版本出现怪物的数量是一定的
			最终的版本应该无限出怪,直到游戏结束为止

**/ 
#ifndef __MONSTERMANAGER_H_
#define __MONSTERMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
class MonsterManager:public Node{
public:
	CREATE_FUNC(MonsterManager);
	void setEarnScoreFunc(std::function<void(int)> monsteraddprice);
	//怪物死亡特效(绑定给怪物回调)
	void monsterDieEffect(Vec2 diepoint);
protected:
	virtual bool init();
	//初始化关卡难度
	void initLevel();
	//出现一波怪物
	void waveMonster(float dt);
	//生成一个怪物
	void createMonster(float dt);
	//随机一个怪物出生位置
	Vec2 monsterCreatePosition();
	virtual void onEnter();
protected:
	//第几波怪
	int nowwaves;
	//每一波之间的间隔
	int intervalperwave;
	//共有几波怪
	int totalwaves;
	//循环次数(出怪数量为monsternumperwave*wavecount,wavecount最大为5)
	int wavecount;
	//每一波怪的id
	std::map<int,int> monsters_id;
	//每一波怪之间的间隔(不应该小于等于2s)
	std::map<int,int> delaytimeperwave;
	//每一波有几个怪
	std::map<int,int> monsternumperwave;
	//怪物死亡时回调这个function,创建怪物时传给怪物
	std::function<void(int)> monsteraddprice;
	ProgressTimer* pro;
	float progress;
};
#endif