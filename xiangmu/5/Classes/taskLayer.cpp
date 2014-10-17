#include "taskLayer.h"
#include "DataXML.h"
#include "GameData.h"
#include "BaseSprite.h"
#include "SimpleAudioEngine.h"

bool taskLayer::init() {

	if (!Layer::init())
	{
		return false;
	}
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	allCondition["multi2long"] =0;
	allCondition["useablebloodbutton"] = 0;
	allCondition["plus50"] = 0;
	allCondition["multi2short"] = 0;
	allCondition["blood_drop"] = 0;
	allCondition["beartrap"] = 0;
	allCondition["campfire"] = 0;
	allCondition["plaster"] = 0;
	allCondition["blade_low"] = 0;
	allCondition["e_fence"] = 0;
	count = 0;

	addSprite();
 	showTask();
 	addTool();
	

	NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(taskLayer::testMessage),"task",NULL);
	return true;
}

void taskLayer::onEnter() {

	Layer::onEnter();

	ValueMap taskMap = DataXML::getInstence()->getTask();
	for (auto t : taskMap)
	{
		std::string taskName = t.first;
		allCondition[taskName] = DataXML::getInstence()->getCurNumber(taskName);
	}
	setLabel();
}

void taskLayer::addSprite() {

	//条件框图标
	conditionIcon_1 = Sprite::createWithSpriteFrameName(CONDITION_NO_FILENAME);
	conditionIcon_1->setPosition(Vec2(300, 580));
	this->addChild(conditionIcon_1);

	conditionIcon_2 = Sprite::createWithSpriteFrameName(CONDITION_NO_FILENAME);
	conditionIcon_2->setPosition(Vec2(420, 580));
	this->addChild(conditionIcon_2);

	conditionIcon_3 = Sprite::createWithSpriteFrameName(CONDITION_NO_FILENAME);
	conditionIcon_3->setPosition(Vec2(540, 580));
	this->addChild(conditionIcon_3);

	conditionIcons.pushBack(conditionIcon_1);
	conditionIcons.pushBack(conditionIcon_2);
	conditionIcons.pushBack(conditionIcon_3);

	//箭头
	Sprite * arrorIcon = Sprite::createWithSpriteFrameName(ARROW_FILENAME);
	arrorIcon->setPosition(Vec2(630, 580));
	this->addChild(arrorIcon);
	//道具解锁条件
	Label * conditionLabel_1 = Label::createWithSystemFont("00/00", "Arial", 25);
	conditionLabel_1->setColor(Color3B::WHITE);
	conditionLabel_1->setNormalizedPosition(Vec2(0.5,0));
	conditionIcon_1->addChild(conditionLabel_1);

	Label * conditionLabel_2 = Label::createWithSystemFont("00/00", "Arial", 25);
	conditionLabel_2->setColor(Color3B::WHITE);
	conditionLabel_2->setNormalizedPosition(Vec2(0.5,0));
	conditionIcon_2->addChild(conditionLabel_2);

	Label * conditionLabel_3 = Label::createWithSystemFont("00/00", "Arial", 25);
	conditionLabel_3->setColor(Color3B::WHITE);
	conditionLabel_3->setNormalizedPosition(Vec2(0.5,0));
	conditionIcon_3->addChild(conditionLabel_3);

	labels.pushBack(conditionLabel_1);
	labels.pushBack(conditionLabel_2);
	labels.pushBack(conditionLabel_3);

}

void taskLayer::showTask() {

	ValueMap taskMap =  DataXML::getInstence()->getTask();
	if (taskMap.size() != 0)
	{
		for (int i = 0; i < conditionIcons.size(); i++)
		{
			conditionIcons.at(i)->setTexture(CONDITION_NO_FILENAME);
		}

		int num = 0;
		for (auto v : taskMap)
		{
			std::string name = v.first;

			Sprite * sp = Sprite::createWithSpriteFrameName(DataXML::getInstence()->getPictureName(name));
			sp->setNormalizedPosition(Vec2(0.5,0.5));
			taskSprites.pushBack(sp);
			conditionIcons.at(num)->setName(name);
			labels.at(num)->setName(conditionIcons.at(num)->getName());
			conditionIcons.at(num)->addChild(sp);
			num++;
		}
	}else{

		for (int i = 0; i < conditionIcons.size(); i++)
		{
			labels.at(i)->setVisible(false);
			conditionIcons.at(i)->setTexture(CONDITION_YES_FILENAME);
		}
	}
}

void taskLayer::addTool() {

	ValueMap toolMap = DataXML::getInstence()->getCurTool();
	if (toolMap.size() != 0)
	{
		for (auto v : toolMap)
		{
			std::string fileName = v.second.asString();
			taskTool = Sprite::createWithSpriteFrameName(fileName);
			taskTool->setPosition(685,570);
			this->addChild(taskTool);
		}
	}else
	{
		taskTool = Sprite::createWithSpriteFrameName(TOOLS_RIBBON_FILENAME);
		taskTool->setPosition(685,585);
		this->addChild(taskTool);
	}
}


void taskLayer::setLabel() {

	ValueMap taskMap = DataXML::getInstence()->getTask();
	int num = 0;
	for (auto v : taskMap)
	{
		std::string name = v.first;
		int curNumber = DataXML::getInstence()->getCurNumber(name);
		int number = v.second.asInt();
		Label *  rects = dynamic_cast<Label *> (this->getChildByName(name)->getChildByName(name));
		rects->setString(StringUtils::format("%d/%d",curNumber,number));
		num++;

		if (curNumber == number)
		{
			count++;
			Sprite * fangKuang  = dynamic_cast<Sprite *> (this->getChildByName(name));
			fangKuang->setTexture(CONDITION_YES_FILENAME);
		}
	}
}

//修改lebal显示
void taskLayer::changeDisplay(std::string name) {

	int i = 0;
	ValueMap taskMap = DataXML::getInstence()->getTask();

		Label *  rects = dynamic_cast<Label *> (this->getChildByName(name)->getChildByName(name));
		for (auto v : taskMap)
		{
			std::string taskName = v.first;
			if (taskName == name)
			{
				
				rects->setString(StringUtils::format("%d/%d",allCondition.at(v.first).asInt(),v.second.asInt()));
				if (allCondition.at(v.first) == v.second)
				{
					
					count++;
					Sprite * fangKuang  = dynamic_cast<Sprite *> (this->getChildByName(name));
					EFFECT_MUSIC("unlocked_row.mp3", audioFlag);
					fangKuang->setTexture(CONDITION_YES_FILENAME);
				}

				if (count == 3)
				{
					count = 0;
					for (auto v : allCondition)
					{
						allCondition.at(v.first) = 0;
					}
					//完成任务，写入XML，更改isfinish，任务完成后计数清零！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					//解锁道具,写入XML，更改isOpen
					for (int i = 0; i < taskSprites.size(); i++)
					{
						taskSprites.at(i)->removeFromParentAndCleanup(true);
					}

					taskSprites.clear();

					DataXML::getInstence()->finishTask();
					//更换任务，添加任务全部完成的情况，别忘了！！！！！！！！！！！！！！！！！！还有道具！！！！！！！！！！！！！！！
					showTask();
					setLabel();
					//移除并更换新道具
					taskTool->removeFromParentAndCleanup(true);
					//播放音效
					EFFECT_MUSIC("unlocked_rooster.mp3", audioFlag);
					addTool();
				} 
			}
		}
		i++;
}

void taskLayer::testMessage(Ref * message) {

	BaseSprite * sprite = dynamic_cast<BaseSprite *> (message);
	std::string name = sprite->getM_name();

	ValueMap taskMap = DataXML::getInstence()->getTask();

	for (auto taskName : taskMap)
	{
	 	std::string taskKey = taskName.first.c_str();
	 	if (name == taskKey)
	 	{
	 		for(auto v :allCondition){
	 			std::string key = v.first.c_str();
	 			if (name == key && allCondition.at(name).asInt() < taskMap.at(name).asInt())
	 			{
					//增加吃到道具数量达到任务要求后的处理！！！！！！！！！！！！！！！！！！！！别忘了
	 				int number = allCondition.at(name).asInt() + 1;
	 				allCondition[key] = number;

					//更改Label显示,更换黄匡
					changeDisplay(name);
	 			}
	 		}
	 	}
	}
}

taskLayer::~taskLayer() {
	
	NotificationCenter::getInstance()->removeObserver(this,"task");
	auto taskMap = DataXML::getInstence()->getTask();
	//存储任务数据
	for (auto v : taskMap)
	{

		std::string name = v.first;
		DataXML::getInstence()->saveData(name,allCondition.at(name).asInt());
	}
	
}
