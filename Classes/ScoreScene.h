#pragma once

#include "cocos2d.h"

class ScoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(ScoreScene);

private:
	cocos2d::Label *menu;
	cocos2d::Label *scores;
};
