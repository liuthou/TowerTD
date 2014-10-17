#include "Bullets.h"
Bullets *Bullets::instence = nullptr; 
Bullets *Bullets::getInstence(){
	if(instence == nullptr){
		instence = new Bullets();
	}
	return instence;
}

Vector<BaseBullet *> Bullets::getRoleBullets(){
	return this->roleBullets;
}

void Bullets::addRoleBullets(BaseBullet *bullet){
	roleBullets.pushBack(bullet);
}

void Bullets::deleteRoleBullets(){
	for(int i = 0; i < roleBullets.size();i++){
		auto bullet = roleBullets.at(i);
		if(bullet->getIsDie() == true){
			roleBullets.erase(i);
			bullet->deleteMy();
			i--;
		}
	}
}

void Bullets::deleteRoleBulletsAll(){
	roleBullets.clear();
}

Vector<BaseBullet *> Bullets::getEnemyBullets(){
	return this->enemyBullets;
}

void Bullets::addEnemyBullets(BaseBullet *bullets){
	enemyBullets.pushBack(bullets);
}

void Bullets::deleteEnemyBullets(){
	for(int i = 0; i < enemyBullets.size();i++){
		auto bullet = enemyBullets.at(i);
		if(bullet->getIsDie() == true){
			enemyBullets.erase(i);
			bullet->deleteMy();
			i--;
		}
	}
}

void Bullets::deleteEnemyBulletsAll(){
	enemyBullets.clear();
}