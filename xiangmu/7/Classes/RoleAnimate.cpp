#include "RoleAnimate.h"
RoleAnimate * RoleAnimate::instance = nullptr;
RoleAnimate * RoleAnimate::getinstance(){
	if(!instance){
		instance = new RoleAnimate();
	}
	return instance;
}
Animate * RoleAnimate::createAnimate(std::vector<std::string> fileName,float HZ,signed int times){
	Animation * ani = Animation::create();
	for(auto it = fileName.begin();it != fileName.end();it++){
		SpriteFrame * sf = SpriteFrameCache::getInstance()->getSpriteFrameByName((*it));
		ani->addSpriteFrame(sf);
	}
	ani->setDelayPerUnit(HZ);
	ani->setLoops(times);
	Animate * animate = Animate::create(ani);
	return animate;
}

Animate * RoleAnimate::getMoveRightAnimate(int m_type,int imageMount,float HZ,int Times){
	std::vector<std::string>fileNames;
	for(int i = 1;i <= imageMount;i++){
		std::string fileName = StringUtils::format("enemy%dMoveRight_0%d.png",m_type,i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,HZ,Times);
	return ani;
}

Animate * RoleAnimate::getMoveLeftAnimate(int m_type,int imageMount,float HZ,int Times){
	std::vector<std::string>fileNames;
	for(int i = 1;i <= imageMount;i++){
		std::string fileName = StringUtils::format("enemy%dMoveLeft_0%d.png",m_type,i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,HZ,Times);
	return ani;
}

Animate * RoleAnimate::getBornAnimate(int m_type,int imageMount,float HZ,int Times){
	std::vector<std::string>fileNames;
	for(int i = 1;i <= imageMount;i++){
		std::string fileName = StringUtils::format("enemy%dBorn_0%d.png",m_type,i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,HZ,Times);
	return ani;
}

Animate * RoleAnimate::getAttackAnimate(int type, int direction){
	if(direction == 1){
		std::vector<std::string>fileNames;
		for (int i = 1; i < 5; i++){
			auto filename = StringUtils::format("enemy%dAttackLeft_0%d.png",type,i);
			fileNames.push_back(filename);
		}
		auto ani = createAnimate(fileNames,0.25,1);
		return ani;
	}else{
		std::vector<std::string>fileNames;
		for (int i = 1; i < 5; i++){
			auto filename = StringUtils::format("enemy%dAttackRight_0%d.png",type,i);
			fileNames.push_back(filename);
		}
		auto ani = createAnimate(fileNames,0.25,1);
		return ani;
	}
}

Animate * RoleAnimate::createAmt(const char * fileName, int imagesCount, float HZ, int loop){
	auto ani = Animation::create();
	for (int i = 1; i <= imagesCount; i++){
		SpriteFrame * sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(fileName,i));
		ani->addSpriteFrame(sf);
	}
	ani->setDelayPerUnit(HZ);
	ani->setLoops(loop);
	Animate * amt = Animate::create(ani);
	return amt;
}

Animate *RoleAnimate::moveLeftAnimate(){
	std::vector<std::string>fileNames;
	for (int  i = 1;i <= 7;i++){
		std::string fileName = StringUtils::format("SnackMoveLeft%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,-1);
	return ani;
}

Animate *RoleAnimate::moveRightAnimate(){
	std::vector<std::string>fileNames;
	for(int i = 1;i <= 7;i++){
		std::string fileName = StringUtils::format("SnackMoveRight%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,-1);
	return ani;
}

Animate *RoleAnimate::dieLeftAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 3; i++){
		std::string fileName = StringUtils::format("DieLeft%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,-1);
	return ani;
}

Animate *RoleAnimate::dieRightAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 3; i++){
		std::string fileName = StringUtils::format("DieRight%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,-1);
	return ani;
}

Animate *RoleAnimate::attrackLeftAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 6; i++){
		std::string fileName = StringUtils::format("AttackSkillLeft%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.1,1);
	return ani;
}

Animate *RoleAnimate::attrackRightAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 6; i++){
		std::string fileName = StringUtils::format("AttackSkillRight%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.1,1);
	return ani;
}

Animate * RoleAnimate::iceSwordLeftAniamte(){
	std::vector<std::string>fileNames;
	for (int i = 1;i <= 4;i++){
		std::string fileName = StringUtils::format("IceSwordLeft%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,2);
	return ani;
}

Animate * RoleAnimate::iceSwordRightAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 4; i++){
		std::string fileName = StringUtils::format("IceSwordRight%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,2);
	return ani;
}

Animate *RoleAnimate::iceBlink(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 4; i++){
		std::string fileName = StringUtils::format("IceSwordRain%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.2,1);
	return ani;
}

Animate *RoleAnimate::HIdingAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 5; i++){
		std::string fileName = StringUtils::format("Hiding%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = createAnimate(fileNames,0.1,1);
	return ani;
}

Animate *RoleAnimate::SnackSkill(){
	std::vector<std::string>fileNames;
	for (int i = 1; i <= 6; i++){
		std::string fileName = StringUtils::format("SnackSkill%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.2,2);
	return ani;
}