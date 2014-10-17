
#ifndef __Dota_Legend__GameSceneBG__
#define __Dota_Legend__GameSceneBG__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class GameSceneBG :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameSceneBG);
protected:
	//加入战役按钮
	void addCampaignMenu();
	//点击战役按钮触发的事件
	void campaignIncident(Ref * sender);
	Sprite * dealWithBG(std::string name);
	//三个图片的原始坐标
	float longBG_begin_x;
	float mediumBG_begin_x;
	float closeBG_begin_x;
	float menuBG_begin_x;
	//触摸的开始坐标跟结束坐标
	float touch_begin_x;
	float touch_end_x;
	//图片缩放比例
	float zoomOutX;
	float zoomOutY;

};
#endif /* defined(__Dota_Legend__GameSceneBG__) */
