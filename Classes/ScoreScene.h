#pragma once

#include "cocos2d.h"

class ScoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static ScoreScene* create();
	bool init() override;

private:
	cocos2d::Label *menu;
	cocos2d::Label *scores;
};
