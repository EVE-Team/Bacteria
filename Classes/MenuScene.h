#pragma once

#include "ButtonScene.h"

class MenuScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene();
	static MenuScene* create();
	bool init() override;
};
