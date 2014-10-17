#ifndef __HELPLAYER_H_
#define __HELPLAYER_H_
#include <cocos2d.h>
using namespace cocos2d;

class HelpLayer : public Layer
{

public:
	virtual bool init();
	CREATE_FUNC(HelpLayer);
private:
	void addLayer();
	void addLayer2();
protected:
	int audioFlag;
};
#endif