#include "CircleSprite.h"
#include <math.h>
#include "Utils.h"

USING_NS_CC;

float CircleSprite::GetArea() const
{
	return M_PI * GetRadius() * GetRadius();
}

void CircleSprite::SetArea(float a)
{
	SetRadius(sqrt(a / M_PI));
}

void CircleSprite::SetVel(Vec2 vel)
{
	this->vel = vel;
}

void CircleSprite::Tick(float dt)
{
	if (vel == Vec2())
		return;

	setPosition(getPosition() + vel * dt);

	float velAmp = Utils::length(vel);
	float newVelAmp = velAmp - 50 * dt;

	if (newVelAmp > 0)
	{
		float mul = newVelAmp / velAmp;
		vel *= mul;
	}
	else
	{
		vel = Vec2();
	}
}

float CircleSprite::GetRadius() const
{
	return picSize * getScale();
}

void CircleSprite::SetRadius(float r)
{
	setScale(r / picSize);
}
