#pragma once

#include "cocos2d.h"
#include "GameProgress.h"
#include "GameData.h"

class Player;
class Planktons;
class Enemies;
class CircleSprite;
class ShadowLabel;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(GameProgress const& progress);
	static GameScene* create(GameProgress const& progress);
	bool init(GameProgress const& progress);

	void update(float dt) override;
	void onEnter() override;
	void onExit() override;

	cocos2d::Sprite *pause;
	Player *player;
	Planktons *planktons;
	ShadowLabel *massText;
	ShadowLabel *scoreText;
	cocos2d::Node *node;
	Enemies *enemies;

	void EatPlankton();
	void EnemyPlayerCollision();
	void AddScore(float score);
	void DelScore(float score);
	void UpdateInfo();
	bool IsAlive(CircleSprite *sprite) const;
	void PushCircleSprite(CircleSprite *sprite, cocos2d::Vec2 const& velocity, float planktonArea);
	const GameData& GetGameData() const;

private:
	GameProgress startProgress;
	float score;
	GameData gameData;
};
