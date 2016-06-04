#pragma once

#include "ButtonScene.h"
#include "GameProgress.h"

class WinScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene(GameProgress const& gameProgress, float newScore);
	static WinScene* create(GameProgress const& gameProgress, float newScore);
	bool init(GameProgress const& gameProgress, float newScore);
};
