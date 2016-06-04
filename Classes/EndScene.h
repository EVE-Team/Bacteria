#pragma once

#include "ButtonScene.h"

class EndScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene();
	static EndScene* create();
	bool init() override;
};
