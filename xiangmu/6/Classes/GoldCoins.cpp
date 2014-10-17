#include "GoldCoins.h"
GoldCoins * GoldCoins::instance = nullptr;
GoldCoins * GoldCoins::getinstance(){
	if (!instance){
		instance = new GoldCoins();
	}
	return instance;
}
void GoldCoins::addgolecoin(BaseGoleCoin * bc){
	golecoinVector.pushBack(bc);
}
void GoldCoins::deletegolecoin(){
	for (auto it = golecoinVector.begin();it != golecoinVector.end();){
		if ((*it)->getIsdie()){
			it = golecoinVector.erase(it);
		}else{
			it++;
		}
	}
}