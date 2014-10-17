#ifndef _VICTORYANIMATION_H_
#define _VICTORYANIMATION_H_

#include "cocos2d.h"
#include <cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>

#include "ProcessControl.h"
#include "Poker.h"
using namespace cocostudio;
using namespace ui;
using namespace cocos2d;
using namespace TexasPoker;

class VictoryAnimation : public Layer{
public:
	void play(TexasPoker::PokerMethod victor);
    
	//金刚动画
	void jgAnimation();
    
	//葫芦动画
	void hlAnimation();
    
	//同花顺想动画
	void thsAnimation();
    
	//皇家同花顺动画
	void hjthsAnimation();

    void initUI();
public:
	TexasPoker::PokerMethod victor;
    CREATE_FUNC(VictoryAnimation);
    
private:
    virtual bool init();
    
    void End();
protected:
    Armature * amt;
	std::function<void()> endFunc;
};

#endif