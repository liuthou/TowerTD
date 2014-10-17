#include "BaseTool.h"
#include "AllVectors.h"

bool BaseTool::initWithSpriteFrameName(Vec2 position){
	std::string fileName = "";
	int rate1 = CCRANDOM_0_1() > 0.7 ? 1 : 2;
	if (rate1 == 1){
		int rate2 = CCRANDOM_0_1() * 100;
		if (rate2 >= 0 && rate2 <= 23){
			m_type = ADDSPEED;
			fileName = "speedUp.png";
		}else if (rate2 > 23 && rate2 <= 54){
			m_type = ADDBLOOD;
			fileName = "hpUp.png";
		}else if (rate2 > 54 && rate2 <= 77){
			m_type = ADDRANGE;
			fileName = "rangeUp.png";
		}else if (rate2 > 77 && rate2 <= 100){
			m_type = ADDATTACK;
			fileName = "fireUp.png";
		}
	}else if (rate1 == 2){
		m_type = ADDSCORE;
		int rate3 = CCRANDOM_0_1()*100;
		if (rate3 >= 0 && rate3 <= 5){
			m_score = 1;
			fileName = "1.png";
		}else if (rate3 > 5 && rate3 <= 30){
			m_score = 100;
			fileName = "100.png";
		}else if (rate3 > 30 && rate3 <= 55){
			m_score = 200;
			fileName = "200.png";
		}else if (rate3 > 55 && rate3 <= 75){
			m_score = 500;
			fileName = "500.png";
		}else if (rate3 > 75 && rate3 <= 90){
			m_score = 1000;
			fileName = "1000.png";
		}else if (rate3 > 90 && rate3 <= 100){
			m_score = 10000;
			fileName = "10000.png";
		}
	}
	if (!Sprite::initWithSpriteFrameName(fileName)){
		return false;
	}


	this->setScale(0.7);
	this->setPosition(position);
	AllVectors::getInstance()->addTool(this);
	auto jb = JumpBy::create(1,Vec2(0,0),100,1);
	auto rb = RotateBy::create(5,0);
	auto cf = CallFunc::create([=](){this->remove();});
	auto seq = Sequence::create(jb,rb,cf,NULL);
	this->runAction(seq);

	return true;

}

BaseTool *BaseTool::create(Vec2 position){
	BaseTool *base = new BaseTool();
	if (base && base->initWithSpriteFrameName(position))
	{
		base->autorelease();
		return base;
	}

	CC_SAFE_DELETE(base);
	return NULL;

}

void BaseTool::remove(){				//移除道具
	this->removeFromParentAndCleanup(true);
	AllVectors::getInstance()->deleteTool(this);

}

// void BaseTool::runAnimation(std ::string fileName){			//运行动画
// 	std::vector<std::string> toolVec;
// 	for (int i = 1;i <= 4;i++)
// 	{
// 	std::string sp = StringUtils::format("%s%d.png",fileName,i);
// 	toolVec.push_back(sp);
// 	}
// 
// 	auto ani = RoleAnimate::getinstance()->createAnimate(toolVec,0.2,3);
// 
// 	this->runAction(ani);
// 
// }
