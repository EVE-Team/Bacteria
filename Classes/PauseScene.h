#pragma once

#include "ButtonScene.h"

class PauseScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene();
	static PauseScene* create();
	bool init() override;
};
