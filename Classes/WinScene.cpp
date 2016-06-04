#include "WinScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* WinScene::createScene(GameProgress const& gameProgress, float newScore)
{
	return Utils::CreateScene<WinScene>(
		[&gameProgress, newScore](){ return WinScene::create(gameProgress, newScore); });
}

WinScene* WinScene::create(GameProgress const& gameProgress, float newScore)
{
	return Utils::CreateCocosObject<WinScene>(
		[](){ return new (std::nothrow) WinScene(); },
		[&gameProgress, newScore](WinScene *s){ return s->init(gameProgress, newScore); });
}

bool WinScene::init(GameProgress const& gameProgress, float newScore)
{
	if (!ButtonScene::init())
		return false;


	auto labelNode = Sprite::create("victory.png");
	labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 400));
	addChild(labelNode);


	AddButton("Next", 250, [gameProgress, newScore](){
		auto newGameProgress(gameProgress);
		newGameProgress.score = newScore;
		++newGameProgress.level;

		auto scene = GameScene::createScene(newGameProgress);
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Main menu", 100, [](){
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
