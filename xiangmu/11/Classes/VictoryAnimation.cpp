#include "VictoryAnimation.h"

bool VictoryAnimation::init(){
    log("VictoryAnimation::init");
    if(!Layer::init()){
        return false;
    }
    
    initUI();
    
    this->addChild(amt);
	
    amt->getAnimation()->setMovementEventCallFunc(
          [this](Armature * _armture, MovementEventType _type, const std::string &_id){
              switch (_type) {
                  case cocostudio::COMPLETE:
                    this->amt->getAnimation()->stop();
                    this->End();
                  break;
                  default:
                  break;
              };
          }
          );
	return true;
}

//索引链表
void VictoryAnimation::play(TexasPoker::PokerMethod victor){
    log("VictoryAnimation::play ");
    
	switch (victor) {
	case TexasPoker::PokerMethod::FourOfAKind:
            log("TexasPoker::PokerMethod::FourOfAKind");
		jgAnimation();
		break;
	case TexasPoker::PokerMethod::Fullhouse:
            log("TexasPoker::PokerMethod::Fullhouse");
		hlAnimation();
		break;
	case TexasPoker::PokerMethod::StraightFlush:
            log("TexasPoker::PokerMethod::StraightFlush");
		thsAnimation();
		break;
	case TexasPoker::PokerMethod::RoyalFlush:
            log("TexasPoker::PokerMethod::RoyalFlush");
		hjthsAnimation();
		break;
    default: 
            log("VictoryAnimation::play none");
            break;
	 }
}

//金刚动画
void  VictoryAnimation::jgAnimation(){
    log("VictoryAnimation::jgAnimation");
    
    amt->setVisible(true);
    amt->setPositionX(amt->getPositionX() +150 );
	amt->getAnimation()->play("jg");
}

//葫芦动画
void  VictoryAnimation::hlAnimation(){
    log("VictoryAnimation::hlAnimation");
    
    amt->setVisible(true);
    amt->setPositionX(amt->getPositionX() +300 );
	amt->getAnimation()->play("hl");
}

//同花顺想动画
void  VictoryAnimation::thsAnimation(){
    log("VictoryAnimation::thsAnimation()");
    
    amt->setVisible(true);
	amt->getAnimation()->play("ths");
}

//皇家同花顺动画
void  VictoryAnimation::hjthsAnimation(){
    log("VictoryAnimation::hjthsAnimation()");
    
    amt->setVisible(true);
	amt->getAnimation()->play("hjths");
}

void VictoryAnimation::initUI(){
	ArmatureDataManager::getInstance()->addArmatureFileInfo("ANIMATION/shengli/shengli.ExportJson");
	amt = Armature::create("shengli");
    amt->setVisible(false);
}

void VictoryAnimation::End(){
    log("VictoryAnimation::End");
    auto _endFunc = endFunc;
    try{
        this->removeFromParentAndCleanup(true);
    }catch(...){
        ;
    }
    
    if (endFunc != nullptr) {
        _endFunc();
    }
    
}
