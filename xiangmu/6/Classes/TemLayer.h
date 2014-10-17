#ifndef __TEMLAYER_H_
#define __TEMLAYER_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class TemLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(TemLayer);
protected:
	PageView * pageView;
	void addStoreSelectLayer(int money);
private:
};
#endif