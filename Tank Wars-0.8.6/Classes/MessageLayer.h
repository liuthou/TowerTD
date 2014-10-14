#ifndef __MESSAGELAYER_H
#define __MESSAGELAYER_H
#include "cocos2d.h"
USING_NS_CC;
class MessageLayer:public Layer
{   
	Label *scorelable;
	std::string scorestr;
	int enemycount;
	Label *enemylable;
	std::string enemystr;
	Label *tankHPlable;
	std::string tankHPstr;
	int tankHP;
	~MessageLayer();
public:
	CC_SYNTHESIZE(int,score,Score);
	void onEnter();
	virtual bool init();
	CREATE_FUNC(MessageLayer);
	void reciveEnemyDie(Ref * obj);//接受敌军死亡消息
	void reciveTankHurt(Ref *obg);//接受坦克受伤消息
};
#endif // !__MESSAGELAYER_H
