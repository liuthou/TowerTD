#include "ResultScene.h"
#include "MainScene.h"

ResultScene* ResultScene::create(float score) {
	auto scene = new ResultScene();
	if (scene && scene->init(score)) {
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool ResultScene::init(float score) {
	if (!Layer::init()) 
	{
		return false;
	}
	initUi();

	m_scoreTxt->setText(StringUtils::format("%0.1f", score));

	float maxScore = UserDefault::getInstance()->getFloatForKey("MaxScore", 0);
	if (maxScore < score) {
		maxScore = score;
		UserDefault::getInstance()->setFloatForKey("MaxScore", maxScore);
	}

	m_maxScoreTxt->setText(StringUtils::format("%0.1f", maxScore));

	return true;
}

Scene* ResultScene::createScene(float score) {
	auto s = Scene::create();
	s->addChild(ResultScene::create(score));
	return s;
}

void ResultScene::initUi() {
	auto bgSpr = Sprite::create("gameBG.png");
	bgSpr->setAnchorPoint(Vec2::ZERO);
	this->addChild(bgSpr);

	Widget * uiLayer = GUIReader::getInstance()->widgetFromJsonFile("EndLayer_1/EndLayer_1.json");
	this->addChild(uiLayer);

	auto m_restartBtn = (Button *)uiLayer->getChildByName("startBut");
	auto m_quitBtn = (Button *)uiLayer->getChildByName("quitBut");
	m_quitBtn->setVisible(false);

	m_scoreTxt = (Text *)uiLayer->getChildByName("currentLabel");
	m_maxScoreTxt = (Text *)uiLayer->getChildByName("historyLabel");

	m_restartBtn->addTouchEventListener([=](Ref* sender,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::BEGAN)	{
			SimpleAudioEngine::getInstance()->playEffect(CLIK_MUSIC);
		}
		if (t == Widget::TouchEventType::ENDED) {
			auto mainScene = MainScene::create();
			mainScene->start();	// start the game
			auto scene = TransitionShrinkGrow::create(1.0f, mainScene);
			Director::getInstance()->replaceScene(mainScene);
		}
	});
}