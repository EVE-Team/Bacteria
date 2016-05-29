#pragma once

#include "CircleSprite.h"

class Enemy : public CircleSprite
{
public:
	static Enemy* create(cocos2d::Texture2D *texture);
};
