#pragma once
#include "cocos2d.h"
USING_NS_CC;

class AboutLayer : public Layer{
public:
	CREATE_FUNC(AboutLayer);
protected:
	void addSprite();
	void addMenu(std::string norName, std::string selName, Vec2 menuPos, std::function<void (Ref *)> menuCallback);
	virtual bool init();
protected:
	bool audioFlag;
};

