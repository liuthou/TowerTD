#include "RoleLayer.h"
#include "Role.h"
#include "GameData.h"
#include "DataXML.h"

bool RoleLayer::init(){
	if (!Layer::init())
	{
		return false;
	}

	soundId = 0;
	lowBloodWarning = nullptr;
	audioFlag = DataXML::getInstence()->getInitialValue("sound");

	role = Role::create();
	role->setPosition(ROLE_POSITION_X, ROLE_POSITION_Y);
	role->setScale(0.7);
	this->addChild(role);

	addHpLoadingBar();
	this->schedule(schedule_selector(RoleLayer::changeHpLoadingBar));

	return true;
}

//添加动态血条
void RoleLayer::addHpLoadingBar(){
	Widget * uiLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("blod/Blod.ExportJson");
	auto bloodImage = uiLayer->getChildByTag(4);
	m_hpLoading = (LoadingBar *)bloodImage->getChildByTag(5);
	uiLayer->setPosition(Vec2(VISIBLE_SIZE.width/4, -100));
	this->addChild(uiLayer);
}
//改变血条长度
void RoleLayer::changeHpLoadingBar(float t){
	float roleHp = role->getM_hp();
	float hpPercent = roleHp * 100 / ROLE_ALL_HP;
	if (hpPercent < 0.0f)
	{
		hpPercent = 0.0f;
	}
	m_hpLoading->setPercent(hpPercent);
	if (hpPercent == 0.0f)
	{
		this->unschedule(schedule_selector(RoleLayer::changeHpLoadingBar));
	}
	if (roleHp <= 0.3 * ROLE_ALL_HP)
	{
		if (lowBloodWarning == nullptr)
		{
			if (audioFlag)
			{
				soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("heartbeat.mp3", true);
			}
			lowBloodWarning = Sprite::createWithSpriteFrameName(LOW_BLOOD_WARNING);
			lowBloodWarning->setPosition(210,75);
			lowBloodWarning->runAction(RepeatForever::create(Blink::create(1, 2)));
			m_hpLoading->runAction(RepeatForever::create(Blink::create(1, 2)));
			this->addChild(lowBloodWarning);
		}
	}
	if (roleHp >= 0.3 * ROLE_ALL_HP || roleHp <= 0)
	{
		if (lowBloodWarning != nullptr)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(soundId);
			lowBloodWarning->removeFromParentAndCleanup(true);
			m_hpLoading->stopAllActions();
			m_hpLoading->setVisible(true);
			lowBloodWarning = nullptr;
		}
	}
}

Role * RoleLayer::getRole(){
	return role;
}

