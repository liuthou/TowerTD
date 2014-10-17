//
//  ChooseToolsLayer.h
//  heroJump
//
//  Created by mazhai on 14-9-23.
//
//

#ifndef __heroJump__ChooseToolsLayer__
#define __heroJump__ChooseToolsLayer__

#include <iostream>
#include <cocos2d.h>
#include "UseToolsBaseSprite.h"
#include "ActionHelper.h"
#include "SkillButton.h"
#define OPACITY_HIGHT 255
#define OPACITY_NOMAL 255/3
USING_NS_CC;
class ChooseToolsLayer:public Layer {
private:
    Vector<UseToolsBaseSprite*> vuts;
	bool _bIsChooseTool;
	NOW_USE_TYPE selectMenuItem;
    SkillButton* mSkillButton;
public:
    virtual bool init();
    CREATE_FUNC(ChooseToolsLayer);
    virtual void addUseToolsBaseSprite(UseToolsBaseSprite* utbs);
	void strengthenBright(Ref * sender);

	MenuItemSprite * sp_item;
	MenuItemSprite * mood_item;
	Menu *sp_menu;
	Menu * mood_menu;
	std::vector<MenuItem *>itemVector;

	NOW_USE_TYPE getNowMenuItem();
    SkillButton* getSkillButton(){
        return this -> mSkillButton;
    }
};
#endif /* defined(__heroJump__ChooseToolsLayer__) */
