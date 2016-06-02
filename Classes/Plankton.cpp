#include "Plankton.h"
#include "GameScene.h"

USING_NS_CC;

Plankton* Plankton::create(GameScene *gameScene, Texture2D *texture, CircleSprite *owner)
{
	Plankton *sprite = new (std::nothrow) Plankton(gameScene, owner);
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Plankton::Plankton(GameScene *gameScene, CircleSprite *owner)
	: owner(owner)
	, gameScene(gameScene)
{}

void Plankton::Tick(float dt)
{
	CircleSprite::Tick(dt);

	if (!gameScene->IsAlive(owner))
		owner = nullptr;

	if (owner && CircleSprite::CenterDistance(owner, this) > owner->GetRadius() + GetRadius())
		owner = nullptr;
}

bool Plankton::Vulnerable(CircleSprite *attacker) const
{
	return attacker != owner;
}
