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

	static const float initForce = 1500000.0;

	if (GetArea() < 2 * Utils::planktonArea)
		return;

	if (Utils::length(GetVelocity()) > 0.5 * (initForce / GetArea()))
		return;

	Player *player = gameScene->player;
	float plDist = Utils::length(player->getPosition(), getPosition());

	if (plDist < 250)
	{
		Vec2 movTw = Utils::ResizeVec2(player->getPosition() - getPosition(), initForce);
		if (player->GetArea() > GetArea())
			movTw *= -1;
		Push(movTw);

		SetArea(GetArea() - Utils::planktonArea);
		gameScene->planktons->AddPlankton(getPosition());
		gameScene->planktons->list.back()->Push(movTw * -0.05);
	}
	else
	{
		auto planktonsList = &(gameScene->planktons->list);
		auto minIt = std::min_element(planktonsList->begin(), planktonsList->end(),
			[this](Plankton *a, Plankton *b){ return Utils::length(getPosition() - a->getPosition()) < Utils::length(getPosition() - b->getPosition()); });

		Vec2 mov = Utils::ResizeVec2((*minIt)->getPosition() - getPosition(), initForce);
		Push(mov);

		SetArea(GetArea() - Utils::planktonArea);
		gameScene->planktons->AddPlankton(getPosition());
		gameScene->planktons->list.back()->Push(mov * -0.05);
	}
}
