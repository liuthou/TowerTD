
#ifndef __Dota_Legend__VectorItemImage__
#define __Dota_Legend__VectorItemImage__

#include <stdio.h>
#include <cocos2d.h>
using namespace cocos2d;

//²Ëµ¥ÈÝÆ÷´æ´¢µ¥Àý
class VectorItemImage{
private:
	VectorItemImage(){}
	VectorItemImage(const VectorItemImage & b){}
	VectorItemImage operator=(const VectorItemImage & b){
		return b;
	}

protected:
	static VectorItemImage * instance;
public:
	CC_SYNTHESIZE_PASS_BY_REF(Vector<MenuItemImage *>, itemImageVector, ItemImageVector);
	static VectorItemImage * getInstance();
	void addVectorItemImage(MenuItemImage * mit);
	void deleteVectorItemImage(MenuItemImage * mit);
	void reset();
};

#endif /* defined(__Dota_Legend__VectorItemImage__) */
