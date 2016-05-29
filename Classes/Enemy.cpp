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
		sprite->picSize = 1.0 * sprite->getContentSize().width / 2;
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

	if (GetArea() < 2 * Utils::planktonArea)
		return;

	Player *player = gameScene->player;
	float plDist = Utils::length(player->getPosition(), getPosition());

	if (plDist < 300)
	{
		Vec2 movTw = Utils::ResizeVec2(player->getPosition() - getPosition(), Utils::bacteriaPushForce);
		if (player->GetArea() > GetArea())
			movTw *= -1;
		Push(movTw);

		reload = RELOAD_TIME_MUL / GetArea();

		SetArea(GetArea() - Utils::planktonArea);
		gameScene->planktons->AddPlankton(getPosition());
		gameScene->planktons->list.back()->Push(movTw * Utils::planktonPushForceMul);
	}
	else
	{
		if (Utils::length(GetVelocity()) > 0.4 * (Utils::bacteriaPushForce / GetArea()))
			return;

		auto planktonsList = &(gameScene->planktons->list);
		auto minIt = std::min_element(planktonsList->begin(), planktonsList->end(),
			[this](Plankton *a, Plankton *b)
		{
			bool fairChoice = Utils::length(getPosition() - a->getPosition()) < Utils::length(getPosition() - b->getPosition());

			if (!b->Vulnerable())
				return a->Vulnerable() ? true : fairChoice;
			else
				return a->Vulnerable() ? fairChoice : false;

		});

		Vec2 mov = Utils::ResizeVec2((*minIt)->getPosition() - getPosition(), Utils::bacteriaPushForce);
		Push(mov);

		reload = RELOAD_TIME_MUL / GetArea();

		SetArea(GetArea() - Utils::planktonArea);
		gameScene->planktons->AddPlankton(getPosition());
		gameScene->planktons->list.back()->Push(mov * Utils::planktonPushForceMul);
	}
}

const float Enemy::RELOAD_TIME_MUL = 2000;
