#ifndef  _SHAPEFUNC_H
#define  _SHAPEFUNC_H
#include "ShapeBullet.h"
class shapeFunc : public ShapeBullet {
	Vec2 vfromPostion;
public:
	struct Increment
	{
		float incrementX;
		float incrementY;
		Increment(float incrementX, float incrementY)
		{
			this->incrementX = incrementX;
			this->incrementY = incrementY;
		}
	};
	std::vector<Increment>own;//存储每隔精灵的线段长度

	//void sprite_create(float speed, Vec2 fromPosition, Vec2 toPosition, int number);
	virtual void update(float t);
	//根据每个精灵来创造位置
	void halfcicle_bullet(float speed, Vec2 fromPosition, Vec2 toPosition, int number);
	virtual bool init(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number);
	//倒数二个参数用来传敌人要发几连发的子弹，最后一个参数是每个子弹的距离角度
	static shapeFunc *create(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number);

	virtual void onEnter();
};
#endif