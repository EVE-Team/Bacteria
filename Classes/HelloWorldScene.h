#pragma once

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

private:
	cocos2d::Sprite *newGame;
	cocos2d::Sprite *scores;
	cocos2d::Sprite *exit;
};
