#include "QuadrantBullet.h"
#define  BULLETTIME 10
QuadrantBullet *QuadrantBullet::create(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int bulletSpecies){
	QuadrantBullet *pRet = new QuadrantBullet();
	if (pRet && pRet->init(speed, fromPosition, attack, fileName, toPosition,bulletSpecies))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool QuadrantBullet::init(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int bulletSpecies){
	if (!BaseBullet::init(speed, fromPosition, attack, fileName,bulletSpecies,0)){
		return false;
	}

	this->toPosition = toPosition;
	return true;
}

void QuadrantBullet::onEnter(){
	Sprite::onEnter();
	exeQuadrantBullet(this->getPosition());
}

void QuadrantBullet::exeQuadrantBullet(Vec2 fromPosition){
	Size viewSize = Director::getInstance()->getVisibleSize();
	//使用相似三角形
	float x_cut = abs(toPosition.x - fromPosition.x);
	float y_cut = abs(toPosition.y - fromPosition.y);

	//求敌人到英雄的距离
	float enemy_hero = ccpDistance(toPosition, fromPosition);
	float dis_time = this->getSpeed() * enemy_hero;
	//一，二，三，四象限内，和X轴正负方向，Y轴正负方向，原心9种情况  
	bool isInQuadrant1 = (toPosition.x > fromPosition.x) && (toPosition.y > fromPosition.y);
	bool isInQuadrant2 = (toPosition.x < fromPosition.x) && (toPosition.y > fromPosition.y);
	bool isInQuadrant3 = (toPosition.x < fromPosition.x) && (toPosition.y < fromPosition.y);
	bool isInQuadrant4 = (toPosition.x > fromPosition.x) && (toPosition.y < fromPosition.y);
	bool isOnXR = (toPosition.y == fromPosition.y) && (toPosition.x > fromPosition.x);
	bool isOnXL = (toPosition.y == fromPosition.y) && (toPosition.x < fromPosition.x);
	bool isOnYT = (toPosition.x == fromPosition.x) && (toPosition.y > fromPosition.y);
	bool isOnYD = (toPosition.x == fromPosition.x) && (toPosition.y < fromPosition.y);
	bool isZero = (toPosition.x == fromPosition.x) && (toPosition.y == fromPosition.y);
	//


	if (isInQuadrant1)
	{
		//敌人点和英雄点形成的直线的斜率  
		float mMidLineSlope = (fromPosition.y - toPosition.y) / (fromPosition.x - toPosition.x);
		//弧度值  
		float mMidLineAngleR = atan(mMidLineSlope);
		//角度值  
		float mMidLineAngleD = mMidLineAngleR*M_PI / 180;
		if (mMidLineAngleD > 45)
		{
			
			float hero_y = y_cut * toPosition.x / x_cut;
			viewSize = Director::getInstance()->getVisibleSize();
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition,Vec2(960, toPosition.y + hero_y));
			auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(960, toPosition.y + hero_y));
			this->runAction(Sequence::create(to, cf, NULL));

		}
		else{
			float hero_x = x_cut * toPosition.y / y_cut;
			viewSize = Director::getInstance()->getVisibleSize();
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition,Vec2(toPosition.x + hero_x, 640));
			auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(toPosition.x + hero_x, 640));
			this->runAction(Sequence::create(to, cf, NULL));
		}
	}
	else if (isInQuadrant2)
	{
		//敌人点和英雄点形成的直线的斜率  
		float mMidLineSlope = (fromPosition.y - toPosition.y) / (fromPosition.x - toPosition.x);
		//弧度值  
		float mMidLineAngleR = atan(mMidLineSlope);
		//角度值  
		float mMidLineAngleD = mMidLineAngleR*M_PI / 180;
		if (mMidLineAngleD > 45)
		{
			float hero_x = x_cut * toPosition.y / y_cut;
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition,Vec2(toPosition.x - hero_x, 640));
			auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(toPosition.x - hero_x, 640));
			this->runAction(Sequence::create(to, cf, NULL));
		}
		else{
			float hero_y = y_cut * toPosition.x / x_cut;
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition,Vec2(0, toPosition.y + hero_y));
			auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(0, toPosition.y + hero_y));
			this->runAction(Sequence::create(to, cf, NULL));
		}
	}
	else if (isInQuadrant3)
	{
		//敌人点和英雄点形成的直线的斜率  
		float mMidLineSlope = (fromPosition.x - toPosition.x) / (fromPosition.y - toPosition.y);
		//弧度值  
		float mMidLineAngleR = atan(mMidLineSlope);
		//角度值  
		float mMidLineAngleD = mMidLineAngleR*M_PI / 180;
		if (mMidLineAngleD > 45)
		{
			float hero_x = x_cut * toPosition.y / y_cut;
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition,Vec2(toPosition.x - hero_x, 0));
			auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(toPosition.x - hero_x, 0));
			this->runAction(Sequence::create(to, cf, NULL));
		}
		else{
			float hero_y = y_cut * toPosition.x / x_cut;
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition,Vec2(0, toPosition.y - hero_y));
			auto to = MoveTo::create(dist/this->getSpeed()*0.5, Vec2(0, toPosition.y - hero_y));
			this->runAction(Sequence::create(to, cf, NULL));
		}
	}
	else if (isInQuadrant4)
	{
		//敌人点和英雄点形成的直线的斜率  
		float mMidLineSlope = (fromPosition.x - toPosition.x) / (fromPosition.y - toPosition.y);
		//弧度值  
		float mMidLineAngleR = atan(mMidLineSlope);
		//角度值  
		float mMidLineAngleD = mMidLineAngleR*M_PI / 180;
		if (mMidLineAngleD > 45)
		{
			float hero_x = x_cut * toPosition.y / y_cut;
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition, Vec2(fromPosition.x + hero_x, 640));
			auto to = MoveTo::create(dist / getSpeed()*0.5, Vec2(fromPosition.x + hero_x, 640));
			this->runAction(Sequence::create(to, cf, NULL));
		}
		else{
			float hero_y = y_cut * toPosition.x / x_cut;
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			float dist = ccpDistance(fromPosition, Vec2(960, toPosition.y - hero_y));
			auto to = MoveTo::create(dist / getSpeed()*0.5, Vec2(960, toPosition.y - hero_y));
			this->runAction(Sequence::create(to, cf, NULL));
		}
	}else if (isOnXL)
	{
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition,Vec2(0, toPosition.y));
		auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(0, toPosition.y));
		this->runAction(Sequence::create(to, cf, NULL));
	}else if(isOnXR){
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition,Vec2(960, toPosition.y));
		auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(960, toPosition.y));
		this->runAction(Sequence::create(to, cf, NULL));
	}else if (isOnYD)
	{
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition,Vec2(toPosition.x, 640));
		auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(toPosition.x, 640));
		this->runAction(Sequence::create(to, cf, NULL));
	}else if (isOnYD)
	{
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition,Vec2(toPosition.x, 0));
		auto to = MoveTo::create(dist/getSpeed()*0.5, Vec2(toPosition.x, 0));
		this->runAction(Sequence::create(to, cf, NULL));
	}
	else if (isOnXL)
	{
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition, Vec2(0, toPosition.y));
		auto to = MoveTo::create(dist / getSpeed()*0.5, Vec2(0, toPosition.y));
		this->runAction(Sequence::create(to, cf, NULL));
	}
	else if (isOnXR){
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition, Vec2(960, toPosition.y));
		auto to = MoveTo::create(dist / getSpeed()*0.5, Vec2(960, toPosition.y));
		this->runAction(Sequence::create(to, cf, NULL));
	}
	else if (isOnYD)
	{
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition, Vec2(toPosition.x, 640));
		auto to = MoveTo::create(dist / getSpeed()*0.5, Vec2(toPosition.x, 640));
		this->runAction(Sequence::create(to, cf, NULL));
	}
	else if (isOnYD)
	{
		auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
		float dist = ccpDistance(fromPosition, Vec2(toPosition.x, 0));
		auto to = MoveTo::create(dist / getSpeed()*0.5, Vec2(toPosition.x, 0));
		this->runAction(Sequence::create(to, cf, NULL));
	}
}


