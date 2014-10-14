#ifndef __SELECTLAYER_H
#define __SELECTLAYER_H
#include "cocos2d.h"
#include "GameBasic.h"
using namespace cocos2d;
class SelectLayer:public Layer{
public:
	virtual bool init();
	CREATE_FUNC(SelectLayer);
	static Scene * createScene();
private:
	Vec2 layerPos;
	int layerNum;	 
	Layer *layer;
	Size size;
	Vector<MenuItemToggle*> toggles;
protected:
	void pageChange(Ref* pSender);
	void changeToggle();
};
#endif