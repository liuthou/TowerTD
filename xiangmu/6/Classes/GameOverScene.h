#ifndef __GAMEOVERSCENE_H_
#define __GAMEOVERSCENE_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
class GameOverScene:public Layer{
protected:
    Size vSize;
	LoadingBar * pb_pb;
public:
    static int scoreMoveLengthPart;
	void onEnter();
	void addjson();
	void addBackground();
	virtual bool init();
	CREATE_FUNC(GameOverScene);
	static Scene * createScene(float moveLength);
	void loadingUpdate(float t);
    void addSocre();
};
#endif
