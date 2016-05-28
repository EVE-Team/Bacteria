#pragma once

#include "CircleSprite.h"

class Plankton : public CircleSprite
{
public:
	static Plankton* create(cocos2d::Texture2D *texture);
};
