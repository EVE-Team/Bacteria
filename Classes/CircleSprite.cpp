#include "CircleSprite.h"
#include <math.h>
#include "Utils.h"

USING_NS_CC;

bool CircleSprite::Collide(CircleSprite *a, CircleSprite *b)
{
	float dist = Utils::length(a->getPosition() - b->getPosition());
	return dist < (a->GetRadius() + b->GetRadius());
}

float CircleSprite::GetArea() const
{
	return M_PI * GetRadius() * GetRadius();
}

void CircleSprite::SetArea(float a)
{
	SetRadius(sqrt(a / M_PI));
}

void CircleSprite::Push(Vec2 force)
{
	this->vel = force / GetArea();
}

void CircleSprite::Tick(float dt)
{
	if (vel == Vec2())
		return;

	setPosition(getPosition() + vel * dt);

	if (getPosition().x < GetRadius())
		setPositionX(GetRadius());
	else if (Utils::fieldSize.width - getPosition().x < GetRadius())
		setPositionX(getPositionX() - (GetRadius() - (Utils::fieldSize.width - getPosition().x)));

	if (getPosition().y < GetRadius())
		setPositionY(GetRadius());
	else if (Utils::fieldSize.height - getPosition().y < GetRadius())
		setPositionY(getPositionY() - (GetRadius() - (Utils::fieldSize.height - getPosition().y)));

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
