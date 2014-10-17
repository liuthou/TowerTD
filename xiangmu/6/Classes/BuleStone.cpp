#include "BuleStone.h"
#include "HitBodys.h"
bool BuleStone::init(){
	if (!BaseStone::init())
	{
		return false;
	}
    HitBodys::getInstance() -> addToolsBaseControlUserScript(this);
	return true;
}
BuleStone* BuleStone::create(std::string fileName) 
{ 
	BuleStone *pRet = new BuleStone();
	if (pRet && pRet->init()) 
	{ 
		pRet -> setTexture(fileName);
		pRet->autorelease(); 
		return pRet; 
	} 	else 

	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}
std::string BuleStone::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}
