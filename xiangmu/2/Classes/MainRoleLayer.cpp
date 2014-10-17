#include "MainRoleLayer.h"
#include "VectorItemImage.h"
#include "SelectRole.h"
#include "SFRole.h"
#include "HpLoadingbar.h"
#include "NecRole.h"

bool MainRoleLayer::init(){
	if(!Layer::init()){
		return false;
	}
	num = 0;
	addMainRole();
	return true;
}
void MainRoleLayer::addMainRole(){
	for(int i = 0;i < VectorItemImage::getInstance()->getItemImageVector().size();i++){
		auto image = VectorItemImage::getInstance()->getItemImageVector().at(i);
		std::string nameXml = image->getName();
		if (num == 0)
		{
			SFRole *mainRole = SFRole::create(nameXml);
			SelectRole::getInstence()->addRoleArmature(mainRole);
			if (num == 0){
				mainRole->setPosition(0, 320);
			}
			else if (num == 1){
				mainRole->setPosition(-100, 360);
			}
			else if (num == 2){
				mainRole->setPosition(-100, 280);
			}
			mainRole->setArmaturestatic(moveStatic);
			mainRole->setZOrder(100);
			this->addChild(mainRole);
		}
		else if (num ==1)
		{
			NECRole *mainRole = NECRole::create(nameXml);
			SelectRole::getInstence()->addRoleArmature(mainRole);
			if (num == 0){
				mainRole->setPosition(0, 320);
				
			}
			else if (num == 1){
				mainRole->setPosition(-100, 360);
			

			}
			else if (num == 2){
				mainRole->setPosition(-100, 280);
				

			}
			
			mainRole->setArmaturestatic(moveStatic);
			this->addChild(mainRole);
		}
		
		
		num++;
		//////////////////////////////////////////////////////////////////////////
 		auto hploadingbar = HpLoadingbar::create(SelectRole::getInstence()->getRoleArmatures().at(i));
		SelectRole::getInstence()->addHplayer(hploadingbar);
 		this->addChild(hploadingbar);
	
		hploadingbar->setPosition(Vec2(134 * i + 76, 0));
	}
	num = 0;
}