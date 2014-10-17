#ifndef _MAINROLEAMRATUE_H
#define _MAINROLEAMRATUE_H

#include "cocos2d.h"

using namespace cocos2d;
class MainRoleAmratue :Layer
{
public:
	static Scene * createScene();
	CREATE_FUNC(MainRoleAmratue);
protected:
	void update(float t);
	void callBack(Ref * sender);
	void callBackSaveGame(Ref * sender);
	void callBackEndGame(Ref * sender);
	virtual bool init();
private:
};
#endif