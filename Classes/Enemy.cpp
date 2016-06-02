#include "Enemy.h"
#include "GameScene.h"
#include "Utils.h"
#include "Player.h"
#include "Planktons.h"
#include "Plankton.h"

USING_NS_CC;

Enemy* Enemy::create(GameScene *gameScene, Texture2D *texture)
{
	Enemy *sprite = new (std::nothrow) Enemy();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		sprite->gameScene = gameScene;
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Enemy::Tick(float dt)
{
	CircleSprite::Tick(dt);

	reload -= dt;
	if (reload < 0)
		reload = 0;

	if (reload > 0)
		return;

	Player *player = gameScene->player;
	float planktonArea = GetArea() * Utils::planktonAreaMul;

	Vec2 vel;

	if (CircleSprite::CenterDistance(player, this) < 250)
	{
		vel = Utils::ResizeVec2(player->getPosition() - getPosition(), Utils::bacteriaPushForce);
		if (player->GetArea() > GetArea())
			vel *= -1;
	}
	else
	{
		if (Utils::length(GetVelocity()) < 0.4 * Utils::bacteriaPushForce)
		{
			auto planktonsList = &(gameScene->planktons->list);
			auto minIt = std::min_element(planktonsList->begin(), planktonsList->end(),
				[this](Plankton *a, Plankton *b)
			{
				bool closerResult = CircleSprite::CenterDistance(this, a) < CircleSprite::CenterDistance(this, b);

				if (!b->Vulnerable(this))
					return a->Vulnerable(this) ? true : closerResult;
				else
					return a->Vulnerable(this) ? closerResult : false;
			});

			vel = Utils::ResizeVec2((*minIt)->getPosition() - getPosition(), Utils::bacteriaPushForce);
		}
	}

	if (vel != Vec2())
	{
		gameScene->PushCircleSprite(this, vel, planktonArea);
		reload = RELOAD_TIME;
	}
}

const float Enemy::RELOAD_TIME = 0.4f;
