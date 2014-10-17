#pragma  once

#include "AppMacro.h"
#include "BaseLayer.h"

/* 
摇杆控制层

拥有四个方向按钮，每个方向按钮都发送同一个消息，但是指定一个方向参数

*/
class ControlLayer : public BaseLayer {
private:
	Button *m_leftBtn;
	Button *m_rightBtn;
	Button *m_upBtn;
	Button *m_downBtn;
private:
	/*
	发送移动指令 PLAYER_MOVE

	#参数1 direction是移动方向
	*/
	void sendMovementOrder(MovementDirection direction);

	/*
	用闭包完成四个按钮监听，监听里决定发送哪个移动指令
	*/
	void initUIandRigsterHandlers();
protected:
	virtual bool init();
public:
	CREATE_FUNC(ControlLayer);

	void reset();

	void start();

	void stop();	
};