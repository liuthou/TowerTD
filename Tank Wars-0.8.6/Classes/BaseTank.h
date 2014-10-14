#ifndef __BASETANK_H
#define __BASETANK_H
#include "cocos2d.h"
using namespace cocos2d;
//坦克移动状态的枚举
enum moverect{
	Up,
	Right,
	Down,
	Left,
	Stop
};
class BaseTank:public Sprite{
protected:
	int speed;//移动时的间距
	//获得下一帧的坐标
	Vec2& getNextFramePostion();
	//坦克产生时的闪烁动画
	virtual void BlinkAnimation();
	//坦克死亡动画
	virtual void dieAnimation();
	//播放移动音乐,只在主坦克中实现
	virtual void playMoveEffect()=0;
public:
	CC_SYNTHESIZE_READONLY(int,score,score);
	CC_SYNTHESIZE(int,hp,Hp);//血量
	CC_SYNTHESIZE(bool,isstop,isStop)//是否是停止状态
	CC_SYNTHESIZE(bool,isdie,ISdie);//是否死亡
	virtual void hurt(int hp);//受伤当前hp-子弹攻击力
	virtual void move(float t);//根据枚举状态选择移动方向
	virtual bool boundingBox(Vec2 position);//移动后碰撞检测
	virtual bool initWithSpriteFrameName(std::string name,int hp,int speed);
	CC_SYNTHESIZE(moverect,state,State);//获取其枚举状态的方法
	virtual void fire()=0;//开火方法
	virtual  void runAnimate()=0;//运行其动画
	Rect& getNextFrameBoundingBox();//下一帧位置与地图的检测
};
#endif