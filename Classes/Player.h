#pragma once

#include "CircleSprite.h"

class Player : public CircleSprite
{
public:
	static Player* create(cocos2d::Size const& fieldSize);
};
