#include "CircleSprite.h"
#include <math.h>
#include "Utils.h"

USING_NS_CC;

float CircleSprite::CenterDistance(CircleSprite *a, CircleSprite *b)
{
	return Utils::length(a->getPosition() - b->getPosition());
}

bool CircleSprite::MassExchange(CircleSprite *a, CircleSprite *b)
{
	CircleSprite *donator, *receiver;
	if (a->GetArea() < b->GetArea())
	{
		donator = a;
		receiver = b;
	}
	else
	{
		donator = b;
		receiver = a;
	}

	if (donator->GetRadius() < Utils::minBacteriaRadius)
		return false;

	float areaSum = a->GetArea() + b->GetArea();
	float cropRadius = a->GetRadius() + b->GetRadius() - CenterDistance(a, b);
	donator->SetRadius(donator->GetRadius() - cropRadius);
	receiver->SetArea(areaSum - donator->GetArea());
	return true;
}

float CircleSprite::GetArea() const
{
	return M_PI * GetRadius() * GetRadius();
}

void CircleSprite::SetArea(float a)
{
	SetRadius(sqrt(a / M_PI));
}

void CircleSprite::AddVelocity(Vec2 vel)
{
	this->vel += vel;
}

void CircleSprite::Tick(float dt)
{
	if (vel == Vec2())
		return;

	setPosition(getPosition() + vel * dt);

	if (getPosition().x < GetRadius())
	{
		setPositionX(GetRadius());
		vel.x = 0;
	}
	else if (Utils::fieldSize.width - getPosition().x < GetRadius())
	{
		setPositionX(getPositionX() - (GetRadius() - (Utils::fieldSize.width - getPosition().x)));
		vel.x = 0;
	}

	if (getPosition().y < GetRadius())
	{
		setPositionY(GetRadius());
		vel.y = 0;
	}
	else if (Utils::fieldSize.height - getPosition().y < GetRadius())
	{
		setPositionY(getPositionY() - (GetRadius() - (Utils::fieldSize.height - getPosition().y)));
		vel.y = 0;
	}

	auto polVel = Utils::LinearToPolar(vel);
	polVel.dist -= 50 * dt;

	if (polVel.dist > 0)
	{
		vel = Utils::PolarToLinear(polVel);
	}
	else
	{
		vel = Vec2();
	}
}

Vec2 CircleSprite::GetVelocity() const
{
	return vel;
}

float CircleSprite::GetRadius() const
{
	return picSize * getScale();
}

void CircleSprite::SetRadius(float r)
{
	setScale(r / picSize);
}
