#ifndef __PERSONLAYER_H_
#define __PERSONLAYER_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class PersonLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PersonLayer);
protected:
	PageView * pageView;
private:
};
#endif