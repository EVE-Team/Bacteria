#pragma once

#include "ButtonScene.h"

class PauseScene : public ButtonScene
{
public:
	static cocos2d::Scene* createScene(std::string const& label = "pause.png", bool resumeAllowed = true);
	static PauseScene* create(std::string const& label, bool resumeAllowed);
	bool init(std::string const& label, bool resumeAllowed);
};
