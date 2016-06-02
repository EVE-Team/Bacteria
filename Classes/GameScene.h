#pragma once

#include "cocos2d.h"

class Player;
class Planktons;
class Enemies;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

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
	void UpdateInfo();

private:
	float score = 0;
};
