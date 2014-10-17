#include "AllVectors.h"

AllVectors * AllVectors::instance = nullptr;		//单例对象

AllVectors * AllVectors::getInstance(){
	if (instance == NULL){
		instance = new AllVectors();
	}
	return instance;
}

Vector<Sprite *> AllVectors::getBricksVector(){
	return bricksVector;
}

void AllVectors::addBrick(Sprite * brick){
	bricksVector.pushBack(brick);
}

void AllVectors::deleteBrick(Sprite * brick){
	bricksVector.eraseObject(brick);
}

void AllVectors::bricksVectorCleanUp(){
	bricksVector.clear();
}

Vector<HeroBullet *> AllVectors::getHeroBulletsVector(){
	return heroBulletsVector;
}

void AllVectors::addHeroBullet(HeroBullet * bullet){
	heroBulletsVector.pushBack(bullet);

}

void AllVectors::deleteHeroBullet(){

	for (auto it = heroBulletsVector.begin();it!=heroBulletsVector.end();){
		if ((*it)->getState()){
			it= heroBulletsVector.erase(it);
		}else{
			it++;
		}
	}

}

void AllVectors::heroBulletsVectorClearUp(){
	heroBulletsVector.clear();
}

Vector<EnemyBullet *> AllVectors::getEnemyBulletsVector(){
	return enemyBulletsVector;
}

void AllVectors::addEnemyBullet(EnemyBullet * bullet){
	enemyBulletsVector.pushBack(bullet);
}

void AllVectors::deleteEnemyBullet(){
	for (auto it = enemyBulletsVector.begin();it!=enemyBulletsVector.end();){
		if ((*it)->getState()){
			it= enemyBulletsVector.erase(it);
		}else{
			it++;
		}
	}

}

void AllVectors::enemyBulletsVectorClearUp(){
	enemyBulletsVector.clear();
}

Vector<BaseTool *> AllVectors::getToolsVector(){
	return toolsVector;
}

void AllVectors::addTool(BaseTool * tool){
	toolsVector.pushBack(tool);
}

void AllVectors::deleteTool(BaseTool * tool){
	toolsVector.eraseObject(tool);
}

void AllVectors::toolsVectorCleanUp(){
	toolsVector.clear();
}

//获得地板集合----------
Vector<Sprite *> AllVectors::getGroundVector(){
	return groundsVector;
}
//向集合添加对象
void AllVectors::addGround(Sprite * ground){
	groundsVector.pushBack(ground);
}

//获得敌人集合----------
Vector<BaseEnemy *> AllVectors::getEnemiesVector(){
	return enemiesVector;
}
//向集合添加对象
void AllVectors::addEnemy(BaseEnemy * enemy){
	enemiesVector.pushBack(enemy);
}
//从集合删除对象
void AllVectors::deleteEnemy(){
	for (auto it = enemiesVector.begin(); it != enemiesVector.end();) {
		if ((*it)->getIsDie() == true) {
			it = enemiesVector.erase(it);
		}else{
			it++;
		}
	}
}
//清空集合
void AllVectors::enemiesVectorCleanUp(){

	enemiesVector.clear();
}

bool AllVectors::getBgmusic(){
	return bg_music_isSelect;
}
void AllVectors::setBgmusic(bool bg){
	bg_music_isSelect = bg;
}

bool AllVectors::getEfmusic(){
	return ef_music_isSelect;
}
void AllVectors::setEfmusic(bool ef){
	ef_music_isSelect = ef;
}