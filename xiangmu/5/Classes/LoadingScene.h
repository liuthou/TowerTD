#ifndef __LOADINGSCENE_H_
#define __LOADINGSCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Layer{
public:
	CREATE_FUNC(LoadingScene);
	static Scene * createScene();
protected:
	//Load picture matter
	void loadPicture();
	//Load music matter
	void loadMusic();
	//Set up Callback function
	void plistImageCallback(Texture2D * text);
	virtual bool init();
protected:
	int count;
};

#endif // !__LOADINGSCENE_H_
