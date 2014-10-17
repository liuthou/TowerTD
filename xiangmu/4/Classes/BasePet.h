#ifndef __BASEPET_H_
#define __BASEPET_H_
#include "Conf.h"
class BaseHeroes;
class BasePet:public Sprite
{
private:
protected:
	Vec2 offSet;

	ActionInterval* petFly();
	BaseHeroes* hero;
	CC_SYNTHESIZE(std::string, _fileName, FileName);
	void addFire();
public:

	CC_SYNTHESIZE(float, _petAttack,PetAttack);

	CC_SYNTHESIZE(bool,isMove,IsMove);
	virtual void onEnter();

	virtual bool initWithSpriteFrameName(std::string fileName,Vec2 position);
	//蓄力完成动作
	virtual void powerOver() = 0;
	//蓄力释放动作 
	virtual void powerRelease() = 0;

	virtual ~BasePet();
	void update(float t);
	void petMove(Vec2 position);

};
#endif