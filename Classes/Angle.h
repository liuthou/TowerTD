#ifndef __ANGLE_H
#define __ANGLE_H
#include "cocos2d.h"
USING_NS_CC;

class Angle: public Layer
{
public:

	
	virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
	void onDraw();
	
	virtual bool init();
	CREATE_FUNC(Angle);
protected:
private:
	CustomCommand _command;
};

#endif