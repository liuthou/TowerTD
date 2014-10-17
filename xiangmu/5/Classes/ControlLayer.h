#ifndef __CONTROLLAYER_H_
#define __CONTROLLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class Role;

class ControlLayer : public Layer{
public:
	CREATE_FUNC(ControlLayer);
protected:
	virtual bool init();
	//增加触摸事件
	void addTouch();
	//添加重力感应
	void addGravity();
private:
	void onEnter();
	Role * role;
	//判断主角是否在正常跑的状态
	bool isNormal;

};

#endif // !__CONTROLLAYER_H_
