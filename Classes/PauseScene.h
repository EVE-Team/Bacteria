#pragma once

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);

private:
	cocos2d::Sprite *resume;
	cocos2d::Sprite *restart;
	cocos2d::Sprite *menu;
};
