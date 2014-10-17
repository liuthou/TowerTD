#include "RoleOneBullet.h"
#include <SelectRole.h>
bool RoleOneBullet::init(Vec2 position,int attack){
 	if(!BaseBullet::init(IMAGENAME,position,attack,ROLEBULLETSPEED)){
 		return false;
 	}
 	return true;
}
void RoleOneBullet::move(){
 	Vec2 pointEnd = SelectRole::getInstence()->getEnemyArmatures().at(0)->getPosition();
 	for(int i = 0; i < SelectRole::getInstence()->getEnemyArmatures().size();i++){
		Vec2 point = SelectRole::getInstence()->getEnemyArmatures().at(i)->getPosition();
		if(pointEnd.x > point.x){
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
RoleOneBullet *RoleOneBullet::create(Vec2 position,int attack){
 	RoleOneBullet *bullet = new RoleOneBullet();
 	if(bullet && bullet->init(position,attack)){
 		bullet->autorelease();
 		return bullet;
 	}
 	CC_SAFE_DELETE(bullet);
 	return nullptr;
}