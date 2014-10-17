#ifndef __MENUITEMLAYER_H_
#define __MENUITEMLAYER_H_
#include "cocos2d.h"

using namespace cocos2d;

class MenuItemLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MenuItemLayer);
protected:
	void onEnter();
	void addMenu();
	void onCallback(Ref * sender);
	void addPersonLayer(Ref * sender);
	void addTemLayer(Ref * sender);
	void addEquipLayer(Ref * sender);
	LayerMultiplex * layerVector;
private:
};
#endif