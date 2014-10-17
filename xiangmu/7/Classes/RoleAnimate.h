#ifndef __ROLEANIMATE_H
#define __ROLEANIMATE_H
#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class RoleAnimate
{
private:
	RoleAnimate(){};
	RoleAnimate(const RoleAnimate * rani){};
	RoleAnimate operator=(const RoleAnimate * rani){
		return rani;
	}
protected:
	static RoleAnimate * instance;

public:
	Animate * createAmt(const char * fileName, int imagesCount, float HZ, int loop);
	static RoleAnimate * getinstance();
	Animate * getAttackAnimate(int type, int direction);
	Animate * createAnimate(std::vector<std::string> fileName,float HZ,signed int times);
	Animate * getMoveRightAnimate(int m_type,int imageMount,float HZ,int Times);
	Animate * getMoveLeftAnimate(int m_type,int imageMount,float HZ,int Times);
	Animate * getBornAnimate(int m_type,int imageMount,float HZ,int Times);



	Animate *moveLeftAnimate();
	Animate *moveRightAnimate();

	Animate *dieLeftAnimate();
	Animate *dieRightAnimate();

	Animate *attrackLeftAnimate();
	Animate *attrackRightAnimate();

	Animate *iceSwordLeftAniamte();
	Animate *iceSwordRightAnimate();
	Animate *iceBlink();
	Animate *HIdingAnimate();
	Animate *SnackSkill();



};
#endif // !__ANIMATELAYER_H
