#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include "EnemyBase.h"
#include "BaseTower.h"
#include "BaseSkill.h"
USING_NS_CC;
class GameManager
{  
	~GameManager();
public:
	void pauseEnemy(); //pause enemy action and schedule
	void pauseSkill(); //pause skill action and schedule
	void pauseTower();//pause tower action and schedule
	void resumeEnemy();//resume enemy action and schedule
	void resumeSkill();//resume skill action and schedule
	void resumeTower();//resume tower action and schedule
	void pauseAll();  //pause enemy,tower,skill action and schedule
	void resumeAll(); //resume enemy,tower,skill action and schedule
public:
	Vector<BaseSkill *> skillVector;
	Vector<BaseTower *> towerVector;
	Vector<EnemyBase *> enemyVector;
	std::vector<ValueMap> enemyGroups;
	std::vector<int> towerSelectVector;
	std::vector<std::string> preEnemyTypesVector;
	std::vector<std::string> enemyTypesVector;
    int curlevel;
	ValueMap resources;
	void init();
	void nextStage();
	void selectStage(int stage);
	int getStageMoney();
	Layer* getStageLayer();
	Layer* getUiLayer();
	void pause();// pause the stage,include children
	void resume();// resume the stage,include children
	void cleanAllVector();
	static GameManager * sharegamemanager;
	static GameManager * getInstance();
};
#endif // !__GAMEMANAGER_H
