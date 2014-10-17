#ifndef __YELLOWTHUNDER_H
#define __YELLOWTHUNDER_H
#include "DoubleThunder.h"
class YellowThunder:public DoubleThunder
{
	void attackAnimate();
public:
	virtual bool init(Vec2 &curpoint);
	static YellowThunder *create(Vec2 curpoint);
};
#endif // !__YELLOWTHUNDER_H
