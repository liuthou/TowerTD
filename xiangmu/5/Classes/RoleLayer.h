#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class Role;

class RoleLayer : public Layer{
public:
	CREATE_FUNC(RoleLayer);
	Role * getRole();
protected:
	//音效开关
	int audioFlag;
	Role * role;
	//低血量警示标示
	Sprite * lowBloodWarning;
	//进度条
	LoadingBar * m_hpLoading;
	//心跳音效返回值
	int soundId;
protected:
	//改变血条长度
	void changeHpLoadingBar(float t);
	//增加血条
	void addHpLoadingBar();
	virtual bool init();
};