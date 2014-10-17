/************************************************************************/
/* 
	m_map
	m_object
	m_
*/
/************************************************************************/
#ifndef _MAPLAYER_H
#define _MAPLAYER_H
#include "cocos2d.h"
using namespace cocos2d;

class MapLayer:public Layer
{
protected:
	TMXTiledMap * m_map;
	TMXObjectGroup * m_object;
public:
	virtual bool init();
	CREATE_FUNC(MapLayer);


	Size visSize;
	void add(float t);
	void addGround1(int posX,int posY,int width);		//添加横地板
	void addGround2(int posX,int posY,int wid,int length);		//添加竖地板


	void finishAmt();

};
#endif