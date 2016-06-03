#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static MenuScene* create();
	bool init() override;

private:
	cocos2d::Label *newGame;
	cocos2d::Label *scores;
	cocos2d::Label *exit;
};
