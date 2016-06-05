#pragma once

#include "ButtonScene.h"

class HelpScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene();
	static HelpScene* create();
	bool init() override;
};
