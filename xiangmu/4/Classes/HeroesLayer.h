#ifndef __HEROESLAYER__
#define __HEROESLAYER__

#include "cocos2d.h"
#include "PetWolf.h"
class BaseHeroes;
class BasePet;

USING_NS_CC;

class HeroesLayer : public cocos2d::Layer
{
private:
	CC_SYNTHESIZE(bool, may, May);
	CC_SYNTHESIZE(std::string,_heroFileName,HeroFileName);
	PetWolf* pet;
	BaseHeroes * hero;
	//创建主角
	void createHeroes(std::string fileName);
	void createPet();
	//两个点
	Vec2 Vbegan_1;
	Vec2 Vbegan_2;
	Vec2 Vmin;
	Vec2 Vend;
	int flag;
	float xy_cut;
	void startTime(float t);
	virtual void onEnter();
public:

    int touchTime;
	
    virtual bool init(std::string fileName);          //init()方法也要加参数

	static HeroesLayer * create(std::string fileName); //重写creat方法

//	~HeroesLayer();

	void setHeroDie();
	void setTouchesStop(bool);

};

#endif // __HELLOWORLD_SCENE_H__
