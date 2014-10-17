#include "StoneLayer.h"
#include "BuleStone.h"
bool StoneLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	times = 1;
	for (int i = 0 ; i < 1; i++)
	{
		times++;
		BuleStone * spriteStone = BuleStone::create("bulestoner.png");
		spriteStone->changeRoleState(times);
		spriteStone->setScale(0.3);
		JUMP_LOG("%d",1);
		this->addChild(spriteStone);
	}
	return true;
   }
void StoneLayer::onEnter(){
	Layer::onEnter();
	
}