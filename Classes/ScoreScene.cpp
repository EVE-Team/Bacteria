#include "ScoreScene.h"
#include "MenuScene.h"
#include "Utils.h"
#include "ShadowLabel.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
	return Utils::CreateScene<ScoreScene>();
}

ScoreScene* ScoreScene::create()
{
	return Utils::CreateCocosObject<ScoreScene>(
		[](){ return new (std::nothrow) ScoreScene(); },
		[](ScoreScene *s){ return s->init(); });
}

bool ScoreScene::init()
{
	if (!ButtonScene::init())
		return false;


	auto bg = Sprite::create("scores_bg.png");
	bg->setPosition(Vec2(Utils::GetVisibleSize().width / 2, Utils::GetVisibleSize().height / 2));
	addChild(bg);


	std::string scoreText = "Scores:\n";
	auto scoreVector = Utils::GetHighScores();
	for (size_t i = 0; i < scoreVector.size(); ++i)
	{
		scoreText += Utils::to_string(i + 1) + ": " + Utils::to_string(scoreVector[i]) + "\n";
	}

	auto scores = ShadowLabel::createWithTTF(scoreText, "fonts/Marker Felt.ttf", 36, Vec2(2, -2), Color3B(255, 255, 255), Color3B(0, 0, 0));
	scores->setPosition(Vec2(Utils::GetVisibleSize().width / 2, Utils::GetVisibleSize().height / 2 + 25));
	addChild(scores);


	AddButton("Back to menu", 100, [](){
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
