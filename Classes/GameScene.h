#pragma once

#include "cocos2d.h"

class Player;
class Planktons;
class Enemies;
class CircleSprite;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static GameScene* create();
	bool init() override;

	void update(float dt) override;
	void onEnter() override;
	void onExit() override;

	cocos2d::Sprite *pause;
	Player *player;
	Planktons *planktons;
	cocos2d::Label *massText;
	cocos2d::Node *node;
	Enemies *enemies;

	void EatPlankton();
	void EnemyPlayerCollision();
	void GameOver(std::string const& reason);
	void AddScore(float score);
	void DelScore(float score);
	void UpdateInfo();
	bool IsAlive(CircleSprite *sprite) const;
	void PushCircleSprite(CircleSprite *sprite, cocos2d::Vec2 const& velocity, float planktonArea);

private:
	float score = 0;
};
