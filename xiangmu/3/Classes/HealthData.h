#ifndef __HealthData_H
#define __HealthData_H
#include "cocos2d.h"
USING_NS_CC;
enum DirectionData{
	DOWNDATA = 0,
	LEFTDATA,
	RIGHTDATA,
	UPDATA,
};

class HealthData:public Sprite{
public:
	bool init(std::string filename,int speed,int hp);
	static HealthData*create(std::string filename,int speed,int hp);
	CC_SYNTHESIZE(int, hp,Hp);
	CC_SYNTHESIZE(int,speed,Speed);
	CC_SYNTHESIZE(std::string,fileName,FileName);
	CC_SYNTHESIZE(int,direct,DataDir);
	CC_SYNTHESIZE(bool,isdie,Isdie);
	virtual bool moveUp(float t);
	virtual bool moveDown(float t);
	virtual bool moveLeft(float t);
	virtual bool moveRight(float t);
	bool checkMove(Vec2 newpoint);
	void remove();
	void die();
protected:
	Vector<Animate*> m_animates;
	void dieAnimate(std::string fileName);
	HealthData(){
		hp = 0;
		speed = 0;
	}
};
#endif