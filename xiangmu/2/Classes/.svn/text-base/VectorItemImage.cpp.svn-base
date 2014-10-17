
#include "VectorItemImage.h"

//×Óµ¯ÈÝÆ÷µ¥Àý
VectorItemImage * VectorItemImage::instance = nullptr;
VectorItemImage * VectorItemImage::getInstance(){
	if (!instance) {
		instance = new VectorItemImage();

	}
	return instance;
}
void VectorItemImage::addVectorItemImage(MenuItemImage * mit){
	itemImageVector.pushBack(mit);
}
void VectorItemImage::deleteVectorItemImage(MenuItemImage * mit){
	for (int i = 0; i < itemImageVector.size(); i++) {
		auto item = itemImageVector.at(i);
		if (item == mit) {
			itemImageVector.eraseObject(mit);

		}
	}

}
void VectorItemImage::reset(){
	itemImageVector.clear();
}