#include "GameManager.h"
#include "XmlHelper.h"

GameManager *GameManager::sharegamemanager = nullptr;
GameManager * GameManager::getInstance() //gamemanager singelton
{
	if (sharegamemanager == nullptr)
	{
		sharegamemanager = new GameManager();
		sharegamemanager->init();
	}
	return sharegamemanager;
}
void GameManager::init() //initialize first stage ?? will init from userdeful;
{  
	curlevel = 1;
}
// change to next stage
void GameManager::nextStage()
{   
	curlevel++;
	if (curlevel > 24)
	{ 
		curlevel = 1;
	}
	selectStage(curlevel);

}
// select stage
void GameManager::selectStage(int stage)
{   
	log("you select %d",stage);
	cleanAllVector();
	preEnemyTypesVector = enemyTypesVector;
	curlevel = stage;
	XmlHelper xml;
	std::string map = StringUtils::format("map%02d.title",curlevel);
	xml.loadXML(map);
	resources = xml.getResoures();
	enemyGroups = xml.getEnenmyGroups();
	enemyTypesVector = xml.types;
	log("select complete!!!");
}
Layer* GameManager::getStageLayer()
{
	auto instance = Director::getInstance();
	auto stageLayer = dynamic_cast<Layer *>(instance->getRunningScene()->getChildByName("stage"));
	if (stageLayer == nullptr)
	{
		return nullptr;
	}
	return stageLayer;
}
Layer* GameManager::getUiLayer()
{
	auto instance = Director::getInstance();
	auto uiLayer = dynamic_cast<Layer *>(instance->getRunningScene()->getChildByName("ui"));
	if (uiLayer == nullptr)
	{
		return nullptr;
	}
	return uiLayer;
}
int GameManager::getStageMoney()
{   
	if (resources.size() <= 0)
	{
		return 0;
	}
	int money = resources.at("money").asInt();
	return money;
}
void GameManager::pause()
{   
	if (!getStageLayer())
	{
		return;
	}
	auto chlidren = getStageLayer()->getChildren();
	for (auto it = chlidren.begin();it != chlidren.end();it++)
	{   
		if (!(*it)->isRunning())
		{
			return;
		}
		(*it)->pause();
	}
	pauseAll();
}
void GameManager::resume()
{   
	if (!getStageLayer())
	{
		return;
	}
	auto chlidren = getStageLayer()->getChildren();
	for (auto it = chlidren.begin();it != chlidren.end();it++)
	{   
		if (!(*it)->isRunning())
		{
			return;
		}
		(*it)->resume();
	}
	resumeAll();
}
void GameManager::pauseEnemy()
{
	for (auto it = enemyVector.begin();it != enemyVector.end();it++)
	{    
		if (!(*it)->isRunning())
		{   
			
			return;
		}
		(*it)->pause();
	}
}
void GameManager::pauseTower()
{
	for (auto it = towerVector.begin();it != towerVector.end();it++)
	{    
		if (!(*it)->isRunning())
		{
			return;
		}
		(*it)->pauseAllTowers();
		(*it)->pause();
	}
}
void GameManager::pauseSkill()
{
	for (auto it = skillVector.begin();it != skillVector.end();it++)
	{    
		if (!(*it)->isRunning())
		{
			return;
		}
		(*it)->pause();
	}
}
void GameManager::resumeSkill()
{
	for (auto it = skillVector.begin();it != skillVector.end();it++)
	{    
		if (!(*it)->isRunning())
		{
			return;
		}
		(*it)->resume();
	}
}
void GameManager::resumeEnemy()
{
	for (auto it = enemyVector.begin();it != enemyVector.end();it++)
	{    
		if (!(*it)->isRunning())
		{
			
			return;
		}
		(*it)->resume();
	}
}
void GameManager::resumeTower()
{
	for (auto it = towerVector.begin();it != towerVector.end();it++)
	{    
		if (!(*it)->isRunning())
		{
			return;
		}
		(*it)->resume();
	}
}
void GameManager::pauseAll()
{
	pauseEnemy();
	pauseTower();
	pauseSkill();
}
void GameManager::resumeAll()
{
	resumeEnemy();
	resumeTower();
	resumeSkill();
}
void GameManager::cleanAllVector()
{
	enemyVector.clear();
	skillVector.clear();
	towerVector.clear();
	towerSelectVector.clear();
}
GameManager::~GameManager()
{
	CC_SAFE_DELETE(sharegamemanager);
}