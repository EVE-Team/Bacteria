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

	if (CircleSprite::CenterDistance(player, this) < 300)
	{
		vel = Utils::ResizeVec2(player->getPosition() - getPosition(), Utils::bacteriaPushForce);
		if (player->GetArea() > GetArea())
			vel *= -1;
	}
	else
	{
		if (Utils::length(GetVelocity()) < 0.2 * Utils::bacteriaPushForce)
		{
			auto planktonsList = &(gameScene->planktons->list);

			std::vector<Plankton*> vulnerablePlankton(planktonsList->size());
			auto vulnerablePlanktonEnd = std::copy_if(planktonsList->begin(), planktonsList->end(), vulnerablePlankton.begin(),
				[this](Plankton* p){ return p->Vulnerable(this); });
			vulnerablePlankton.erase(vulnerablePlanktonEnd, vulnerablePlankton.end());

			if (!vulnerablePlankton.empty())
			{
				std::vector<Plankton*> bigPlankton(vulnerablePlankton.size());
				auto bigPlanktonLast = std::copy_if(vulnerablePlankton.begin(), vulnerablePlankton.end(), bigPlankton.begin(),
					[planktonArea, this](Plankton* p){ return p->GetArea() > planktonArea + 100 && CircleSprite::CenterDistance(p, this) < 350; });
				bigPlankton.erase(bigPlanktonLast, bigPlankton.end());

				std::vector<Plankton*> &findSource = !bigPlankton.empty() ? bigPlankton : vulnerablePlankton;
				auto minIt = std::min_element(findSource.begin(), findSource.end(),
					[this](Plankton *a, Plankton *b){ return CircleSprite::CenterDistance(this, a) < CircleSprite::CenterDistance(this, b); });
				vel = Utils::ResizeVec2((*minIt)->getPosition() - getPosition(), Utils::bacteriaPushForce);
			}
		}
	}

	if (vel != Vec2())
	{
		gameScene->PushCircleSprite(this, vel, planktonArea);
		reload = RELOAD_TIME;
	}
}

const float Enemy::RELOAD_TIME = 0.4f;
