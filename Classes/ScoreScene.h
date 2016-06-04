#pragma once

#include "ButtonScene.h"

class ScoreScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene();
	static ScoreScene* create();
	bool init() override;
};
