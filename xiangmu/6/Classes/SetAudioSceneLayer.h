#ifndef __SETAUDIOSCENELAYER_H_
#define __SETAUDIOSCENELAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class SetAudioSceneLayer:public Layer
{
public:
	virtual bool init();
	static Scene * createScene();
	CREATE_FUNC(SetAudioSceneLayer);
	void onEnter();
	//control play music item
	void menuItemPlayMusic();
	//set bool play backGroundMusic
	void audioBackGroundMusic(Ref * sender);
	//set bool play effectMusic
	void audioEffectMusic(Ref * sender);
	//return setting scene
	void onCallBack(Ref * sender);
protected:
private:
};
#endif