#include "Enemys.h"

Enemys *Enemys::instance = nullptr;

Enemys *Enemys::getInstance() {
	if(instance == nullptr) {
		instance = new Enemys();
	}
	return instance;
}

void Enemys::addEnemy(BaseEnemy *be) {
	enemyVector.pushBack(be);
}

void Enemys::deleteEnemy() {
	for(auto it = enemyVector.begin(); it != enemyVector.end(); ) {
		if((*it)->getDie()) {
			it = enemyVector.erase(it);
		}
		else {
			it++;
		}
	}
}

void Enemys::reset() {
	enemyVector.clear();
}
