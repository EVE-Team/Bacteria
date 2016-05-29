#pragma once

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(std::string const& label = "Pause", bool resumeAllowed = true);
	static PauseScene* create(std::string const& label, bool resumeAllowed);
	virtual bool init(std::string const& label, bool resumeAllowed);

private:
	cocos2d::Sprite *resume = nullptr;
	cocos2d::Sprite *restart;
	cocos2d::Sprite *menu;
};
