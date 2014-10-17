#include "SceneManager.h"
USING_NS_CC;
SceneManager* SceneManager::scenemanager=NULL;

SceneManager* SceneManager::getInstance(){
	if (scenemanager == nullptr)
	{
		scenemanager = new SceneManager();
	}

	return scenemanager;
}








SceneManager::SceneManager(){

}
SceneManager::~SceneManager(){

}
SceneManager::SceneManager(const SceneManager &scenemanager){

}
SceneManager* SceneManager::operator=(const SceneManager &scenemanager){
	return nullptr;
}