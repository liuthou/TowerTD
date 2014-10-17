#ifndef __BossFour_H_

#define __BossFour_H_

#include "cocos2d.h"
#include "BaseEnemy.h"

using namespace cocos2d;

enum direction{
	MOVELEFT = 1,
	MOVERIGHT
};

class BossFour:public BaseEnemy{

protected:
	int m_dir;
	
	bool m_bossIsHurt;
	
	int hp;

	bool isDie;

public:

	virtual bool init();
	CREATE_FUNC(BossFour);

	void callEnemy(Vec2 pos,int speed,int tyoe,Size body,std::string name,int ai);		//’––°π÷
	void move(float t);   //移动的方法
	void moveLeftAnimate(); //向左移动的腚花
	void moveRightAnimate();	//œÚ”““∆∂Ø∂Øª≠
	
	void bornAnimate(float t);		//≥ˆ…˙∂Øª≠
	void hurtAnimate();		// ‹…À∂Øª≠
	void dieAnimate();		//À¿Õˆ∂Øª≠

	void hurt();				// ‹…À∑Ω∑®
	void die();			//À¿Õˆ∑Ω∑®
	void _update(float t );

	bool getState();

	//ª«Ú∫Õ Bossµƒ≈ˆ◊≤ºÏ≤‚
	void fireBallPKBoss(float t);

};




#endif