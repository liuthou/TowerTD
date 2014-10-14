#include "Enemylayer.h"
#include "OneEnemyplan.h"
#include "TwoEnemyplan.h"
#include "ThreeEnemylayer.h"
bool Enemylayer::init(){
	if(!Layer::init()){
		return false;;
	}
	//初始化
	t=0;
	quickf=5;
	bigf=0;
	levelt=20;
	outplane=0.8;
	outsum=0;
	//增加时间	
	//一秒回调一次
	this->schedule(schedule_selector(Enemylayer::addtime),1);
	this->schedule(schedule_selector(Enemylayer::update));
	return true;
}
void Enemylayer::addtime(float t){
	this->t++;
	if(this->t>levelt){
		nextlevel();
	}
}
void Enemylayer::nextlevel(){
	//升级
	levelt*+2;
	//快飞机概率
	if(quickf<50){
	quickf+=5;
	}
	//大飞机概率
	if(bigf<10){
		bigf++;
	}
}
void Enemylayer::go(){
	int r = CCRANDOM_0_1() * 100;
	if(r < bigf) {
		//出现大飞机
		ThreeEnemyplan::create(DAFEIJISPEED);
	} else {
		int k = CCRANDOM_0_1() * 100;
		//速度
		int spe = k < quickf ? QUICKSPEED : BASEPLANSPEED;
		//出现中飞机
		r = CCRANDOM_0_1() * 100;
		if(r < 20) {
			TwoEnemyplan::create(spe);
		} else {
			OneEnemyplan::create(spe);
		}
	}
}

void Enemylayer::update(float t){
	outsum+=t;
	if(outsum>outplane){
		//输出飞机
		go();
		outsum=0;
	}
}
