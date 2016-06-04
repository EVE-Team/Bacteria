#pragma once

#include "ButtonScene.h"
#include "GameProgress.h"

class LoseScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene(GameProgress const& gameProgress);
	static LoseScene* create(GameProgress const& gameProgress);
	bool init(GameProgress const& gameProgress);
};
