#include "Plankton.h"
#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;

Plankton* Plankton::create(GameScene *gameScene, Texture2D *texture, CircleSprite *owner)
{
	return Utils::CreateCocosObject<Plankton>(
		[gameScene, owner](){ return new (std::nothrow) Plankton(gameScene, owner); },
		[texture](Plankton *s){ return s->initWithTexture(texture); });
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
