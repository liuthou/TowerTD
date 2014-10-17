#include "EnemyOneBullet.h"
#include "SelectRole.h"
bool EnemyOneBullet::init(Vec2 position,int attack){
 	if(!BaseBullet::init("slice66_66.png",position,attack,SPEED)){
 		return false;
 	}
	return true;
}
EnemyOneBullet *EnemyOneBullet::create(Vec2 position,int attack){
 	EnemyOneBullet *enemyBullet = new EnemyOneBullet();
 	if(enemyBullet && enemyBullet->init(position,attack)){
 		enemyBullet->autorelease();
 		return enemyBullet;
 	}
 	CC_SAFE_DELETE(enemyBullet);
 	return nullptr;
}
void EnemyOneBullet::move(){
	Vec2 pointEnd = SelectRole::getInstence()->getRoleArmatures().at(0)->getPosition();
	for(int i = 0; i < SelectRole::getInstence()->getRoleArmatures().size();i++){
		Vec2 point = SelectRole::getInstence()->getRoleArmatures().at(i)->getPosition();
		if(point.x < pointEnd.x){
			pointEnd = point;
		}
	}
	float dis = 0;
 	if(this->getPositionX() > pointEnd.x){
 		dis = this->getPositionX() - pointEnd.x;
 	}else
 	{
 		dis = pointEnd.x - this->getPositionX();
 	}
 	auto move = MoveTo::create(dis/speed,Vec2(pointEnd.x,pointEnd.y));
 	auto remove = CallFunc::create([=](){
 		this->deleteMy();
 	});
 	auto seq = Sequence::create(move,remove,nullptr);
 	this->runAction(seq);
}