#pragma once

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

private:
	cocos2d::Label *newGame;
	cocos2d::Label *scores;
	cocos2d::Label *exit;
};
