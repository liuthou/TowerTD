#include "BaseStone.h"
#include "SystemMarcoUtil.h"
#include "HitBodys.h"
bool BaseStone::init(){
	if (!ToolsBaseScript::init())
	{
		return false;
	}
	HitBodys::getInstance()->addToolsBaseControlUserScript(this);
    Size sprite_size = this->getContentSize();

	return true;
    
}
void BaseStone::changeRoleState(int times){
    Size sprite_size = this->getContentSize();
     this->setPosition(Vec2(sprite_size.width/7, STONEHEIGHT * times));
     value = CCRANDOM_0_1()*3 + 1;
     if (value == 1)
     {
         this->setPosition(Vec2(sprite_size.width/7, STONEHEIGHT * times));
     } else
         if (value == 2)
         {
             this->setPosition(Vec2(GET_WINDOWS_SIZE.width - sprite_size.width/7, STONEHEIGHT * times));
         } else
             if (value == 3)
             {
                 this->setPosition(Vec2(GET_WINDOWS_SIZE.width/2, STONEHEIGHT * times));
             }
}