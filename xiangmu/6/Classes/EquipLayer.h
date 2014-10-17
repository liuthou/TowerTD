#ifndef __EQUIPLAYER_H_
#define __EQUIPLAYER_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class EquipLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(EquipLayer);
protected:
	void addStoreSelectLayer(int money);
	PageView * pageView;
private:
};
#endif