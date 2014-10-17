#ifndef  __TOUCHDIR_R_
#define  __TOUCHDIR_R_

#include "cocos2d.h"
using namespace cocos2d;

enum Driection
{
	LEFT,
	RIGHT,
	JUMP,
	NEARSKILL,
	LEFTFARSKILL,
	RIGHTFARSKILL,
	BIGSKILL,
	ATTACK,
	STOP
};

class TouchDir : public Ref
{
private:
	Vec2  _beginPoint;
	Vec2  _endPoint;
public:
	//判断角度并返回方向
	Driection judgeDriection();
	virtual bool init(Vec2 beginPoint, Vec2 endPoint);
	static TouchDir * create(Vec2 beginPoint, Vec2 endPoint);
};

#endif