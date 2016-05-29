#pragma once

#include "cocos2d.h"

class Utils
{
public:
	static float sqr(float a);
	static float length(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	static float length(cocos2d::Vec2 v);
	static const cocos2d::Size fieldSize;
};
