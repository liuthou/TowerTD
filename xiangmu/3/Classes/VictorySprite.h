#ifndef __VictorSprite_H
#define __VictorSprite_H
#include "cocos2d.h"
USING_NS_CC;
class VirctoSprite :public Sprite{
public:
	virtual bool init(int hp,int needfile,float selfrecoverspeed);
	static VirctoSprite*create(int hp,int needfile,float selfrecoverspeed=0.5);
	CC_SYNTHESIZE(int,fullhp,Fullhp);//总血量
	CC_SYNTHESIZE(int,curhp,Curhp);//当前血量
	CC_SYNTHESIZE(int,receivedfile,ReceivedFile);//接受到的文件个数
	CC_SYNTHESIZE(int,needfile,Needfile);//需要多少文件达成胜利条件
	CC_SYNTHESIZE(float,selfrecoverspeed,SelfRecoverSpeed);
	virtual void onEnter();
	//接受文件
	void increaseprogress();
	//受到伤害
	int hurt(int attackValue);
	void setProgressFunc(std::function<void(float)> gameprogress);
	//满血血量,当前血量
	void setHurtEffectFunc(std::function<void(int fullhp,int curhp)> hurteffect);
	//失败调用函数
	void setLoseFunc(std::function<void()>losefunc);
	//成功调用函数
	void setWinFunc(std::function<void()>winfunc);
	virtual void update(float t);
protected:
	//自动回血
	void selfRecover(float dt);
	std::function<void(float)> gameprogress;//函数对象用来回调进度条的增长函数
	std::function<void(int,int)> hurteffect;
	std::function<void()> losefunc;
	std::function<void()>winfunc;
	Animate*normalAni;
	Animate*hurtAni;
	bool getprogressfuncbind;//函数是否绑定成功
	
	VirctoSprite(){
		curhp = 0;
		fullhp = 0;
		needfile =0;
		getprogressfuncbind= false;
	}
};



#endif  