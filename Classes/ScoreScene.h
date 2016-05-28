#pragma once

#include "cocos2d.h"

class ScoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ScoreScene);

private:
	cocos2d::Sprite *menu;
};
