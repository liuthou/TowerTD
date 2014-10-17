#include "ScoreLayer.h"

bool ScoreLayer::init() {
	if (!BaseLayer::init()) {
		return false;
	}
	m_time = 0;
	m_timeLbl = Label::createWithSystemFont("0", "微软雅黑", 20);
	m_timeLbl->setSystemFontSize(20);
	m_timeLbl->setAnchorPoint(Vec2(1.0f, 0.5f));
	m_timeLbl->setPosition(VSIZE.width - 2, VSIZE.height - 10);
	this->addChild(m_timeLbl);

	//ÃÌº”Lable
	addTimeLabel();

	return true;
}

void ScoreLayer::update(float dt) {
	m_time += dt;
	m_timeLbl->setString(StringUtils::format("%0.3f", m_time));
}

void ScoreLayer::reset() {
	m_time = 0;
	m_timeLbl->setString("0");
}

void ScoreLayer::start() {
	this->setVisible(true);
	auto del = DelayTime::create(SCORE_COUNTING_START_DELAY);
	auto cal = CallFunc::create([=]() {
		this->scheduleUpdate();
	});
	this->runAction(Sequence::create(del, cal, NULL));
}

void ScoreLayer::stop() {
	this->unscheduleUpdate();
}

float ScoreLayer::getScore() {
	return this->m_time;
}

void ScoreLayer::addTimeLabel() {
	this->m_promTime = 5;
	m_lb = Label::create("", "Arial", 40);
	m_lb->setColor(Color3B::WHITE);
	m_lb->setAnchorPoint(Vec2(0.0f, 1.0f));
	m_lb->setPosition(VSIZE.width - 310, VSIZE.height - 10);
	m_lb->setVisible(false);
	this->addChild(m_lb);
}

void ScoreLayer::countTime(int t) {
	m_lb->stopAllActions();
	m_promTime = t;
	if (-1 == m_promTime) {
		m_lb->setVisible(false);
	} else {
		if (m_promTime >= 3) {
			m_lb->setColor(Color3B::WHITE);
		} else if (m_promTime <= 2 && m_promTime >= 0) {
			m_lb->setColor(Color3B::RED);
		}
		auto l_scale = ScaleTo::create(1.0f, 0);
		auto l_cal = CallFunc::create([=]() {
			this->m_lb->setScale(1.0f);
			this->countTime(m_promTime - 1);
		});
		m_lb->setVisible(true);
		m_lb->setString(StringUtils::format("%d", m_promTime));
		m_lb->runAction(Sequence::create(l_scale, l_cal, NULL));
	}
}
