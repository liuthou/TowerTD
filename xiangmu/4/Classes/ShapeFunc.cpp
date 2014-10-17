#include "ShapeFunc.h"
#include "LinearBullet.h"
#include "EnemyBullets.h"
shapeFunc *shapeFunc::create(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number){
	shapeFunc *pRet = new shapeFunc();
	if (pRet && pRet->init(speed, fromPosition, attack, fileName, toPosition, number))
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

bool shapeFunc::init(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number){
	if (!Sprite::init()){
		return false;
	}



	this->number = number;
	this->toPosition = toPosition;
	this->setSpeed(speed);
	this->vfromPostion = fromPosition;
	spritenumber = 0;
	for (int i = 0; i < number; i++){
		
		LinearBullet * sp = LinearBullet::create(speed,fromPosition,attack,fileName,1,2);
		sp->setTag(i);
		sp->setPosition(fromPosition);
		this->addChild(sp);
		sp->setScale(0.5);
		EnemyBullets::getInstance()->addBullet(sp);
	}

	this->scheduleUpdate();
	return true;
}

void shapeFunc::onEnter(){
	Sprite::onEnter();
	halfcicle_bullet(this->getSpeed(), vfromPostion, this->toPosition, number);
}


void shapeFunc::halfcicle_bullet(float speed, Vec2 fromPosition, Vec2 toPosition, int number){

	bool isjishu;
	float mMidValue = 0;
	if (number %2 == 0)
	{
		mMidValue = number % 2 + number - 3;
		isjishu = 0;
	}else
	{
		isjishu = 1;
		mMidValue = number % 2 + number - 3;
	}
	

	//以子弹起始点为原心，建立直角坐标系  
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

	//起始点和触摸点形成的直线的斜率  
	float mMidLineSlope = (fromPosition.y - toPosition.y) / (fromPosition.x - toPosition.x);
	//弧度值  
	float mMidLineAngleR = atan(mMidLineSlope);
	//角度值  
	float mMidLineAngleD =CC_RADIANS_TO_DEGREES( mMidLineAngleR);

	float mm = mMidLineAngleD;
	
	//lo
	//如果在二，三象限，mMidLineAngleD会小于0  
	if (isInQuadrant2 || isInQuadrant3)
	{
		//转换为正数，方便计算  
		mMidLineAngleD = 180 + mMidLineAngleD;
	}
	else if (isOnYT)
	{
		mMidLineAngleD = 90;
	}
	else if (isOnXR)
	{
		mMidLineAngleD = 0;
	}
	else if (isOnXL)
	{
		mMidLineAngleD = 180;
	}
	else if (isInQuadrant4)
	{
		//在第四象限mMidLineAngleD小于0，转换为正数  
		mMidLineAngleD = 360 + mMidLineAngleD;
	}
	else if (isOnYD)
	{
		mMidLineAngleD = 270;
	}
	else if (isZero)
	{
		return  ;
	}

	if (isInQuadrant4)
	{
		mMidLineAngleD = 360 - mMidLineAngleD;
	}
	else if (isInQuadrant2)
	{
		mMidLineAngleD = 180 - mMidLineAngleD;
	}
	else if (isInQuadrant3)
	{
		mMidLineAngleD += 180;
	}

	//x和y方向的增量  
	float mIncrementX = 0;
	float mIncrementY = 0;
	float mIncrement = 3;
	
	bool isone = isInQuadrant1;
	bool istwo = isInQuadrant2;
	bool isthree = isInQuadrant3;
	bool isforth = isInQuadrant4;

	//每颗子弹形成的直线的角度 
	float mLineAngleD = 0;

	if (isjishu)
	{
		mLineAngleD = mm - (number-number/2-1)*ANGLE;
	}else
	{
		mLineAngleD = mm - (number/2 )*ANGLE+ANGLE/2;
	}
	for (int i = 1 ; i <= number ; i++)
	{
		
		float mlined = 0;
		if (mLineAngleD < 0)
		{
			if (isInQuadrant1)
			{
				mlined = mLineAngleD + 360;
				isone = false;
				isforth = true;
			}else if (isInQuadrant3)
			{
				mlined = mLineAngleD + 180;
				istwo = true;
				isthree = false;
			}else if (isInQuadrant2)
			{
				mlined = mLineAngleD;
				istwo = true;
			}else
			{
				mlined = mLineAngleD;
				isforth = true;
			}
			if (isOnYT)
			{
				isone = true;
				if (isjishu)
				{
					mIncrementY = speed;
				}
				
			}
			else if (isOnXR)
			{
				isforth = true;
				if (isjishu)
				{
					mIncrementX = speed;
				}
			}
			else if (isOnXL)
			{
				istwo = true;
				if (isjishu)
				{
					mIncrementX = -speed;
				}
			}else if (isOnYD)
			{
				isforth = true;
				if (isjishu)
				{
					mIncrementY = -speed;
				}
				
			}
		}else if(mLineAngleD > 0)
		{
			if (isInQuadrant1)
			{
				mlined = mLineAngleD;
				isone = true;
				isforth = false;
			}else if (isInQuadrant3)
			{
				mlined = mLineAngleD;
				istwo = false;
				isthree = true;
			}else if (isInQuadrant2)
			{
				mlined = 180 + mLineAngleD;
				istwo = false;
				isthree = true;
			}else
			{
				mlined = mLineAngleD;
				isforth = false;
				isone = true;
			}
			if (isOnYT)
			{
				istwo = true;
				isone = false;
				if (isjishu)
				{
					mIncrementY = speed;
				}
			}
			else if (isOnXR)
			{
				isforth = false;
				isone = true;
				if (isjishu)
				{
					mIncrementX = speed;
				}
			}
			else if (isOnXL)
			{
				istwo = false;
				isthree = true;
				if (isjishu)
				{
					mIncrementX = -speed;
				}
			}else if (isOnYD)
			{
				isthree = true;
				isforth = false;
				if (isjishu)
				{
					mIncrementY = -speed;
				}

			}
		}
		float mLineAngleR = CC_DEGREES_TO_RADIANS(mlined);

		if (isone)
		{
			mIncrementX = abs(mIncrement * cos(mLineAngleR))*this->getSpeed();
			mIncrementY = abs(mIncrement * sin(mLineAngleR))*this->getSpeed();
		}
		else if (istwo)
		{
			mIncrementX = mIncrement * cos(mLineAngleR)*this->getSpeed();
			mIncrementY = abs(mIncrement * sin(mLineAngleR))*this->getSpeed();
			if (mIncrementX > 0) mIncrementX = -mIncrementX;
		}else if (isthree)
		{
			mIncrementX = mIncrement * cos(mLineAngleR)*this->getSpeed();
			mIncrementY = mIncrement * sin(mLineAngleR)*this->getSpeed();
			if (mIncrementX > 0) mIncrementX = -mIncrementX;
			if (mIncrementY > 0) mIncrementY = -mIncrementY;
		}
		else if (isforth)
		{
			mIncrementX = abs(mIncrement * cos(mLineAngleR))*this->getSpeed();
			mIncrementY = mIncrement * sin(mLineAngleR)*this->getSpeed();
			if (mIncrementY > 0) mIncrementY = -mIncrementY;
		}
		
		Increment mResult = Increment(mIncrementX, mIncrementY);
		own.push_back(mResult);
		mLineAngleD += ANGLE;
	}
	
	//每颗子弹形成的直线的弧度  
	
	return;
}

void shapeFunc::update(float t){
	for (int i = 0; i < this->number; i++)
	{
		LinearBullet * sprite = (LinearBullet *)this->getChildByTag(i);
		if (sprite)
		{
		for (int j = 0; j < own.size(); j++)
		{
			auto it = own.at(j);
			if (j == i)
			{
				sprite->runAction(MoveTo::create((this->getSpeed()/50)/3, Vec2(sprite->getPosition().x + it.incrementX, sprite->getPosition().y + it.incrementY)));
			}

		}
		}

	}
	//判断精灵是否出屏
	for (int i = 1; i < number; i++)
	{
		Sprite * sprite = (Sprite *)this->getChildByTag(i);
		if (sprite)
		{
		if (sprite->getPositionX() > 960 || sprite->getPositionX() < 0)
		{
			auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
			sprite->runAction(cf);
			spritenumber++;
			if (spritenumber == number)
			{
				this->removeFromParentAndCleanup(true);
			}
		}
		}
	}

}