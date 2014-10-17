#include "SkillButton.h"


USING_NS_CC;

SkillButton::SkillButton():
mStencil(NULL),
mProgressTimer(NULL),
mCDTime(1.f)
{
    
}

SkillButton::~SkillButton()
{
    
}

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name)
{
    SkillButton* skillButton = new SkillButton();
    if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name))
    {
        skillButton->autorelease();
        return skillButton;
    }
    else
    {
        delete skillButton;
        skillButton = NULL;
    }
    
    return NULL;
}

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name)
{
    CCAssert(stencil_file_name, "SkillButton::init stencil_file_name != NULL");
    CCAssert(button_normal_name, "SkillButton::init button_normal_name != NULL");
    
    // Notice:添加child时要注意上下层


    // 最下方是CCMenuItemImage 其次是模版图片 最上方是CCProgressTimer
//    mStencil2 = Sprite::create(button_normal_name);
//    mStencil2->setPosition(Vec2::ZERO);
//    mStencil2->setVisible(false);
//    addChild(mStencil2);
    // 添加阴影模版
//    mStencil = Sprite::create(button_normal_name);
//    mStencil->setPosition(Vec2::ZERO);
//    mStencil->setVisible(false);
//    addChild(mStencil);
    // 添加旋转进度条精灵
    Sprite* progressSprite = Sprite::create(stencil_file_name);
    mProgressTimer = ProgressTimer::create(progressSprite);
    mProgressTimer->setPosition(Vec2::ZERO);
    mProgressTimer->setVisible(false);
    addChild(mProgressTimer, 100);
    
    mCDTime = cdTime;
    return true;
}
void SkillButton::startCd(int i){
    // 模版可见
//    mStencil->setVisible(true);
    // 设置精灵进度条为顺时针
    mProgressTimer->setVisible(true);
    mProgressTimer->setType(ProgressTimer::Type::RADIAL);
//    mProgressTimer -> setPercentage(25);
    //准备一个5秒旋转360度的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)
    ActionInterval* action_progress_to = ProgressTo::create(0.5, i);
//    CallFunc* action_callback =  CallFunc::create([=]{
//        // 进度条技能不可见
//        mProgressTimer->setVisible(false);
//    });
    mProgressTimer->runAction(CCSequence::create(action_progress_to, NULL));
}
void SkillButton::onEnter(){
    Node::onEnter();

}
Size SkillButton::getContentSize(){
    return mProgressTimer -> getContentSize();
}
