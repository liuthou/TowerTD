#ifndef __AUDIOUTIL_H_
#define __AUDIOUTIL_H_
#include "cocos2d.h"
using namespace cocos2d;
class AudioUtil:public Node
{
public:
	static AudioUtil * getInstance();
	//destroy instance
	static void destroyInstance();
	//play backGroundMusic
	void playBackgroundSound(const char * backGroundName);
	//play effect
	void playEffect(const char * effectName);
	//set bool backGround
	void setIsBackGround(const bool &isPlay);
	bool getIsBackGround();
	void setIsEffectPlay(const bool &isPlay);
	bool getIsEffectPlay();
	//stop backGroundMusic
	void stopBackGroundPlay();
	void stopEffectPlay();

protected:
	bool isBackGroundPlay ;
	bool isEffectPlay;
	//CC_SYNTHESIZE_PASS_BY_REF(bool, isEffectPlay, IsEffectPlay);
	static AudioUtil * instance;
	std::string backGroundName;
	std::string effectName;
private:
	AudioUtil();
	virtual ~AudioUtil();
	AudioUtil(const AudioUtil & audio){}
	
};
#endif