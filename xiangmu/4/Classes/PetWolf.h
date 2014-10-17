#ifndef __PETWOLF_H_
#define __PETWOLF_H_
#include "Conf.h"
#include "BasePet.h"
class PetWolf:public BasePet
{
private:
	CC_SYNTHESIZE(bool, isMay, IsMay);
	CC_SYNTHESIZE(Vec2,_heroVec2,HeroVec2);
	void heroPowerOver();
	void exePetPowerRelease();
	Spawn* parallelAction();
	Sequence* serialAction();
	Spawn* backBigen();
	Vec2 bigenPoint;
public:

	virtual bool initWithSpriteFrameName(Vec2 position);

	static PetWolf * create(Vec2 position);
	//蓄力完成动作
	virtual void powerOver();
	//蓄力释放动作 
	virtual void powerRelease();

	virtual void onEnter();

	virtual ~PetWolf();

	void changeIsMove();
	void changeIsMay();
	void stopPowerOver();
	void removePet();
	void die();
};
#endif