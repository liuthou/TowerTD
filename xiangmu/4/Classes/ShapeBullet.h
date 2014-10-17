#ifndef _SHAPEBULLET_H_
#define _SHAPEBULLET_H_

#include "BaseBullet.h"
#define M_PI       3.14159265358979323846
#define ANGLE 15
class ShapeBullet : public BaseBullet{
protected:
	int number;
	Vec2 toPosition;
	int spritenumber;
public:
	virtual bool init(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number);
	//倒数二个参数用来传敌人要发几连发的子弹，最后一个参数是每个子弹的距离角度
	static ShapeBullet *create(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number);

};
#endif