#pragma once

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static HelloWorld* create();
	bool init() override;

private:
	cocos2d::Label *newGame;
	cocos2d::Label *scores;
	cocos2d::Label *exit;
};
