#ifndef __BASEBULLET_H
#define __BASEBULLET_H
#include "cocos2d.h"
#define YIDONGSUDU 200
#define BULLETATTACK 50
using namespace cocos2d;
enum moverect;
class Basebullet:public Sprite{
public:
	CC_SYNTHESIZE_READONLY(int,Attack,ATTACK);//子弹的攻击力的读取
	static Basebullet* Createbullet(Vec2 position,moverect STATE);
	virtual bool initWithTank(Vec2 position,moverect STATE);
	virtual void move();//子弹的移动方法
	virtual void remove();//将移出屏幕的子弹弄死
	CC_SYNTHESIZE(bool,isdie,ISDIE);//读取子弹是否死亡
private:
	int sid;
	moverect STATE;//枚举状态
	Size vsize;//屏幕尺寸
	Vec2 position;//初始位置
};
#endif