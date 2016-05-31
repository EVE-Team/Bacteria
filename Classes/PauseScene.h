#pragma once

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(std::string const& label = "pause.png", bool resumeAllowed = true);
	static PauseScene* create(std::string const& label, bool resumeAllowed);
	virtual bool init(std::string const& label, bool resumeAllowed);

private:
	cocos2d::Label *resume = nullptr;
	cocos2d::Label *restart;
	cocos2d::Label *menu;
};
