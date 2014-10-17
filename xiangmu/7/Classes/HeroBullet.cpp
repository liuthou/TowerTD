#include "HeroBullet.h"
#include "GameScene.h"

bool HeroBullet::init(std::string fileName,Vec2 position)
{
	if (!BaseBullet::init(fileName))
	{
		return false;
	}

	this->setPosition(position);		//设置子弹的位置
	//获取当前运行的场景
	GameScene * scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	//获取英雄层
	auto layer = scene->getHeroLayer();
	//将子弹加入到 英雄层中
	layer->addChild(this);
	//子弹加入到弹夹中
	AllVectors::getInstance()->addHeroBullet(this);
	
	return true;

}

HeroBullet *HeroBullet::create(std::string fileName,Vec2 position)
{
	HeroBullet * herobullet = new HeroBullet();

	if(herobullet && herobullet->init(fileName,position)){
		herobullet->autorelease();
		return herobullet;
	}
	CC_SAFE_DELETE(herobullet);
	return nullptr;
}
void HeroBullet::move(int direction){
	if(direction == 1){
		auto moveright = MoveBy::create(m_range/BULLETSPEED,Vec2(m_range,0));
		std::vector<std::string>fileNames;
		for (int i =1;i <= 5;i++){
			std::string filename = StringUtils::format("RightBullet%d.png",i);
			fileNames.push_back(filename);
		}
		auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.1,2);
		auto swa = Spawn::create(ani,moveright,nullptr);
		auto cf = CCCallFunc::create([=](){
			this->die();
		});
		this->runAction(Sequence::create(swa,cf,nullptr));
	}else{
		auto moveleft = MoveBy::create(m_range/BULLETSPEED,Vec2(-m_range,0));
		std::vector<std::string>fileNames;
		for (int i =1;i <= 5;i++){
			std::string filename = StringUtils::format("LeftBullet%d.png",i);
			fileNames.push_back(filename);
		}
		
		auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.1,2);
		auto swa = Spawn::create(moveleft,ani,nullptr);
		auto cf = CCCallFunc::create([=](){
			this->die();
		});

		this->runAction(Sequence::create(swa,cf,nullptr));
	}
}